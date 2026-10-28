"""Browser regression checks. Serve dist first; optional argument is base URL."""
import math
from pathlib import Path
import sys
from playwright.sync_api import sync_playwright

BASE = sys.argv[1] if len(sys.argv) > 1 else 'http://127.0.0.1:3001'


with sync_playwright() as p:
    browser = p.chromium.launch(executable_path='/usr/bin/chromium', args=['--no-sandbox', '--enable-unsafe-swiftshader'])
    page = browser.new_page(viewport={'width': 1200, 'height': 900})
    errors = []
    page.on('pageerror', lambda e: errors.append(str(e)))
    page.on('console', lambda m: errors.append(m.text) if m.type == 'error' and '404' not in m.text else None)
    page.goto(BASE + '/character.html')
    page.wait_for_function('window.characterDiagnostics !== undefined', timeout=90000)
    page.wait_for_function('characterDiagnostics().frames > 3')
    for name in ['idle', 'walk', 'run', 'combat']:
        page.click(f'[data-clip="{name}"]')
        page.wait_for_function('(name) => characterDiagnostics().clip === name', arg=name)
        first = page.evaluate('characterDiagnostics()')
        page.wait_for_function('(t) => characterDiagnostics().time > t + .25', arg=first['time'])
        later = page.evaluate('characterDiagnostics()')
        assert later['finitePose'] and later['glError'] == 0, later
        assert math.dist(first['sampleVertex'], later['sampleVertex']) > .0001
    page.click('#togglePlayback')
    paused = page.evaluate('characterDiagnostics().time')
    page.wait_for_timeout(400)
    assert page.evaluate('characterDiagnostics().time') == paused
    page.check('#skeleton')
    assert page.evaluate('characterDiagnostics().skeletonVisible')
    page.uncheck('#skeleton')
    page.click('[data-clip="idle"]')
    page.mouse.move(800, 300); page.mouse.down(); page.mouse.move(900, 330); page.mouse.up()
    assert abs(page.evaluate('characterDiagnostics().azimuth') - .35) > .1
    old_distance = page.evaluate('characterDiagnostics().distance')
    page.mouse.wheel(0, 150)
    page.wait_for_function('(old) => characterDiagnostics().distance !== old', arg=old_distance)
    page.keyboard.down('KeyW')
    page.wait_for_function('Math.hypot(...characterDiagnostics().position) > .15')
    page.keyboard.up('KeyW')
    page.click('#resetView')
    assert page.evaluate('characterDiagnostics().position') == [0, 0, 0]
    page.screenshot(path='/tmp/rf-character-desktop.png')
    assert not errors, errors
    print('PASS desktop: 4 animated poses, pause, skeleton, orbit, zoom and WASD')

    page.goto(BASE + '/?character=1')
    page.wait_for_function('window.platformDiagnostics !== undefined', timeout=120000)
    initial = page.evaluate('platformDiagnostics()')
    assert initial['character']['triangles'] == 3098 and initial['glError'] == 0
    page.click('#play')
    page.keyboard.down('KeyW')
    page.wait_for_function('(z) => platformDiagnostics().player[2] < z - .35', arg=initial['player'][2])
    page.wait_for_function('platformDiagnostics().character.clip === "walk"')
    page.keyboard.down('ShiftLeft')
    page.wait_for_function('platformDiagnostics().character.clip === "run"')
    page.keyboard.up('ShiftLeft'); page.keyboard.up('KeyW')
    page.wait_for_function('platformDiagnostics().character.clip === "idle"')
    state = page.evaluate('platformDiagnostics()')
    assert abs(state['player'][1] - initial['player'][1]) < .1
    assert state['character']['finitePose'] and state['glError'] == 0
    page.screenshot(path='/tmp/rf-character-map.png')
    page.keyboard.press('Escape')
    page.wait_for_function('!platformDiagnostics().running')
    assert page.locator('#menu').is_visible()
    assert not errors, errors
    print('PASS map: original terrain + character, ground following, walk/run/idle, pause, no GL errors')

    mobile = browser.new_page(viewport={'width': 390, 'height': 844}, is_mobile=True, has_touch=True, device_scale_factor=1)
    mobile.on('pageerror', lambda e: errors.append(str(e)))
    mobile.goto(BASE + '/character.html')
    mobile.wait_for_function('window.characterDiagnostics !== undefined', timeout=90000)
    mobile.tap('[data-clip="run"]')
    mobile.wait_for_function('characterDiagnostics().clip === "run" && characterDiagnostics().frames > 3')
    assert mobile.evaluate('document.documentElement.scrollWidth <= innerWidth')
    mobile.screenshot(path='/tmp/rf-character-mobile.png')
    mobile.goto(BASE + '/?character=1')
    mobile.wait_for_function('window.platformDiagnostics !== undefined', timeout=120000)
    mobile.tap('#play')
    assert mobile.locator('#touch').is_visible()
    assert mobile.locator('[data-key="KeyE"]').is_hidden()
    z = mobile.evaluate('platformDiagnostics().player[2]')
    # Pointer events exercise the same held-button path used on touchscreens.
    mobile.locator('[data-key="KeyW"]').dispatch_event('pointerdown', {'pointerId':1})
    mobile.wait_for_function('(z) => platformDiagnostics().player[2] < z - .15', arg=z)
    mobile.locator('[data-key="KeyW"]').dispatch_event('pointerup', {'pointerId':1})
    assert mobile.evaluate('platformDiagnostics().glError') == 0
    assert not errors, errors
    print('PASS mobile: layout, animation selection, map touch controls')
    mobile.close()

    page.goto(BASE + '/')
    page.wait_for_function('window.platformDiagnostics !== undefined', timeout=120000)
    assert not page.evaluate('platformDiagnostics().characterMode')
    page.select_option('#skySelect', '1')
    page.wait_for_function('platformDiagnostics().sky.name === "Platform01sky2"')
    assert page.evaluate('platformDiagnostics().glError') == 0
    assert page.locator('a[href="character.html"]').is_visible()
    assert not errors, errors
    print('PASS existing flight mode and sky selection')

    failure = browser.new_page()
    failure.route('**/assets/character/*.png', lambda route: route.fulfill(status=503, body='unavailable'))
    failure.goto(BASE + '/character.html')
    failure.wait_for_selector('#retry:visible', timeout=60000)
    assert failure.locator('#loading').is_visible()
    assert 'Tekstur karakter gagal dimuat' in failure.locator('#loadText').inner_text()
    print('PASS missing texture: visible error and retry instead of blank page')
    browser.close()

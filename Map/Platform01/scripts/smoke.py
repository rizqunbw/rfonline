"""End-to-end test against npm start. Requires Playwright and Chromium."""
from pathlib import Path
import math
from playwright.sync_api import sync_playwright
with sync_playwright() as p:
    browser = p.chromium.launch(executable_path='/usr/bin/chromium', args=['--no-sandbox','--enable-unsafe-swiftshader'])
    page = browser.new_page(viewport={'width': 800, 'height': 600})
    errors = []
    page.on('pageerror', lambda e: errors.append(str(e)))
    page.goto('http://127.0.0.1:3000')
    page.wait_for_function('window.platformDiagnostics !== undefined', timeout=120000)
    assert page.evaluate('platformDiagnostics().triangles') == 271641
    assert page.evaluate('platformDiagnostics().terrain.textures') == 368
    assert page.evaluate('platformDiagnostics().terrain.lightmaps') == 9
    page.wait_for_function('platformDiagnostics().sky.frames > 0')
    assert page.evaluate('platformDiagnostics().sky.textures') == 9
    page.select_option('#skySelect','1')
    page.wait_for_function('platformDiagnostics().sky.name === "Platform01sky2"')
    assert page.evaluate('platformDiagnostics().sky.textures') == 13
    page.select_option('#skySelect','0')
    page.wait_for_function('platformDiagnostics().sky.name === "Platform01Sky"')
    assert page.evaluate('platformDiagnostics().glError') == 0
    print('PASS: both textured sky variants load and switch without WebGL errors')
    page.click('#play')
    page.wait_for_function('platformDiagnostics().running')
    # Navigate only via real keyboard controls. No teleport or game-state edits.
    held = set()
    for tick in range(1500):
        state = page.evaluate('platformDiagnostics()')
        if state['completed']:
            break
        target = next(b['position'] for b in state['beacons'] if not b['found'])
        delta = [target[i] - state['camera'][i] for i in range(3)]
        wanted = {'ShiftLeft'}
        for d, positive, negative in zip(delta, ['KeyD','KeyE','KeyS'], ['KeyA','KeyQ','KeyW']):
            if abs(d) > 2:
                wanted.add(positive if d > 0 else negative)
        for key in held - wanted: page.keyboard.up(key)
        for key in wanted - held: page.keyboard.down(key)
        held = wanted
        page.wait_for_timeout(100)
    for key in held: page.keyboard.up(key)
    assert state['completed'], state
    assert sum(b['found'] for b in state['beacons']) == 5
    assert page.locator('#finish').is_visible()
    assert state['glError'] == 0
    print('PASS: decoded mesh, keyboard navigation, 5 beacon pickups, victory screen')
    page.click('#restart')
    page.wait_for_function('platformDiagnostics().running')
    assert not any(b['found'] for b in page.evaluate('platformDiagnostics()')['beacons'])
    page.keyboard.press('Escape')
    page.wait_for_function('!platformDiagnostics().running')
    assert page.locator('#menu').is_visible()
    assert not errors, errors
    print('PASS: restart resets objectives, Escape pauses, no browser JS/WebGL errors')
    mobile = browser.new_context(viewport={'width':390,'height':844},is_mobile=True,has_touch=True)
    page = mobile.new_page()
    page.goto('http://127.0.0.1:3000')
    page.wait_for_function('window.platformDiagnostics !== undefined', timeout=120000)
    page.select_option('#skySelect','1')
    page.wait_for_function('platformDiagnostics().sky.name === "Platform01sky2"')
    page.tap('#play')
    assert page.locator('#touch').is_visible()
    assert page.evaluate('document.documentElement.scrollWidth <= innerWidth')
    print('PASS: mobile start, touch controls visible, no horizontal overflow')
    failure_page=browser.new_page()
    failure_page.route('**/assets/sky/Platform01Sky/1.png',lambda route:route.abort())
    failure_page.goto('http://127.0.0.1:3000')
    failure_page.wait_for_function('document.getElementById("status").textContent === "GAGAL MEMUAT"', timeout=120000)
    assert failure_page.locator('#play').is_disabled()
    print('PASS: missing sky texture reports a load error and prevents incomplete startup')
    browser.close()

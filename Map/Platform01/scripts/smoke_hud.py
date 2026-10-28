"""Exercise actual HUD controls against a built static site."""
import sys
from playwright.sync_api import sync_playwright

BASE=sys.argv[1] if len(sys.argv)>1 else 'http://127.0.0.1:3001'
with sync_playwright() as p:
    browser=p.chromium.launch(executable_path='/usr/bin/chromium',args=['--no-sandbox','--enable-unsafe-swiftshader'])
    page=browser.new_page(viewport={'width':1280,'height':960})
    errors=[]
    page.on('pageerror',lambda e:errors.append(str(e)))
    page.goto(BASE+'/')
    page.wait_for_function('window.platformDiagnostics !== undefined',timeout=120000)
    assert page.evaluate('platformDiagnostics().characterMode')
    page.click('#play')
    page.wait_for_selector('#rfHUD:visible')
    assert page.evaluate('platformDiagnostics().hud.roles')==40
    assert page.evaluate("[...document.querySelectorAll('#rfHUD img')].every(i=>i.complete && i.naturalWidth>0)")
    page.wait_for_selector('#rfNameplate:visible')
    box=page.locator('#rfNameplate').bounding_box()
    assert 0<box['x']<1280 and 0<box['y']<960
    page.keyboard.press('KeyI');page.wait_for_selector('[data-panel=inventory]:visible')
    page.screenshot(path='/tmp/rf-hud-inventory.png')
    page.click('[data-panel=inventory] [data-action=headwear]')
    assert page.evaluate('platformDiagnostics().character.headwear')=='helmet'
    page.keyboard.press('Escape')
    assert page.locator('#rfWindow').is_hidden() and page.evaluate('platformDiagnostics().running')

    position=page.evaluate('platformDiagnostics().player')
    page.keyboard.press('Enter')
    page.keyboard.type('wasd <img src=x onerror=alert(1)>')
    page.wait_for_timeout(300)
    assert page.evaluate('platformDiagnostics().player')==position
    page.keyboard.press('Enter')
    assert '<img src=x' in page.locator('#rfChatLog').inner_text()
    assert page.locator('#rfChatLog img').count()==0

    page.keyboard.down('KeyW');page.keyboard.down('ShiftLeft')
    page.wait_for_function('platformDiagnostics().stamina < 96',timeout=30000)
    page.keyboard.up('KeyW');page.keyboard.up('ShiftLeft')
    state=page.evaluate('platformDiagnostics()');assert state['player'][2]<position[2]
    page.wait_for_function('(old)=>platformDiagnostics().stamina>old+1',arg=state['stamina'])
    page.keyboard.press('Digit1')
    page.wait_for_function('platformDiagnostics().character.clip === "combat"')
    page.keyboard.press('Digit1')
    page.keyboard.press('KeyO');page.select_option('#rfSky','1')
    page.wait_for_function('platformDiagnostics().sky.name === "Platform01sky2"')
    page.locator('#rfCameraDistance').fill('10');page.locator('#rfCameraDistance').dispatch_event('input')
    assert page.evaluate('platformDiagnostics().cameraDistance')==10
    page.keyboard.press('Escape') # blur range
    page.keyboard.press('Escape') # close panel
    assert page.locator('#rfWindow').is_hidden()
    page.click('#rfRadarPlus');assert page.evaluate('platformDiagnostics().hud.radarRange')==65
    page.keyboard.press('KeyM');page.wait_for_selector('[data-panel=map]:visible')
    page.wait_for_function('document.getElementById("rfFullMapCoords").textContent.includes("Posisi")')
    page.keyboard.press('Escape')
    page.screenshot(path='/tmp/rf-hud-desktop.png')
    assert page.evaluate('platformDiagnostics().glError')==0
    page.keyboard.press('Escape');assert not page.evaluate('platformDiagnostics().running')
    assert page.locator('#rfHUD').is_hidden()
    print('PASS desktop HUD: original sprites, inventory/headwear, safe local chat, SP, combat pose, settings, map, pause',flush=True)

    mobile=browser.new_page(viewport={'width':390,'height':844},is_mobile=True,has_touch=True,device_scale_factor=1)
    mobile.on('pageerror',lambda e:errors.append(str(e)))
    mobile.goto(BASE+'/');mobile.wait_for_function('window.platformDiagnostics !== undefined',timeout=120000)
    mobile.tap('#play');mobile.wait_for_selector('#rfHUD:visible')
    assert mobile.evaluate('document.documentElement.scrollWidth<=innerWidth')
    for button in mobile.locator('.rf-hotkeys button').all():
        r=button.bounding_box();assert r['width']>=40 and r['height']>=40 and r['y']+r['height']<=844
    mobile.tap('.rf-hotkeys [data-action=inventory]');assert mobile.locator('[data-panel=inventory]').is_visible()
    mobile.tap('#rfWindowClose')
    z=mobile.evaluate('platformDiagnostics().player[2]')
    mobile.locator('[data-key=KeyW]').dispatch_event('pointerdown',{'pointerId':1})
    mobile.wait_for_function('(z)=>platformDiagnostics().player[2]<z-.15',arg=z)
    mobile.locator('[data-key=KeyW]').dispatch_event('pointerup',{'pointerId':1})
    mobile.screenshot(path='/tmp/rf-hud-mobile.png')
    mobile.tap('#rfPause');assert mobile.locator('#menu').is_visible()
    assert not errors,errors
    print('PASS mobile HUD: all 10 actions reachable, panels, movement, pause; no JS/GL errors',flush=True)
    browser.close()

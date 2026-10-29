"""Browser regression for the RF HUD, source keymaps and both control modes."""
import sys
from playwright.sync_api import sync_playwright
BASE=sys.argv[1] if len(sys.argv)>1 else 'http://127.0.0.1:3001'
with sync_playwright() as p:
    browser=p.chromium.launch(executable_path='/usr/bin/chromium',args=['--no-sandbox','--enable-unsafe-swiftshader'])
    page=browser.new_page(viewport={'width':1600,'height':900})
    errors=[]
    page.on('pageerror',lambda e:errors.append(str(e)))
    page.goto(BASE+'/');page.wait_for_function('window.platformDiagnostics !== undefined',timeout=120000)
    page.click('#play');page.wait_for_selector('#rfHUD:visible')
    assert page.evaluate('platformDiagnostics().nativeInput.commands')==76
    assert page.evaluate('platformDiagnostics().nativeInput.keys')==86
    assert page.evaluate('platformDiagnostics().nativeInput.keyboardBindings')==72
    assert page.evaluate('platformDiagnostics().hud.roles')==48
    assert page.evaluate('platformDiagnostics().controlMode')=='mouse'
    assert page.locator('[data-slot]').count()==50
    assert page.evaluate("[...document.querySelectorAll('#rfHUD img')].every(i=>i.complete && i.naturalWidth>0)")
    assert page.evaluate("[document.body,document.querySelector('button'),document.querySelector('input')].every(e=>getComputedStyle(e).fontFamily.includes('Lucida Console'))")
    page.keyboard.press('KeyI');page.keyboard.press('KeyC')
    assert set(page.evaluate('platformDiagnostics().hud.openPanels'))=={'inventory','character'}
    page.screenshot(path='/tmp/rf-native-windows.png')
    before=page.locator('#rfCharacterWindow').bounding_box()
    title=page.locator('#rfCharacterWindow h2').bounding_box()
    page.mouse.move(title['x']+title['width']/2,title['y']+8);page.mouse.down();page.mouse.move(title['x']+title['width']/2+65,title['y']+40,steps=4);page.mouse.up()
    after=page.locator('#rfCharacterWindow').bounding_box();assert after['x']>before['x']+50
    page.keyboard.press('Escape');assert page.locator('#rfCharacterWindow').is_hidden()
    assert page.locator('#rfInventoryWindow').is_visible()
    page.click('[data-equipment=helmet]')
    assert page.evaluate('platformDiagnostics().character.headwear')=='helmet'
    page.keyboard.press('Escape');assert page.evaluate('platformDiagnostics().running')
    print('PASS native windows: concurrent, draggable, separate closing, real headwear switch',flush=True)

    initial=page.evaluate('platformDiagnostics().player')
    page.keyboard.press('KeyW')
    assert page.evaluate('platformDiagnostics().runMode') # Mouse map W toggles walk/run.
    assert page.evaluate('platformDiagnostics().player')==initial
    page.keyboard.press('KeyW')
    page.mouse.click(890,600)
    page.wait_for_function('platformDiagnostics().moveTarget!==null',timeout=5000)
    page.wait_for_function('(p)=>Math.hypot(...platformDiagnostics().player.map((v,i)=>v-p[i]))>.2',arg=initial)
    page.keyboard.press('KeyH')
    assert page.evaluate('platformDiagnostics().controlMode')=='keyboard'
    assert page.evaluate('platformDiagnostics().moveTarget') is None
    page.keyboard.down('ShiftLeft');page.keyboard.down('KeyW')
    page.wait_for_function('platformDiagnostics().stamina<96')
    page.keyboard.up('KeyW');page.keyboard.up('ShiftLeft')
    state=page.evaluate('platformDiagnostics()')
    page.wait_for_function('(old)=>platformDiagnostics().stamina>old+1',arg=state['stamina'])
    page.keyboard.press('Semicolon');page.wait_for_function('platformDiagnostics().character.clip==="combat"')
    page.keyboard.press('Semicolon')
    camera=page.evaluate('platformDiagnostics().camera')
    page.keyboard.down('KeyQ');page.wait_for_function('(old)=>Math.abs(platformDiagnostics().camera[0]-old[0])>.15',arg=camera);page.keyboard.up('KeyQ')
    position=page.evaluate('platformDiagnostics().player')
    page.keyboard.press('Enter');page.keyboard.type('h wasd <b>test</b>');page.keyboard.press('Enter')
    assert page.evaluate('platformDiagnostics().controlMode')=='keyboard'
    assert page.evaluate('platformDiagnostics().player')==position
    assert '<b>test</b>' in page.locator('#rfChatLog').inner_text()
    assert page.locator('#rfChatLog b').count()==0
    print('PASS source control modes: mouse click movement, H, plain WASD, shift sprint, Q camera, chat isolation',flush=True)

    page.click('[data-slot="1:0"]');page.select_option('#rfSlotAction','inventory');page.click('#rfSlotDone')
    page.keyboard.press('F1');assert page.locator('#rfInventoryWindow').is_visible()
    page.keyboard.press('Escape')
    page.click('[data-slot="1:0"]',button='right');assert page.evaluate('platformDiagnostics().hud.assignedSlots')==0
    page.keyboard.press('Backslash');assert page.evaluate('platformDiagnostics().hud.activeBelt')==2
    page.keyboard.press('Alt+KeyH');assert page.locator('#rfHUD').evaluate("e=>e.classList.contains('rf-ui-hidden')")
    page.keyboard.press('Alt+KeyH')
    page.keyboard.press('KeyO');page.select_option('#rfSky','1');page.wait_for_function('platformDiagnostics().sky.name==="Platform01sky2"')
    page.locator('#rfCameraDistance').fill('10');page.locator('#rfCameraDistance').dispatch_event('input');assert page.evaluate('platformDiagnostics().cameraDistance')==10
    page.keyboard.press('Escape');page.keyboard.press('Escape')
    page.keyboard.press('KeyM');page.wait_for_selector('[data-panel=map]:visible');page.keyboard.press('Escape')
    page.screenshot(path='/tmp/rf-native-hud.png')
    assert page.evaluate('platformDiagnostics().glError')==0
    page.keyboard.press('Escape');assert not page.evaluate('platformDiagnostics().running')
    print('PASS hotbar assignment, native bindings, settings, map and pause',flush=True)
    page.close()

    mobile=browser.new_page(viewport={'width':390,'height':844},is_mobile=True,has_touch=True,device_scale_factor=1)
    mobile.on('pageerror',lambda e:errors.append(str(e)))
    mobile.goto(BASE+'/');mobile.wait_for_function('window.platformDiagnostics !== undefined',timeout=120000)
    mobile.tap('#play');mobile.wait_for_selector('#rfHUD:visible')
    assert mobile.evaluate('document.documentElement.scrollWidth<=innerWidth')
    assert mobile.locator('.rf-belt-row.active [data-slot]').count()==10
    for button in mobile.locator('.rf-belt-row.active [data-slot]').all():
        box=button.bounding_box();assert box['width']>=44 and box['height']>=44 and box['y']+box['height']<=844
    mobile.tap('#rfNextBelt');assert mobile.evaluate('platformDiagnostics().hud.activeBelt')==2
    mobile.tap('#rfInputMode');assert mobile.evaluate('platformDiagnostics().controlMode')=='keyboard'
    mobile.tap('[data-slot="2:0"]');mobile.select_option('#rfSlotAction','inventory');mobile.tap('#rfSlotDone');mobile.tap('[data-slot="2:0"]')
    assert mobile.locator('#rfInventoryWindow').is_visible();mobile.tap('[data-close-window=inventory]')
    z=mobile.evaluate('platformDiagnostics().player[2]')
    mobile.locator('[data-key=KeyW]').dispatch_event('pointerdown',{'pointerId':1});mobile.wait_for_function('(z)=>platformDiagnostics().player[2]<z-.15',arg=z)
    mobile.locator('[data-key=KeyW]').dispatch_event('pointerup',{'pointerId':1})
    mobile.screenshot(path='/tmp/rf-native-mobile.png')
    mobile.tap('#rfPause');assert mobile.locator('#menu').is_visible()
    assert not errors,errors
    print('PASS mobile: reachable controls, 5 selectable belts, mode switch, inventory, touch movement and pause',flush=True)
    browser.close()

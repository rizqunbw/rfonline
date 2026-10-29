"""Check the actual game consumes non-default config and fails visibly on bad config."""
import json
import sys
from pathlib import Path
from playwright.sync_api import sync_playwright

BASE = sys.argv[1] if len(sys.argv) > 1 else 'http://127.0.0.1:3001'
source = json.loads((Path(__file__).resolve().parents[3] / 'System/web-client.json').read_text())
with sync_playwright() as p:
    browser = p.chromium.launch(executable_path='/usr/bin/chromium', args=['--no-sandbox', '--enable-unsafe-swiftshader'])
    page = browser.new_page(viewport={'width':1024,'height':768}, device_scale_factor=2)
    errors = []
    page.on('pageerror', lambda e: errors.append(str(e)))
    custom = json.loads(json.dumps(source))
    custom['camera'].update(distance=10, minDistance=6, maxDistance=12, fovDegrees=70)
    custom['input']['defaultMode'] = 'keyboard'
    custom['renderer']['maxPixelRatio'] = .75
    custom['movement']['walkSpeed'] = 3
    page.route('**/assets/system/web-client.json', lambda route: route.fulfill(json=custom))
    page.goto(BASE)
    page.wait_for_function('window.platformDiagnostics !== undefined', timeout=120000)
    assert page.evaluate('platformDiagnostics().cameraDistance') == 10
    assert page.evaluate('platformDiagnostics().controlMode') == 'keyboard'
    assert page.locator('#rfCameraDistance').get_attribute('min') == '6'
    assert page.locator('#rfCameraDistance').get_attribute('max') == '12'
    assert page.locator('#rfCameraDistance').input_value() == '10'
    assert page.locator('#world').evaluate('e=>e.width') == 768
    assert 'Lucida Console' in page.locator('#rfChatInput').evaluate('e=>getComputedStyle(e).fontFamily')
    page.click('#play')
    assert 'Keyboard mode' in page.locator('#rfInputMode').inner_text()
    before = page.evaluate('platformDiagnostics().player')
    page.keyboard.down('KeyW')
    page.wait_for_function('(p)=>platformDiagnostics().player[2]<p[2]-.2',arg=before)
    page.keyboard.up('KeyW')
    page.keyboard.press('KeyH')
    assert page.evaluate('platformDiagnostics().controlMode') == 'mouse'
    # The configured FOV must also feed the screen-to-ground ray.
    page.locator('#world').click(position={'x':512,'y':500})
    page.wait_for_function('platformDiagnostics().moveTarget!==null')
    page.keyboard.press('Escape')
    page.keyboard.press('Escape')
    assert page.evaluate('platformDiagnostics().glError') == 0
    assert not errors, errors
    print('PASS active JSON config: camera/slider, renderer, font, initial keyboard mode, movement and click ray at custom FOV', flush=True)
    page.close()
    bad = browser.new_page()
    invalid = json.loads(json.dumps(source));invalid['camera']['distance'] = 999
    bad.route('**/assets/system/web-client.json', lambda route: route.fulfill(json=invalid))
    bad.goto(BASE)
    bad.wait_for_function("document.getElementById('assetInfo').textContent.includes('invalid camera.distance')")
    assert bad.locator('#play').is_disabled()
    assert bad.evaluate('window.platformDiagnostics===undefined')
    print('PASS invalid configuration blocks startup with field-specific error', flush=True)
    browser.close()

"""Verify Excel serials, the native character panel and item tooltip behavior."""
import sys
from playwright.sync_api import sync_playwright
BASE=sys.argv[1] if len(sys.argv)>1 else 'http://127.0.0.1:3001'
with sync_playwright() as p:
 b=p.chromium.launch(executable_path='/usr/bin/chromium',args=['--no-sandbox','--enable-unsafe-swiftshader'])
 page=b.new_page(viewport={'width':1280,'height':993});errors=[]
 page.on('pageerror',lambda e:errors.append(str(e)))
 page.goto(BASE+'/');page.wait_for_function('window.platformDiagnostics!==undefined',timeout=120000)
 assert page.evaluate('platformDiagnostics().language.count')==4321
 page.click('#play');page.keyboard.press('KeyC')
 assert page.locator('#rfCharacterWindow').is_visible()
 for section in ['General Info','Status Info','Ability Info','Elem. Resist Info']:
  assert page.locator('#rfCharacterWindow summary').filter(has_text=section).count()==1
 assert '99.99%' not in page.locator('#rfCharacterWindow').inner_text()
 assert page.locator('#rfInfo-status dd').filter(has_text='—').count()==10
 assert page.locator('.rf-belt-row:visible').count()==1
 mismatches=page.evaluate('''async()=>{
  const d=await (await fetch('assets/language.json')).json();
  return [...document.querySelectorAll('#rfHUD span[data-language-id]')].filter(e=>!d.phrases[e.dataset.languageId].includes('%') && e.textContent!==d.phrases[e.dataset.languageId].replaceAll('\\\\n','\\n')).map(e=>({id:e.dataset.languageId,text:e.textContent}));
 }''')
 assert not mismatches,mismatches
 page.screenshot(path='/tmp/rf-language-character.jpg',type='jpeg',quality=80)
 page.keyboard.press('KeyC');page.keyboard.press('KeyI')
 page.locator('[data-equipment=upper]').hover()
 page.wait_for_selector('#rfItemTooltip:visible')
 assert page.locator('#rfItemType').inner_text()=='Upper'
 assert 'Required Level' in page.locator('#rfItemTooltip').inner_text()
 assert 'Defense Success Rate' in page.locator('#rfItemTooltip').inner_text()
 assert '[Description]' in page.locator('#rfItemTooltip').inner_text()
 box=page.locator('#rfItemTooltip').bounding_box();assert box['x']>=0 and box['x']+box['width']<=1280 and box['y']>=0 and box['y']+box['height']<=993
 assert page.locator('#rfItemTooltip img').count()==0 # Real item icons deferred.
 page.screenshot(path='/tmp/rf-language-item.jpg',type='jpeg',quality=80)
 page.mouse.move(400,200);page.wait_for_selector('#rfItemTooltip',state='hidden')
 page.locator('[data-equipment=boots]').focus();page.wait_for_selector('#rfItemTooltip:visible');assert page.locator('#rfItemType').inner_text()=='Shoes'
 page.keyboard.press('Escape');assert page.locator('#rfItemTooltip').is_hidden()
 page.keyboard.press('KeyH');assert page.evaluate('platformDiagnostics().controlMode')=='keyboard'
 assert page.locator('#rfInputMode').inner_text()=='Keyboard mode [H]'
 position=page.evaluate('platformDiagnostics().player');page.keyboard.down('KeyW');page.wait_for_function('(p)=>platformDiagnostics().player[2]<p[2]-.15',arg=position);page.keyboard.up('KeyW')
 page.keyboard.press('Enter');page.keyboard.type('h <b>test</b>');page.keyboard.press('Enter')
 assert '<b>test</b>' in page.locator('#rfChatLog').inner_text();assert page.locator('#rfChatLog b').count()==0
 assert page.evaluate('platformDiagnostics().controlMode')=='keyboard'
 page.keyboard.press('KeyO');page.select_option('#rfBeltRows','5');assert page.locator('.rf-belt-row:visible').count()==5
 page.keyboard.press('Escape');page.keyboard.press('Escape')
 assert page.evaluate('platformDiagnostics().glError')==0
 print('PASS Excel serials, character sections, empty mastery, hover/focus tooltip, viewport clamping, no fake item icon, keyboard and safe chat',flush=True)
 page.close()
 mobile=b.new_page(viewport={'width':390,'height':844},is_mobile=True,has_touch=True,device_scale_factor=1)
 mobile.on('pageerror',lambda e:errors.append(str(e)))
 mobile.goto(BASE+'/');mobile.wait_for_function('window.platformDiagnostics!==undefined',timeout=120000);mobile.tap('#play')
 mobile.tap('[data-slot="1:0"]');mobile.select_option('#rfSlotAction','inventory');mobile.tap('#rfSlotDone');mobile.tap('[data-slot="1:0"]')
 mobile.tap('[data-equipment=upper]');mobile.wait_for_selector('#rfItemTooltip:visible')
 box=mobile.locator('#rfItemTooltip').bounding_box();assert box['x']>=0 and box['x']+box['width']<=390 and box['y']>=0 and box['y']+box['height']<=844
 assert mobile.locator('#rfItemTooltip').evaluate("e=>e.classList.contains('pinned')")
 mobile.screenshot(path='/tmp/rf-language-mobile.jpg',type='jpeg',quality=80)
 mobile.tap('#rfItemTooltipClose');assert mobile.locator('#rfItemTooltip').is_hidden()
 assert mobile.locator('#rfInventoryWindow').is_visible()
 mobile.tap('[data-close-window=inventory]');mobile.tap('#rfPause');assert mobile.locator('#menu').is_visible()
 assert mobile.evaluate('document.documentElement.scrollWidth<=innerWidth')
 assert not errors,errors
 print('PASS mobile tooltip: tap, close, inventory preserved, viewport fit, no JS errors',flush=True)
 b.close()

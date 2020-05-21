load("api_timer.js")
load("api_config.js")
load("api_zswitch_gpio.js")

function onTimer(sw) {
  let state = sw.toggleState();
  if (state === ZenThing.RESULT_ERROR) {
    print('Error toggling status of switch', sw.id);
  } else {
    print('Switch', sw.id, 'switched', (state === true  ? 'ON' : 'OFF'));
  }
};

/* Create switches having the same group ID,
 * so when one will be turned on, all others
 * will be automatically torned off.
 */   
let cfg = {groupId: 1};
let sw1 = ZenSwitch.create(Cfg.get('app.relay1.id'), cfg);
let sw2 = ZenSwitch.create(Cfg.get('app.relay2.id'), cfg);

let success = false;
let gpioCfg = {activeHigh: Cfg.get('app.relays_active_high')};
if (sw1 && sw2) {
  if (sw1.GPIO.attach(Cfg.get('app.relay1.pin'), gpioCfg) &&
      sw2.GPIO.attach(Cfg.get('app.relay2.pin'), gpioCfg)) {
    Timer.set(5000, Timer.REPEAT, onTimer, sw1);
    Timer.set(10000, Timer.REPEAT, onTimer, sw2);
    success = true;
  }
}

if (!success) {
  if (sw1) {
    sw1.GPIO.detach();
    sw1.close();
  }
  if (sw2) {
    sw2.GPIO.detach();
    sw2.close();
  }
  print('Error initializing the firmware');
}

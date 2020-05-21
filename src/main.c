#include "mgos.h"
#include "mgos_zswitch_gpio.h"


static void relay_timer_cb(void *arg) {
  struct mgos_zswitch *handle = (struct mgos_zswitch *)arg;
  int state = mgos_zswitch_state_toggle(handle);
  if (state == MGOS_ZTHING_RESULT_ERROR) {
    LOG(LL_ERROR, ("Error toggling status of switch '%s'", handle->id));  
  } else {
    LOG(LL_INFO, ("Switch '%s', switched %s", handle->id,
      (state == true ? "ON" : "OFF")));
  }
}

enum mgos_app_init_result mgos_app_init(void) {
  /* Create switches having the same group ID,
   * so when one will be turned on, all others
   * will be automatically torned off.
   */
  struct mgos_zswitch_cfg cfg = MGOS_ZSWITCH_CFG;
  cfg.group_id = 1;
  struct mgos_zswitch *sw1 = NULL;
  sw1 = mgos_zswitch_create(mgos_sys_config_get_app_relay1_id(), &cfg);
  struct mgos_zswitch *sw2 = NULL;
  sw2 = mgos_zswitch_create(mgos_sys_config_get_app_relay2_id(), &cfg);
  
  if (sw1 == NULL || sw2 == NULL) return MGOS_APP_INIT_ERROR;

  struct mgos_zswitch_gpio_cfg gpio_cfg = MGOS_ZSWITCH_GPIO_CFG;
  gpio_cfg.active_high = mgos_sys_config_get_app_relays_active_high();
 
  /* Attach switches to GPIOs */
  if (!mgos_zswitch_gpio_attach(sw1, mgos_sys_config_get_app_relay1_pin(), &gpio_cfg) ||
      !mgos_zswitch_gpio_attach(sw2, mgos_sys_config_get_app_relay2_pin(), &gpio_cfg)) {
    return MGOS_APP_INIT_ERROR;
  }
  
  mgos_set_timer(5000, MGOS_TIMER_REPEAT,
    relay_timer_cb, sw1);
  
  mgos_set_timer(10000, MGOS_TIMER_REPEAT,
    relay_timer_cb, sw2);

  return MGOS_APP_INIT_SUCCESS;
}
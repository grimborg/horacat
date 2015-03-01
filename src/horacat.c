/**
 * L'hora en català
 *
 * Pebble SDK 2.0
 * GPL v3
 * Copyright dev@oscarvilaplana.cat
 **/

#include <pebble.h>
#include "./rellotge.h"
#include "./layers.h"
#include "./hores.h"

Window *window;

rellotge_t rellotge;

/**
 * Window load event handler.
 */
static void window_load(Window *window) {
  init_clock();
}

/**
 * Window uload event handler.
 */
static void window_unload(Window *window) {
  destroy_clock();
}

/**
 * Minute tick event handler.
 */
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  update_temps(tick_time);
  update_clock();
}

/**
 * Initialize the watchface.
 */
static void init(void) {
  window = window_create();
  window_set_background_color(window, GColorBlack);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
  const bool animated = true;
  window_stack_push(window, animated);
}

/**
 * Destroy the window.
 */
static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

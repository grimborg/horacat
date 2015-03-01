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

#ifdef PBL_COLOR
static void update_color(struct tm *tick_time) {
    GColor8 color;
    int hour = tick_time->tm_min;
    if (hour >= 6 && hour < 10) {
        color = GColorCadetBlue;
    }
    else if (hour >= 10 && hour < 12) {
        color = GColorChromeYellow;
    } else if (hour >= 12 && hour < 14) {
        color = GColorRoseVale;
    } else if (hour>=14 && hour < 18) {
        color = GColorWindsorTan;
    } else if (hour>=18 && hour < 22) {
        color = GColorLiberty;
    } else {
        color = GColorBulgarianRose;
    }
    window_set_background_color(window, color);
}
#else
static void update_color(struct tm *tick_time) {
}
#endif


/**
 * Minute tick event handler.
 */
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  update_color(tick_time);
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

/**
 * L'hora en català
 *
 * Create, update and destroy the clock layers.
 *
 * Pebble SDK 2.0
 * GPL v3
 * Copyright dev@oscarvilaplana.cat
 **/

#include <pebble.h>
#include "./hores.h"
#include "./layers.h"
#include "./rellotge.h"

static GFont font_thin;
static GFont font_thick;

Window *window;
rellotge_t rellotge;
temps_t temps;

/**
 * Create a text layer for the clock and add it to the window.
 *
 * @param window_layer window layer where the text layer should be added.
 * @param font font to use in the text layer
 * @param x left coordinate
 * @param y top coordinate
 * @param w width
 * @param h height
 */
static TextLayer *create_clock_text_layer(Layer *window_layer, GFont font,
    int x, int y, int w, int h) {
  GRect rect = (GRect) {.origin = {x, y}, .size = {w, h}};
  TextLayer *text_layer = text_layer_create(rect);
  text_layer_set_font(text_layer, font);
  text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
  text_layer_set_text_color(text_layer, GColorWhite);
  text_layer_set_background_color(text_layer, GColorClear);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  return text_layer;
}

/**
 * Initialize the fonts.
 */
static void init_fonts() {
  font_thin = fonts_load_custom_font(
    resource_get_handle(RESOURCE_ID_FONT_ARIAL_26));
  font_thick = fonts_load_custom_font(
    resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_28));
}

/**
 * Initialize the text layers
 */
static void init_text_layers() {
  int y = 30;
  int h = 30;
  int left = 2;
  int top = 30;
  int width = 144;
  Layer *window_layer = window_get_root_layer(window);
  rellotge.quarts = create_clock_text_layer(window_layer, font_thin,
    left, top, width, h+3);
  rellotge.quarts_extra = create_clock_text_layer(window_layer, font_thin,
    left, top + h, width, h+3);
  rellotge.article = create_clock_text_layer(window_layer, font_thin,
    left, top + 2*h, width, h+3);
  rellotge.hores = create_clock_text_layer(window_layer, font_thick,
    left, top + 2*h - 2, width, h+3);
  rellotge.hores_extra = create_clock_text_layer(window_layer, font_thin,
    left, top + 3*h, width, h+3);
}

/**
 * Update the position of the hours layer so that it matches with the position
 * of the article.
 */
void update_layer_position() {
  Layer *layer = text_layer_get_layer(rellotge.hores);
  GRect frame = layer_get_frame(layer);
  frame.origin.x = 2 + temps.mida_article;
  layer_set_frame(layer, frame);
}

/**
 * Update the clock with the current values in the temps structure.
 */
void update_clock() {
  update_layer_position();
  text_layer_set_text(rellotge.quarts, temps.quarts);
  text_layer_set_text(rellotge.quarts_extra, temps.quarts_extra);
  text_layer_set_text(rellotge.hores, temps.hores);
  text_layer_set_text(rellotge.hores_extra, temps.hores_extra);
  text_layer_set_text(rellotge.article, temps.article);
}

/**
 * Initialize the clock fonts and layers
 */
void init_clock() {
  init_fonts();
  init_text_layers();
}

/**
 * Destroy the clock fonts and layers.
 */
void destroy_clock() {
  text_layer_destroy(rellotge.quarts);
  text_layer_destroy(rellotge.quarts_extra);
  text_layer_destroy(rellotge.hores);
  text_layer_destroy(rellotge.hores_extra);
  text_layer_destroy(rellotge.article);
}

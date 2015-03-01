/**
 * L'hora en català
 *
 * Struct that contains the text layers in the clock.
 *
 * Pebble SDK 2.0
 * GPL v3
 * Copyright dev@oscarvilaplana.cat
 **/
typedef struct {
  TextLayer *quarts;
  TextLayer *quarts_extra;
  TextLayer *article;
  TextLayer *hores;
  TextLayer *hores_extra;
} rellotge_t;

/**
 * L'hora en català
 *
 * Structure to store the time representation.
 *
 * Pebble SDK 2.0
 * GPL v3
 * Copyright dev@oscarvilaplana.cat
 **/

typedef struct {
    const char *quarts;
    const char *quarts_extra;
    const char *article;
    const char *hores;
    const char *hores_extra;
    int mida_article;
} temps_t;

void update_temps(struct tm *tick_time);

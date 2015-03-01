/**
 * L'hora en català
 *
 * Translate time to catalan time description
 * and update the global temps struct.
 *
 * Pebble SDK 2.0
 * GPL v3
 * Copyright dev@oscarvilaplana.cat
 **/

#include <pebble.h>
#include "./hores.h"

temps_t temps;

/**
 * Map hours to hour names.
 */
static const char *string_hores[] = {
    "",
    "una",
    "dues",
    "tres",
    "quatre",
    "cinc",
    "sis",
    "set",
    "vuit",
    "nou",
    "deu",
    "onze",
    "dotze"
};

/**
 * Map minutes to the first quarters string
 */
static const char *string_quarts[] = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "cinc min per",
    "cinc min per",
    "vora",
    "vora",
    "vora",
    "gairebé",
    "",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "cinc min per",
    "cinc min per",
    "cinc min per",
    "vora",
    "vora",
    "gairebé",
    "",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "cinc min per",
    "cinc min per",
    "cinc min per",
    "vora",
    "vora",
    "gairebé",
    "",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "",
    "",
    "",
    "",
    "",
    ""
};

/**
 * Map minutes to second quarters string
 */
static const char *string_quarts_extra[] = {
    "",
    "",
    "",
    "",
    "gairebé",
    "",
    "",
    "mig quart",
    "mig quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "un quart",
    "tocat",
    "tocat",
    "ben tocat",
    "i cinc",
    "i cinc",
    "i cinc",
    "i mig",
    "i mig",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "dos quarts",
    "tocats",
    "tocats",
    "ben tocats",
    "i cinc",
    "i cinc",
    "i cinc",
    "i mig",
    "i mig",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tres quarts",
    "tocats",
    "tocats",
    "ben tocats",
    "i cinc",
    "i cinc",
    "i cinc",
    "i mig",
    "i mig",
    "cinc min per",
    "cinc min per",
    "cinc min per",
    "vora",
    "vora",
    "gairebé"
};

/**
 * Update the global temps structure with the
 * time description according to the value in tick_time.
 *
 * @param tick_time time to show on the clock
 */
void update_temps(struct tm *tick_time) {
    int hour = tick_time->tm_hour;
    int min = tick_time->tm_min;

    temps.quarts = string_quarts[min];
    temps.quarts_extra = string_quarts_extra[min];
    if (min >= 7) {
        hour = (hour + 1);
    }
    hour = hour % 12;
    if (hour == 0) hour = 12;
    temps.hores = string_hores[hour];
    int de = (min >=7 && min < 54);
    if (de) {
        if (hour == 1 || hour == 11) {
            temps.article = "d'";
            temps.mida_article = 20;
        } else {
            temps.article = "de";
            temps.mida_article = 35;
        }
    } else {
        if (hour == 1) {
            temps.article = "la";
            temps.mida_article = 26;
        } else {
            temps.article = "les";
            temps.mida_article = 40;
        }
    }
    if (min == 1 || min == 2) {
        if (hour == 1) {
            temps.hores_extra = "tocada";
        } else {
            temps.hores_extra = "tocades";
        }
    } else if (min == 3) {
        if (hour == 1) {
            temps.hores_extra = "ben tocada";
        } else {
            temps.hores_extra = "ben tocades";
        }
    } else if (min >= 4 && min <= 6) {
        temps.hores_extra = "i cinc";
    } else {
        temps.hores_extra = "";
    }
}

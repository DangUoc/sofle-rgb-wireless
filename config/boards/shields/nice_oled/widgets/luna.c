/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/wpm.h>

#include "luna.h"

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

LV_IMG_DECLARE(lizard_logo);

struct luna_wpm_status_state {
    uint8_t wpm;
};

void luna_wpm_status_update_cb(struct luna_wpm_status_state state) {
    // Static logo, do nothing on WPM change
}

struct luna_wpm_status_state luna_wpm_status_get_state(const zmk_event_t *eh) {
    return (struct luna_wpm_status_state){.wpm = 0};
};

ZMK_DISPLAY_WIDGET_LISTENER(widget_luna, struct luna_wpm_status_state, luna_wpm_status_update_cb,
                            luna_wpm_status_get_state)

ZMK_SUBSCRIPTION(widget_luna, zmk_wpm_state_changed);

int zmk_widget_luna_init(struct zmk_widget_luna *widget, lv_obj_t *parent) {
    widget->obj = lv_img_create(parent);
    lv_img_set_src(widget->obj, &lizard_logo);

    sys_slist_append(&widgets, &widget->node);

    widget_luna_init();

    return 0;
}

lv_obj_t *zmk_widget_luna_obj(struct zmk_widget_luna *widget) { return widget->obj; }

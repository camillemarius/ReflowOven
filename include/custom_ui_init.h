#ifndef UI_INIT_H
#define UI_INIT_H

#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include "ui/ui.h"
#include "ui_init.h"

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void initCustomLVGL();

#endif
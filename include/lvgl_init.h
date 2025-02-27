#ifndef LVGL_INIT_H
#define LVGL_INIT_H

#include <lvgl.h>


/* Change to your screen resolution */

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void initCustomLVGL();

#endif
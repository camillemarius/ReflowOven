
/* Includes ------------------------------------------------------------------*/
#include "lvgl_init.h"

#include <Arduino_GFX_Library.h>
#include "ui/ui.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define TFT_BL 2

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);

//  ST7262 IPS LCD 800x480
Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
    bus,
    800 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 8 /* hsync_back_porch */,
    480 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 8 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 14000000 /* prefer_speed */, true /* auto_flush */);

    
#include "touch.h"
/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    // Allocate only if needed
    lv_color_t *rotated_buffer = (lv_color_t *)heap_caps_malloc(w * h * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    if (!rotated_buffer) {
        //Serial.println("Memory allocation failed!");
        lv_disp_flush_ready(disp);
        return;
    }

    // Rotate manually 270° (swap x and y)
    for (uint32_t y = 0; y < h; y++) {
        for (uint32_t x = 0; x < w; x++) {
            rotated_buffer[x * h + (h - 1 - y)] = color_p[y * w + x];
        }
    }

    // Draw rotated image
#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(800 - area->y2 - 1, area->x1, (uint16_t *)rotated_buffer, h, w);
#else
    gfx->draw16bitRGBBitmap(800 - area->y2 - 1, area->x1, (uint16_t *)rotated_buffer, h, w);
#endif

    free(rotated_buffer); // Free memory
    lv_disp_flush_ready(disp); // Notify LVGL
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void initCustomLVGL() {
    gfx->begin();
   
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
  
    gfx->fillScreen(BLACK);
    delay(500);
  
    lv_init();
    delay(10);
    touch_init();
    screenWidth = gfx->width();
    screenHeight = gfx->height();
  
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  
    if (!disp_draw_buf)
    {
      gfx->fillScreen(RED);
      delay(500);
    }
    else
    {
      lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 4);
      /* Initialize the display */
      lv_disp_drv_init(&disp_drv);
      /* Change the following line to your display resolution */
      disp_drv.hor_res = screenWidth;// screenWidth;
      disp_drv.ver_res = screenHeight;
      disp_drv.flush_cb = my_disp_flush;
      disp_drv.draw_buf = &draw_buf;
  
      // Set screen Roation
      lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
      lv_disp_set_rotation(disp,LV_DISP_ROT_270);
  
      /* Initialize the (dummy) input device driver */
      static lv_indev_drv_t indev_drv;
      lv_indev_drv_init(&indev_drv);
      indev_drv.type = LV_INDEV_TYPE_POINTER;
      indev_drv.read_cb = my_touchpad_read;
      lv_indev_drv_register(&indev_drv);
    }
  }
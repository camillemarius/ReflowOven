#include <Arduino.h> /* for platformio only */
#include "profile_management.h"

#include "temperatur_sensor.h"
#include "custom_ui.h"
#include "pid.h"
/*******************************************************************************
 * LVGL Widgets
 * This is a widgets demo for LVGL - Light and Versatile Graphics Library
 * import from: https://github.com/lvgl/lv_demos.git
 *
 * Dependent libraries:
 * LVGL: https://github.com/lvgl/lvgl.git

 * Touch libraries:
 * FT6X36: https://github.com/strange-v/FT6X36.git
 * GT911: https://github.com/TAMCTec/gt911-arduino.git
 * XPT2046: https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
 *
 * LVGL Configuration file:
 * Copy your_arduino_path/libraries/lvgl/lv_conf_template.h
 * to your_arduino_path/libraries/lv_conf.h
 * Then find and set:
 * #define LV_COLOR_DEPTH     16
 * #define LV_TICK_CUSTOM     1
 *
 * For SPI display set color swap can be faster, parallel screen don't set!
 * #define LV_COLOR_16_SWAP   1
 *
 * Optional: Show CPU usage and FPS count
 * #define LV_USE_PERF_MONITOR 1
 ******************************************************************************/
//#include "lv_demo_widgets.h"
#include <lvgl.h>
//#include <demos/lv_demos.h>
/*******************************************************************************
 * 
 ******************************************************************************/
#include <Arduino_GFX_Library.h>
#include "ui/ui.h"
#define TFT_BL 2
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

//----------------------------------------------------TEST CCH
//const int PIN_SCK = 12; //FSPICLK
//const int PIN_SO = 13; //FSPIQ
//const int PIN_CS = 11; //FSPICSO // 10
//----------------------------------------------------TEST CCH

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

#include "touch/touch.h"

/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

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

void setup()
{
  //Serial.begin(115200);
  //while (!Serial);
  //Serial.println("LVGL Widgets Demo");

  // Init touch device

  // Init Display
  gfx->begin();
  //gfx->setRotation(3);
 
#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
#endif
  //gfx->fillScreen(RED);
  //delay(500);
  //gfx->fillScreen(GREEN);
  //delay(500);
  //gfx->fillScreen(BLUE);
  //delay(500);
  //gfx->fillScreen(RED);
  //delay(500);
  gfx->fillScreen(BLACK);
  delay(500);
  //gfx->fillScreen(BLUE);
  //delay(500);
  //gfx->fillScreen(BLACK);
  //delay(500);
  //gfx->fillScreen(BLUE);
  //delay(500);
  //gfx->fillScreen(BLACK);
  //delay(500);
  lv_init();
  delay(10);
  touch_init();
  screenWidth = gfx->width();
  screenHeight = gfx->height();

#ifdef ESP32
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4);
#endif
  if (!disp_draw_buf)
  {
    gfx->fillScreen(RED);
    delay(500);
    //Serial.println("LVGL disp_draw_buf allocate failed!");
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

    // CCH; Rotate UI by 270°
    //disp_drv.sw_rotate = 1;
    //disp_drv.rotated = LV_DISP_ROT_180;  
    //disp_drv.full_refresh = 1;  // full_refresh must be 1

    //lv_disp_drv_register(&disp_drv);
    
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
    lv_disp_set_rotation(disp,LV_DISP_ROT_270);

    //if (disp_drv.rotated == (LV_DISP_ROT_90 || LV_DISP_ROT_180)) {
    //  disp_drv.hor_res = screenHeight;
    //  disp_drv.ver_res = screenWidth;
    //}
  


    /* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    (void) loadProfiles();
    
    ui_init();


    //----------------------------------------------------TEST CCH
    //pinMode(PIN_SCK, OUTPUT);  // Set pin 12 as output
    //digitalWrite(PIN_SCK, LOW); // Start with LOW
    
    //pinMode(PIN_SO, OUTPUT);  // Set pin 12 as output
    //digitalWrite(PIN_SO, LOW); // Start with LOW
    
    //pinMode(PIN_CS, OUTPUT);  // Set pin 12 as output
    //digitalWrite(PIN_CS, LOW); // Start with LOW
    //----------------------------------------------------TEST CCH
  }
}



void loop() {
  static unsigned long last_gui_update = 0;
  static unsigned long last_temp_update = 0;
  const uint32_t GUI_UPDATE_INTERVAL = 10;  // Update GUI every 10ms
  const uint32_t TEMP_UPDATE_INTERVAL = 1000; // Update temperature every 1000ms

  unsigned long current_time = millis();

  // Handle GUI updates
  if (current_time - last_gui_update >= GUI_UPDATE_INTERVAL) {
    lv_timer_handler(); 
    last_gui_update = current_time;
  }

  // Handle temperature updates
  if (current_time - last_temp_update >= TEMP_UPDATE_INTERVAL) {
    //if(startReflowProcess == true) {
    float temp = getTemperatur();

    // Convert float to string only when needed
    static float last_temp = -1000; // Ensure initial update
    if (temp != last_temp) {
      char temp_str[10];  
      snprintf(temp_str, sizeof(temp_str), "%.1f°C", temp);
      lv_label_set_text(ui_LaActualTemperature, temp_str);
      last_temp = temp;
    }
    drawTemperaturePoint(temp);
    //}
    

    //checkTemperature();
    //----------------------------------------------------TEST CCH
    //char temp_str[15];  
    //snprintf(temp_str, sizeof(temp_str), "PIN_SCK: %d", digitalRead(PIN_SCK));
    //lv_label_set_text(ui_LabelPreheat5, temp_str);

    //snprintf(temp_str, sizeof(temp_str), "PIN_SO: %d", digitalRead(PIN_SO));
    //lv_label_set_text(ui_LabelPreheat6, temp_str);

    //digitalWrite(PIN_SCK, !digitalRead(PIN_SCK));  // Toggle state
    //digitalWrite(PIN_SO, !digitalRead(PIN_SO));  // Toggle state
    //digitalWrite(PIN_CS, !digitalRead(PIN_CS));  // Toggle state
    //----------------------------------------------------TEST CCH

    last_temp_update = current_time;
  }

  delay(5);
}

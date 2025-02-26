// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Load_Profile
void ui_Load_Profile_screen_init(void);
void ui_event_Load_Profile(lv_event_t * e);
extern lv_obj_t * ui_Load_Profile;
extern lv_obj_t * ui_Panel14;
extern lv_obj_t * ui_Image6;
extern lv_obj_t * ui_Label4;
void ui_event_BuCloseLoadProfile(lv_event_t * e);
extern lv_obj_t * ui_BuCloseLoadProfile;
extern lv_obj_t * ui_Panel39;
extern lv_obj_t * ui_PanelProfile1;
extern lv_obj_t * ui_PanelPreheat2;
extern lv_obj_t * ui_LabelPreheat20;
extern lv_obj_t * ui_laProfile1;
extern lv_obj_t * ui_Panel41;
void ui_event_BuSettingsProfile1(lv_event_t * e);
extern lv_obj_t * ui_BuSettingsProfile1;
void ui_event_BuSelectProfile1(lv_event_t * e);
extern lv_obj_t * ui_BuSelectProfile1;
void ui_event_Label34(lv_event_t * e);
extern lv_obj_t * ui_Label34;
extern lv_obj_t * ui_PanelProfile2;
extern lv_obj_t * ui_PanelPreheat1;
extern lv_obj_t * ui_LabelPreheat2;
extern lv_obj_t * ui_laProfile2;
extern lv_obj_t * ui_Panel26;
void ui_event_BuSettingsProfile2(lv_event_t * e);
extern lv_obj_t * ui_BuSettingsProfile2;
void ui_event_BuSelectProfile2(lv_event_t * e);
extern lv_obj_t * ui_BuSelectProfile2;
extern lv_obj_t * ui_Label10;
extern lv_obj_t * ui_PanelProfile3;
extern lv_obj_t * ui_PanelPreheat3;
extern lv_obj_t * ui_LabelPreheat21;
extern lv_obj_t * ui_laProfile3;
extern lv_obj_t * ui_Panel43;
void ui_event_BuSettingsProfile3(lv_event_t * e);
extern lv_obj_t * ui_BuSettingsProfile3;
void ui_event_BuSelectProfile3(lv_event_t * e);
extern lv_obj_t * ui_BuSelectProfile3;
extern lv_obj_t * ui_Label13;
extern lv_obj_t * ui_PanelProfile4;
extern lv_obj_t * ui_PanelPreheat4;
extern lv_obj_t * ui_LabelPreheat22;
extern lv_obj_t * ui_laProfile4;
extern lv_obj_t * ui_Panel45;
void ui_event_BuSettingsProfile4(lv_event_t * e);
extern lv_obj_t * ui_BuSettingsProfile4;
void ui_event_BuSelectProfile4(lv_event_t * e);
extern lv_obj_t * ui_BuSelectProfile4;
extern lv_obj_t * ui_Label8;
extern lv_obj_t * ui_PanelProfile5;
extern lv_obj_t * ui_PanelPreheat10;
extern lv_obj_t * ui_LabelPreheat23;
extern lv_obj_t * ui_laProfile5;
extern lv_obj_t * ui_Panel47;
void ui_event_BuSettingsProfile5(lv_event_t * e);
extern lv_obj_t * ui_BuSettingsProfile5;
void ui_event_BuSelectProfile5(lv_event_t * e);
extern lv_obj_t * ui_BuSelectProfile5;
extern lv_obj_t * ui_Label11;
// CUSTOM VARIABLES
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;

// SCREEN: ui_Reflow_Oven
void ui_Reflow_Oven_screen_init(void);
extern lv_obj_t * ui_Reflow_Oven;
extern lv_obj_t * ui_Panel6;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_LaMenuTitle;
extern lv_obj_t * ui_Chart1;
extern lv_obj_t * ui_LaActualTemperature;
extern lv_obj_t * ui_Panel3;
extern lv_obj_t * ui_PanelPreheat5;
extern lv_obj_t * ui_LabelPreheat5;
extern lv_obj_t * ui_laPreheatTempRise;
extern lv_obj_t * ui_Panel4;
extern lv_obj_t * ui_Panel5;
extern lv_obj_t * ui_LaPreheatStatus;
extern lv_obj_t * ui_ImPreheatStatus;
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_PanelPreheat6;
extern lv_obj_t * ui_LabelPreheat6;
extern lv_obj_t * ui_laSoakTemp;
extern lv_obj_t * ui_laSoakDur;
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui_LaSoakStatus;
extern lv_obj_t * ui_ImSoakStatus;
extern lv_obj_t * ui_Panel7;
extern lv_obj_t * ui_PanelPreheat7;
extern lv_obj_t * ui_LabelPreheat7;
extern lv_obj_t * ui_laRampPeakTempRise;
extern lv_obj_t * ui_Panel8;
extern lv_obj_t * ui_LaRampPeakStatus;
extern lv_obj_t * ui_ImRampPeakStatus;
extern lv_obj_t * ui_Panel9;
extern lv_obj_t * ui_PanelPreheat8;
extern lv_obj_t * ui_LabelPreheat8;
extern lv_obj_t * ui_laReflowTemp;
extern lv_obj_t * ui_laReflowDur;
extern lv_obj_t * ui_Panel10;
extern lv_obj_t * ui_LaReflowStatus;
extern lv_obj_t * ui_ImReflowStatus;
extern lv_obj_t * ui_Panel11;
extern lv_obj_t * ui_PanelPreheat9;
extern lv_obj_t * ui_LabelPreheat9;
extern lv_obj_t * ui_laCooldownTemp;
extern lv_obj_t * ui_laCooldownDur;
extern lv_obj_t * ui_Panel12;
extern lv_obj_t * ui_LaCooldownStatus;
extern lv_obj_t * ui_ImCooldownStatus;
extern lv_obj_t * ui_Panel13;
void ui_event_BuStartReflow(lv_event_t * e);
extern lv_obj_t * ui_BuStartReflow;
extern lv_obj_t * ui_BuStartReflowText;
void ui_event_BuNewProfile(lv_event_t * e);
extern lv_obj_t * ui_BuNewProfile;
extern lv_obj_t * ui_Label7;
void ui_event_BuLoadProfile(lv_event_t * e);
extern lv_obj_t * ui_BuLoadProfile;
extern lv_obj_t * ui_Label5;
// CUSTOM VARIABLES
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;
extern lv_obj_t * uic_Panel1;

// SCREEN: ui_New_Profile
void ui_New_Profile_screen_init(void);
extern lv_obj_t * ui_New_Profile;
extern lv_obj_t * ui_Panel38;
extern lv_obj_t * ui_Image10;
extern lv_obj_t * ui_Label3;
void ui_event_BuCloseNewProfile(lv_event_t * e);
extern lv_obj_t * ui_BuCloseNewProfile;
extern lv_obj_t * ui_Panel15;
extern lv_obj_t * ui_Panel37;
extern lv_obj_t * ui_Panel16;
extern lv_obj_t * ui_Label2;
void ui_event_taProfileName(lv_event_t * e);
extern lv_obj_t * ui_taProfileName;
extern lv_obj_t * ui_Panel32;
extern lv_obj_t * ui_Panel17;
extern lv_obj_t * ui_LabelPreheat1;
extern lv_obj_t * ui_Panel18;
extern lv_obj_t * ui_LabelPreheat3;
void ui_event_taPreheatTempRise(lv_event_t * e);
extern lv_obj_t * ui_taPreheatTempRise;
extern lv_obj_t * ui_Panel33;
extern lv_obj_t * ui_Panel25;
extern lv_obj_t * ui_LabelPreheat14;
extern lv_obj_t * ui_Panel21;
extern lv_obj_t * ui_LabelPreheat4;
void ui_event_taSoakTemp(lv_event_t * e);
extern lv_obj_t * ui_taSoakTemp;
extern lv_obj_t * ui_Panel22;
extern lv_obj_t * ui_LabelPreheat10;
void ui_event_taSoakDur(lv_event_t * e);
extern lv_obj_t * ui_taSoakDur;
extern lv_obj_t * ui_Panel34;
extern lv_obj_t * ui_Panel27;
extern lv_obj_t * ui_LabelPreheat15;
extern lv_obj_t * ui_Panel20;
extern lv_obj_t * ui_LabelPreheat11;
void ui_event_taRampUpTempRise(lv_event_t * e);
extern lv_obj_t * ui_taRampUpTempRise;
extern lv_obj_t * ui_Panel35;
extern lv_obj_t * ui_Panel28;
extern lv_obj_t * ui_LabelPreheat16;
extern lv_obj_t * ui_Panel23;
extern lv_obj_t * ui_LabelPreheat12;
void ui_event_taReflowTemp(lv_event_t * e);
extern lv_obj_t * ui_taReflowTemp;
extern lv_obj_t * ui_Panel24;
extern lv_obj_t * ui_LabelPreheat13;
void ui_event_taReflowDur(lv_event_t * e);
extern lv_obj_t * ui_taReflowDur;
extern lv_obj_t * ui_Panel36;
extern lv_obj_t * ui_Panel29;
extern lv_obj_t * ui_LabelPreheat17;
extern lv_obj_t * ui_Panel30;
extern lv_obj_t * ui_LabelPreheat18;
void ui_event_taCooldownTemp(lv_event_t * e);
extern lv_obj_t * ui_taCooldownTemp;
extern lv_obj_t * ui_Panel31;
extern lv_obj_t * ui_LabelPreheat19;
void ui_event_taCooldownDur(lv_event_t * e);
extern lv_obj_t * ui_taCooldownDur;
void ui_event_Keyboard2(lv_event_t * e);
extern lv_obj_t * ui_Keyboard2;
// CUSTOM VARIABLES

// EVENTS

extern lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS
LV_IMG_DECLARE(ui_img_fire_png);    // assets/fire.png
LV_IMG_DECLARE(ui_img_close_png);    // assets/close.png
LV_IMG_DECLARE(ui_img_settings_png);    // assets/settings.png
LV_IMG_DECLARE(ui_img_check_png);    // assets/check.png
LV_IMG_DECLARE(ui_img_running_png);    // assets/running.png
LV_IMG_DECLARE(ui_img_watch3_png);    // assets/watch3.png
LV_IMG_DECLARE(ui_img_settings2_png);    // assets/settings2.png
LV_IMG_DECLARE(ui_img_watch2_png);    // assets/watch2.png

// UI INIT
void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

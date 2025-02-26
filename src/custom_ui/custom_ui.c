#include "custom_ui.h"
#include "profile_management.h"
#include "ui/ui.h"

lv_obj_t* chart;
static lv_chart_series_t* ui_Chart1_series_1;
static lv_chart_series_t* ui_Chart1_series_2;



//---------------------------------------------------------------------------------
//-- CHART
//---------------------------------------------------------------------------------
void initChart(void) {
    // Create and configure the chart
    chart = ui_Chart1;
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR); // Ensure circular update
    lv_chart_set_point_count(chart, 700); // Set a default max number of points

    // Set chart range (adjust later dynamically)
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 300);

    // Create the series once during initialization
    ui_Chart1_series_1 = lv_chart_add_series(chart, lv_color_hex(0x1879FB), LV_CHART_AXIS_PRIMARY_Y);
    ui_Chart1_series_2 = lv_chart_add_series(chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
}

void addTemperatureProfileToChart(ReflowProfile reflowProfile) {
	// Setup default graph (Chart)
	
	//lv_obj_t* chart = ui_Chart1;
	//static lv_chart_series_t* ui_Chart1_series_1; // Declare the series
	//static lv_coord_t time_steps[700];  // 7 steps to match the reflow profile stages

	// 📌 Gesamtzeit des Reflow-Profils berechnen
	int TOTAL_SECONDS = 0;
	TOTAL_SECONDS += (reflowProfile.soak_temp - 25) / reflowProfile.preheat_tempRise; // Preheat
	TOTAL_SECONDS += reflowProfile.soak_duration; // Soak
	TOTAL_SECONDS += (reflowProfile.reflow_temp - reflowProfile.soak_temp) / reflowProfile.rampPeak_TempRise; // Ramp to Peak
	TOTAL_SECONDS += reflowProfile.reflow_duration; // Reflow
	TOTAL_SECONDS += reflowProfile.cooldown_duration; // Cooldown
	TOTAL_SECONDS += 1; // Sicherheitspuffer

	
    lv_chart_set_point_count(ui_Chart1, TOTAL_SECONDS);

	
	lv_coord_t* temp_values = (lv_coord_t*)malloc(TOTAL_SECONDS * sizeof(lv_coord_t));
	if (temp_values == NULL) {
		// Handle allocation failure
	}

	// Startwerte setzen
    //time_steps[0] = 0;
    temp_values[0] = 25;  // Umgebungstemperatur (typisch 25°C)
    int index = 1;

    // 🔥 Preheat-Phase (Aufheizen auf Soak-Temperatur)
    int preheat_steps = (reflowProfile.soak_temp - temp_values[0]) / reflowProfile.preheat_tempRise;
    for (int i = 0; i < preheat_steps; i++) {
        //time_steps[index] = time_steps[index - 1] + 1;
        temp_values[index] = temp_values[index - 1] + reflowProfile.preheat_tempRise;
        index++;
    }

    // 🌡 Soak-Phase (Temperatur halten)
    for (int i = 0; i < reflowProfile.soak_duration; i++) {
        //time_steps[index] = time_steps[index - 1] + 1;
        temp_values[index] = reflowProfile.soak_temp;
        index++;
    }

    // 🚀 Ramp to Peak (Anstieg zur Reflow-Temperatur)
    int rampPeak_steps = (reflowProfile.reflow_temp - temp_values[index - 1]) / reflowProfile.rampPeak_TempRise;
    for (int i = 0; i < rampPeak_steps; i++) {
        //time_steps[index] = time_steps[index - 1] + 1;
        temp_values[index] = temp_values[index - 1] + reflowProfile.rampPeak_TempRise;
        index++;
    }

    // 🔥 Reflow-Phase (maximale Temperatur halten)
    for (int i = 0; i < reflowProfile.reflow_duration; i++) {
        //time_steps[index] = time_steps[index - 1] + 1;
        temp_values[index] = reflowProfile.reflow_temp;
        index++;
    }

    // ❄ Cooldown-Phase (Abkühlen)
	double cooldown_temp_steps = (double)(reflowProfile.reflow_temp - reflowProfile.cooldown_temp) / reflowProfile.cooldown_duration;
	double temp_accumulator = temp_values[index - 1];  // Store as floating-point
    for (int i = 0; i < reflowProfile.cooldown_duration && index < TOTAL_SECONDS; i++) {
        //time_steps[index] = time_steps[index - 1] + 1;
        //temp_values[index] = (double) temp_values[index - 1] - cooldown_temp_steps;
		temp_accumulator -= cooldown_temp_steps;  // Apply precise floating-point decrement
    	temp_values[index] = (int)(temp_accumulator + 0.5);  // Use round() function

        if (temp_values[index] < reflowProfile.cooldown_temp) {
            temp_values[index] = reflowProfile.cooldown_temp;
        }
        index++;
    }

    // Falls noch nicht 521 Einträge gefüllt sind, letzte Temperatur übernehmen
    while (index < TOTAL_SECONDS) {
        //time_steps[index] = time_steps[index - 1] + 1;
        temp_values[index] = temp_values[index - 1];
        index++;
    }

	//------------------------------------------------------------------------------------DEBUG
	//char debug_str[50];  // Buffer to hold the string representation
	//snprintf(debug_str, sizeof(debug_str), "time[%d,%d,%d,%d,%d,%d]", time_steps[0],time_steps[1],time_steps[2],time_steps[3],time_steps[4],time_steps[5]);
	//lv_label_set_text(ui_LabelPreheat5, debug_str);
	//------------------------------------------------------------------------------------DEBUG
 
	lv_chart_set_range(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, reflowProfile.reflow_temp + 10);

	// Add data series to the chart
	ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x1879FB), LV_CHART_AXIS_PRIMARY_Y);
	lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, temp_values);
	lv_chart_refresh(ui_Chart1);

	_ui_screen_change(&ui_Reflow_Oven, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Reflow_Oven_screen_init);

	// Free allocated memory
    free(temp_values);
}

void addTemperaturePointToChart(int temp) {
    //static lv_chart_series_t* temp_series = NULL; // Store the series referenc

    if (ui_Chart1_series_2 == NULL) {
        // Create a new series if it doesn't exist
        ui_Chart1_series_2 = lv_chart_add_series(ui_Chart1, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    }

    // Add the new temperature point to the series
    lv_chart_set_next_value(ui_Chart1, ui_Chart1_series_2, temp);

    // Refresh the chart to update the display
    lv_chart_refresh(ui_Chart1);
}

void deleteTemperatureSeries(void) {
    if (ui_Chart1_series_2 != NULL) {
        lv_chart_remove_series(ui_Chart1, ui_Chart1_series_2);
        ui_Chart1_series_2 = NULL;
        lv_chart_refresh(ui_Chart1);
    }
}

//---------------------------------------------------------------------------------
//-- Progress
//---------------------------------------------------------------------------------
void setIconStateBasedOnReflowPhase(ReflowPhases phase) {
    
    const char str_completed[] = "Completed";
    const char str_in_progress[] = "in Progress";
    const char str_pending[] = "Pending";

    switch (phase)
    {
    case IDLE:
        /* code */
        lv_label_set_text(ui_LaPreheatStatus, str_completed);
        lv_label_set_text(ui_LaSoakStatus, str_completed);
        lv_label_set_text(ui_LaRampPeakStatus, str_completed);
        lv_label_set_text(ui_LaReflowStatus, str_completed);
        lv_label_set_text(ui_LaCooldownStatus, str_completed);

        lv_img_set_src(ui_ImPreheatStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImSoakStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImRampPeakStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImReflowStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImCooldownStatus,&ui_img_check_png);

    break;


    case PREHEAT:
        /* code */
	    lv_label_set_text(ui_LaPreheatStatus, str_in_progress);
	    lv_label_set_text(ui_LaSoakStatus, str_pending);
	    lv_label_set_text(ui_LaRampPeakStatus, str_pending);
	    lv_label_set_text(ui_LaReflowStatus, str_pending);
	    lv_label_set_text(ui_LaCooldownStatus, str_pending);

        lv_img_set_src(ui_ImPreheatStatus,&ui_img_running_png);
        lv_img_set_src(ui_ImSoakStatus,&ui_img_watch3_png);
        lv_img_set_src(ui_ImRampPeakStatus,&ui_img_watch3_png);
        lv_img_set_src(ui_ImReflowStatus,&ui_img_watch3_png);
        lv_img_set_src(ui_ImCooldownStatus,&ui_img_watch3_png);
    break;

        
    case SOAK:
    /* code */
	    lv_label_set_text(ui_LaPreheatStatus, str_completed);
	    lv_label_set_text(ui_LaSoakStatus, str_in_progress);
	    lv_label_set_text(ui_LaRampPeakStatus, str_pending);
	    lv_label_set_text(ui_LaReflowStatus, str_pending);
	    lv_label_set_text(ui_LaCooldownStatus, str_pending);

        lv_img_set_src(ui_ImPreheatStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImSoakStatus,&ui_img_running_png);
        lv_img_set_src(ui_ImRampPeakStatus,&ui_img_watch3_png);
        lv_img_set_src(ui_ImReflowStatus,&ui_img_watch3_png);
        lv_img_set_src(ui_ImCooldownStatus,&ui_img_watch3_png);
    break;

    
    case RAMPPEAK:
        /* code */
	    lv_label_set_text(ui_LaPreheatStatus, str_completed);
	    lv_label_set_text(ui_LaSoakStatus, str_completed);
	    lv_label_set_text(ui_LaRampPeakStatus, str_in_progress);
	    lv_label_set_text(ui_LaReflowStatus, str_pending);
	    lv_label_set_text(ui_LaCooldownStatus, str_pending);

        lv_img_set_src(ui_ImPreheatStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImSoakStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImRampPeakStatus,&ui_img_running_png);
        lv_img_set_src(ui_ImReflowStatus,&ui_img_watch3_png);
        lv_img_set_src(ui_ImCooldownStatus,&ui_img_watch3_png);
    break;

        
    case REFLOW:
    /* code */
	    lv_label_set_text(ui_LaPreheatStatus, str_completed);
	    lv_label_set_text(ui_LaSoakStatus, str_completed);
	    lv_label_set_text(ui_LaRampPeakStatus, str_completed);
	    lv_label_set_text(ui_LaReflowStatus, str_in_progress);
	    lv_label_set_text(ui_LaCooldownStatus, str_pending);

        lv_img_set_src(ui_ImPreheatStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImSoakStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImRampPeakStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImReflowStatus,&ui_img_running_png);
        lv_img_set_src(ui_ImCooldownStatus,&ui_img_watch3_png);
    break;
    

    case COOLDOWN:
    /* code */
	    lv_label_set_text(ui_LaPreheatStatus, str_completed);
	    lv_label_set_text(ui_LaSoakStatus, str_completed);
	    lv_label_set_text(ui_LaRampPeakStatus, str_completed);
	    lv_label_set_text(ui_LaReflowStatus, str_completed);
	    lv_label_set_text(ui_LaCooldownStatus, str_in_progress);

        lv_img_set_src(ui_ImPreheatStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImSoakStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImRampPeakStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImReflowStatus,&ui_img_check_png);
        lv_img_set_src(ui_ImCooldownStatus,&ui_img_running_png);
    break;

    default:
        break;
    }
}

void setStartButtonBakgroundColor(bool start) {
    if(start == true) {
        lv_obj_set_style_bg_color(ui_BuStartReflow, lv_color_hex(0xFF0000), LV_PART_MAIN); // Red background
        lv_label_set_text(ui_BuStartReflowText, "Stop");
    }else {
        lv_obj_set_style_bg_color(ui_BuStartReflow, lv_color_hex(0x1879FB), LV_PART_MAIN); // Blue background
        lv_label_set_text(ui_BuStartReflowText, "Start");
    }
}
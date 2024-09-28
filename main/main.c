#include "esp_adc_cal.h"
#include "driver/adc.h"
#include "esp_log.h"
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_sleep.h"

#define DEFAULT_VREF    4200  // Reference voltage in mV (adjust based on your board calibration)
#define ADC_WIDTH       ADC_WIDTH_BIT_13  // 12-bit resolution
#define ADC_ATTEN       ADC_ATTEN_DB_11   // 11dB attenuation (for higher voltage range)
#define ADC_CHANNEL     ADC1_CHANNEL_8    // GPIO14 is ADC1 Channel 6 on ESP32-S2



// Function to read the battery voltage from the ADC
void get_battery_voltage() {
    // Set up ADC configuration
    // adc2_config_width(ADC_WIDTH);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);
    adc1_config_width(ADC_WIDTH);
    // Read raw ADC value
    int raw_out=0;
    int adc_reading = adc1_get_raw(ADC_CHANNEL);
    printf("Raw Batt: %d\n",adc_reading);
    
}

void app_main(void) {
    // Initialize the ADC and log the battery voltage and percentage
    while (1) {
        get_battery_voltage();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
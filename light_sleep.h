#include "esphome.h"
#define LED_BUILTIN GPIO_NUM_13
#define LDO2 GPIO_NUM_21

class LightSleep : public PollingComponent, public Sensor {
 public:
  // constructor
  LightSleep() : PollingComponent(15000) {}

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void setup() override {
    // This will be called by App.setup()
	//pinMode(LED_BUILTIN, OUTPUT);
	//digitalWrite(LED_BUILTIN, HIGH);
    gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_BUILTIN, 1);

	
	
	//pinMode(LDO2, OUTPUT);
	//digitalWrite(LDO2, HIGH);
    gpio_set_direction(LDO2, GPIO_MODE_OUTPUT);
    gpio_set_level(LDO2, 1);

	// wait for a second   
	//esp_sleep_enable_timer_wakeup(3000000); //3 seconds
    esp_sleep_enable_timer_wakeup(900000000); //15 minutes
	int ret = esp_light_sleep_start();
	//digitalWrite(LED_BUILTIN, LOW);
	gpio_set_level(LED_BUILTIN, 0);
  }
  void update() override {
    // This will be called every "update_interval" milliseconds.	
  }
};
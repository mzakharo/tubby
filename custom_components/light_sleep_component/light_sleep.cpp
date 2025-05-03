#include "light_sleep.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h" // Required for App.run_safe_shutdown()
#include "esp_sleep.h"

namespace esphome {
namespace light_sleep_component {

float LightSleepComponent::get_setup_priority() const {
  return setup_priority::HARDWARE;
}

void LightSleepComponent::setup() {
  if (this->ldo_pin_ != nullptr) {
    this->ldo_pin_->setup(); // Setup pin as output
    this->ldo_pin_->digital_write(true); // Set LDO high (assuming high = on) on startup/wake
  }
  esp_sleep_enable_timer_wakeup(this->sleep_duration_us_);
  esp_light_sleep_start();
}

void LightSleepComponent::dump_config() {
}


void LightSleepComponent::on_shutdown() {
   // Delay to allow clean network disconnect etc.
   delay(2000);
 }

} // namespace light_sleep_component
} // namespace esphome

#pragma once
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h" // Include if you later add sensor features

namespace esphome {
namespace light_sleep_component {

// Forward declaration
class LightSleepComponent : public Component {
 public:
  // Constructor
  LightSleepComponent() = default; // Use default constructor

  // --- Configuration setters ---
  void set_sleep_duration(uint64_t duration_us) { this->sleep_duration_us_ = duration_us; }
  void set_ldo_pin(GPIOPin *pin) { this->ldo_pin_ = pin; }

  // --- Component overrides ---
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void on_shutdown() override;

 protected:
  uint64_t sleep_duration_us_{0};
  GPIOPin *ldo_pin_{nullptr}; // Use ESPHome's GPIOPin abstraction
};

} // namespace light_sleep_component
} // namespace esphome

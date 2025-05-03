import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import gpio
from esphome import pins
from esphome.const import (
    CONF_ID,
    CONF_DURATION,
    CONF_PIN,
)

# Declare dépendencies if any (e.g., depends_on=["wifi"])
# DEPENDENCIES = [] # No specific dependencies needed beyond core

# Namespace for the C++ code
light_sleep_component_ns = cg.esphome_ns.namespace("light_sleep_component")

# The C++ class name
LightSleepComponent = light_sleep_component_ns.class_("LightSleepComponent", cg.Component )
# YAML Configuration Schema
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(LightSleepComponent),
        cv.Required(CONF_DURATION): cv.positive_time_period_microseconds, # Sleep duration
        # Optional LDO Control Pin
        cv.Optional("ldo_pin"): pins.gpio_output_pin_schema,

    }
).extend(cv.COMPONENT_SCHEMA) # Extend base component schema

# Code generation function
async def to_code(config):
    # Get the generated ID
    var = cg.new_Pvariable(config[CONF_ID])

    # Register as a component
    await cg.register_component(var, config)
    # Register as a polling component (handles update_interval)
    #await cg.register_polling_component(var, config)


    # Set the sleep duration (converted to microseconds by cv)
    cg.add(var.set_sleep_duration(config[CONF_DURATION]))

    # Handle optional LDO pin
    if "ldo_pin" in config:
        pin = await cg.gpio_pin_expression(config["ldo_pin"])
        cg.add(var.set_ldo_pin(pin))

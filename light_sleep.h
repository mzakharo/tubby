#include "esphome.h"
#define LED_BUILTIN GPIO_NUM_13
#define LDO2 GPIO_NUM_21

#include "../../../../model_fc.h"

#include <tflm_esp32.h>

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/core/api/error_reporter.h"

const int tensor_arena_size = 8000;
uint8_t tensor_arena[tensor_arena_size];

class LightSleep : public PollingComponent, public Sensor
{
public:
  int duration;
  tflite::MicroInterpreter *interpreter;
  TfLiteTensor *model_input;
  // constructor
  LightSleep(int dur) : PollingComponent(15000)
  {
    duration = dur;
  }

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void setup() override
  {
    // This will be called by App.setup()

    const tflite::Model *model = tflite::GetModel(model_fc_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION)
    {
      printf("Model provided is schema version %d not equal "
             "to supported version %d.\n",
             model->version(), TFLITE_SCHEMA_VERSION);
    }
    tflite::AllOpsResolver resolver;
    tflite::ErrorReporter *reporter = new MicroErrorReporter();
    interpreter = new tflite::MicroInterpreter(model, resolver, tensor_arena,
                                               tensor_arena_size, reporter, nullptr, nullptr);
    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk)
    {
      while (1)
      {
        printf("unable to allocate tensors\n");
      }
    }
    model_input = interpreter->input(0);
    if (model_input == nullptr)
    {
      while (1)
      {
        printf("unable to allocate input\n");
      }
    }
    if (model_input->dims->size != 2 || model_input->type != kTfLiteFloat32)
    {
      while (1)
      {
        printf("input mismatch\n");
      }
    }

    // power on sensors
    gpio_set_direction(LDO2, GPIO_MODE_OUTPUT);
    gpio_set_level(LDO2, 1);

    // settle sensors
    esp_sleep_enable_timer_wakeup(duration);
    esp_light_sleep_start();

    // UI
    gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_BUILTIN, 1);
  }
  float predict_ppm(float orp, float ph)
  {
    model_input->data.f[0] = orp;
    model_input->data.f[1] = ph;

    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk)
    {
      printf("Invoke error: status %d\n", invoke_status);
      return -1.0;
    }
    TfLiteTensor *output = interpreter->output(0);
    return output->data.f[0];
  }

  void update() override
  {
    // This will be called every "update_interval" milliseconds.
  }
};
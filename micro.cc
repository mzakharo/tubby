#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "micropython/tfmicro/model_fc.h"
#include <stdio.h>

const int tensor_arena_size = 5000;
uint8_t tensor_arena[tensor_arena_size];

int main() {
  const tflite::Model* model = tflite::GetModel(model_fc_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
        printf("Model provided is schema version %d not equal "
        "to supported version %d.\n",
        model->version(), TFLITE_SCHEMA_VERSION);
  }
  tflite::AllOpsResolver resolver;
  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena,
                                       tensor_arena_size);
  TfLiteStatus allocate_status = interpreter.AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    printf("unable to allocate tensors\n");
    return 1;
  }
  TfLiteTensor* model_input = interpreter.input(0);
  if (model_input == nullptr) {
    printf("unable to allocate input\n");
    return 1;
  }
  if (model_input->dims->size != 2 || model_input->type != kTfLiteFloat32) {
    printf("input mismatch\n");
    return 1;
  }
  model_input->data.f[0] = 700.0;
  model_input->data.f[1] = 7.5;

  TfLiteStatus invoke_status = interpreter.Invoke();
  if (invoke_status != kTfLiteOk) {
      printf("Invoke error: status %d\n", invoke_status);
  }
  TfLiteTensor* output = interpreter.output(0);
  float y = output->data.f[0];
  printf("output %f\n", (double)y);
 
  return 0;
}

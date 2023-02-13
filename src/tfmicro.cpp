#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "model_fc.h"
#include <stdio.h>


extern "C" {
#include <tfmicromodule.h>

const int tensor_arena_size = 3200;
uint8_t * tensor_arena = NULL;

//Function that converts ORP & PH to Free Chlorine (FC)
mp_obj_t fc(mp_obj_t a_obj, mp_obj_t b_obj) {

  const auto a = mp_obj_get_float(a_obj);
  const auto b = mp_obj_get_float(b_obj);

  if (tensor_arena == NULL) {
     tensor_arena = (uint8_t *)malloc(tensor_arena_size);
  }
  if (tensor_arena == NULL) {
    return mp_const_none;
  }

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
    return mp_const_none;
  }

  TfLiteTensor* model_input = interpreter.input(0);
  if (model_input == nullptr) {
    printf("unable to allocate input\n");
    return mp_const_none;
  }

  if (model_input->dims->size != 2 || model_input->type != kTfLiteFloat32) {
     return mp_const_none;
  }

  model_input->data.f[0] = (float)a;
  model_input->data.f[1] = (float)b;

  TfLiteStatus invoke_status = interpreter.Invoke();
  if (invoke_status != kTfLiteOk) {
      printf("Invoke error: status %d\n", invoke_status);
  }
  TfLiteTensor* output = interpreter.output(0);
  float y = output->data.f[0];

  mp_obj_t oy = mp_obj_new_float(y);
  // Prove we're being scanned for QSTRs.
  mp_obj_t tup[] = {oy, MP_ROM_QSTR(MP_QSTR_hellocpp)};
  return mp_obj_new_tuple(2, tup);
}
}

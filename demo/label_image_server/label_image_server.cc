#include <cstdio>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"
#include "tensorflow/lite/builtin_op_data.h"
#include "tensorflow/lite/string_util.h"
#include "model_data.cc"

extern "C" void eapp_print(const char*s, ...);
extern "C" int __main_label_image_server(int* imported_image);
int  __main_label_image_server(int* imported_image){
  // Load model
  std::unique_ptr<tflite::FlatBufferModel> model =
      tflite::FlatBufferModel::BuildFromBuffer((const char *) imported_model, imported_model_size);
  if (!model) {
    eapp_print("Failed to load model!\n");
    return -1;
  }
  eapp_print("Load model successfully!\n");

  // Build the interpreter with the InterpreterBuilder.
  // Note: all Interpreters should be built with the InterpreterBuilder,
  // which allocates memory for the Intrepter and does various set up
  // tasks so that the Interpreter can read the provided model.
  tflite::ops::builtin::BuiltinOpResolver resolver;
  eapp_print("tflite::ops::builtin::BuiltinOpResolver resolver\n");
  tflite::InterpreterBuilder builder(*model, resolver);
  eapp_print("tflite::InterpreterBuilder builder(*model, resolver)\n");
  std::unique_ptr<tflite::Interpreter> interpreter;
  eapp_print("std::unique_ptr<tflite::Interpreter> interpreter\n");
  builder.AddInterpreter(&interpreter);
  eapp_print("builder.AddInterpreter(&interpreter)\n");
  if (!interpreter) {
    eapp_print("Failed to construct interpreter!\n");
    return -1;
  }
  eapp_print("Construct interpreter successfully!\n");

  // Allocate tensor buffers.
  if (interpreter->AllocateTensors() != kTfLiteOk) {
    eapp_print("Failed to allocate tensors!\n");
    return -1;
  }
  eapp_print("=== Pre-invoke Interpreter State ===\n");

  // Fill input buffers
  {
  TfLiteTensor *input_tensor = interpreter->tensor(interpreter->inputs()[0]);
  switch (input_tensor->type) {
  case kTfLiteFloat32: {
    int input0 = interpreter->inputs()[0];

    TfLiteIntArray* dims = interpreter->tensor(input0)->dims;
    int wanted_height = dims->data[1];
    int wanted_width = dims->data[2];
    int wanted_channels = dims->data[3];
    auto number_of_pixels = wanted_height * wanted_width * wanted_channels;

    uint8_t* input = interpreter->typed_tensor<uint8_t>(input0);
    for (int i = 0; i < number_of_pixels; i++) {
      input[i] = imported_image[i] / 255.f;
    }
	  break; 
    }
  case kTfLiteUInt8: {
    int input0 = interpreter->inputs()[0];

    TfLiteIntArray* dims = interpreter->tensor(input0)->dims;
    int wanted_height = dims->data[1];
    int wanted_width = dims->data[2];
    int wanted_channels = dims->data[3];
    auto number_of_pixels = wanted_height * wanted_width * wanted_channels;

    uint8_t* input = interpreter->typed_tensor<uint8_t>(input0);
    for (int i = 0; i < number_of_pixels; i++) {
      input[i] = static_cast<uint8_t>(imported_image[i]);
    }
	  break; 
    }
  }
  }

  // Run inference
  int number_of_warmup_runs = 10;
  for (int i = 0; i < number_of_warmup_runs; i++){
    if (interpreter->Invoke() != kTfLiteOk) {
      eapp_print("Failed to invoke interpreter!\n");
      return -1;
    }
  }

  int loop_count = 10;
  for (int i = 0; i < loop_count; i++){
    if (interpreter->Invoke() != kTfLiteOk) {
      eapp_print("Failed to invoke interpreter!\n");
      return -1;
    }
  }
  eapp_print("=== Post-invoke Interpreter State ===\n");

  // Read output buffers
  TfLiteTensor *output_tensor = interpreter->tensor(interpreter->outputs()[0]);
  unsigned int max = output_tensor->data.uint8[0];
  unsigned int index = 0;
  for(int i = 1; i < 1001; i++){
    if(output_tensor->data.uint8[i] > max){
      max = output_tensor->data.uint8[i];
      index = i;
    }
  }
  return index;
}

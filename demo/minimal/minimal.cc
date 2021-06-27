/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <cstdio>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"
#include "model_data.cc"

// This is an example that is minimal to read a model
// from disk and perform inference. There is no data being loaded
// that is up to you to add as a user.
//
// NOTE: Do not add any dependencies to this that cannot be built with
// the minimal makefile. This example must remain trivial to build with
// the minimal build tool.
//
// Usage: minimal <tflite model>

#define TFLITE_MINIMAL_CHECK(x)                              \
  if (!(x)) {                                                \
    fprintf(stderr, "Error at %s:%d\n", __FILE__, __LINE__); \
    exit(1);                                                 \
  }

extern "C" void eapp_print(const char*s, ...);
extern "C" int __main_minimal();
int __main_minimal() {
  // Load model
  // tflite::Interpreter* test = new tflite::Interpreter();
  // eapp_print(" tflite::Interpreter* test = new tflite::Interpreter()\n");
  std::unique_ptr<tflite::FlatBufferModel> model =
      tflite::FlatBufferModel::BuildFromBuffer((const char *) imported_model, imported_model_size);
  TFLITE_MINIMAL_CHECK(model != nullptr);
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
  // builder(&interpreter);
  eapp_print("builder(&interpreter)\n");
  TFLITE_MINIMAL_CHECK(interpreter != nullptr);
  eapp_print("TFLITE_MINIMAL_CHECK(interpreter != nullptr)\n");

  // Allocate tensor buffers.
  TFLITE_MINIMAL_CHECK(interpreter->AllocateTensors() == kTfLiteOk);
  eapp_print("=== Pre-invoke Interpreter State ===\n");
  tflite::PrintInterpreterState(interpreter.get());

  // Fill input buffers
  // TODO(user): Insert code to fill input tensors.
  // Note: The buffer of the input tensor with index `i` of type T can
  // be accessed with `T* input = interpreter->typed_input_tensor<T>(i);`

  // Run inference
  TFLITE_MINIMAL_CHECK(interpreter->Invoke() == kTfLiteOk);
  eapp_print("=== Post-invoke Interpreter State ===\n");
  tflite::PrintInterpreterState(interpreter.get());

  // Read output buffers
  // TODO(user): Insert getting data out code.
  // Note: The buffer of the output tensor with index `i` of type T can
  // be accessed with `T* output = interpreter->typed_output_tensor<T>(i);`

  return 0;
}

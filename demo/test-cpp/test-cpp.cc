#include "./test-cpp.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

extern "C" void eapp_print(const char*s, ...);
extern "C" int test_cpp();

ErrorReporter* DefaultErrorReporter() {
  ErrorReporter* error_reporter = new ErrorReporter();
  return error_reporter;
}

const char* Father::FindOp(const char* op, int version) const {
  return (char *)"hello";
}
const char* Father::FindOp(int op, int version) const {
  return (char *)"hello";
}

Son::Son(ErrorReporter* error_reporter)
    : error_reporter_(error_reporter ? error_reporter
                                     : DefaultErrorReporter()) {
        eapp_print("this is ErrorReporter son!\n");             
 }

Son::~Son(){

}

void Son::SetExternalContext(int type,
                          char* ctx) {
}

void Son::SetCustomAllocationForTensor(
    int tensor_index, const char& allocation) {

}

void Son::SetInputs(std::vector<int> inputs) {
}

void Son::SetOutputs(std::vector<int> outputs) {
}

void Son::SetVariables(std::vector<int> variables) {
}

void Son::AllocateTensors() {
}

void Son::ReserveNodes(int count) {

}

void Son::AddSubgraphs(int subgraphs_to_add,
                               int* first_new_subgraph_index) {
}

void Son::AddNodeWithParameters(
   const std::vector<int>& inputs,
                                     const std::vector<int>& outputs,
                                     const char* init_data,
                                     size_t init_data_size, void* builtin_data,
                                     const char* registration,
                                     int* node_index) {
}

void Son::ResizeInputTensor(int tensor_index,
                                            const std::vector<int>& dims) {
}

void Son::ResizeInputTensorStrict(
    int tensor_index, const std::vector<int>& dims) {
}

void Son::ReleaseNonPersistentMemory() {
}

void Son::Invoke() {
}

void Son::AddTensors(int tensors_to_add,
                                     int* first_new_tensor_index) {
}

void Son::ResetVariableTensors() {
}

void Son::SetTensorParametersReadOnly(
    int tensor_index, int type, const char* name,
      const std::vector<int>& dims, char* quantization,
      const char* buffer, size_t bytes, const char* allocation) {
}

void Son::SetTensorParametersReadWrite(
    int tensor_index, int type,
                                            const char* name,
                                            const std::vector<int>& dims,
                                            char quantization,
                                            bool is_variable) {
}

void Son::SetTensorParametersReadOnly(
    int tensor_index, int type, const char* name, const size_t rank,
      const int* dims, int quantization,
      const char* buffer, size_t bytes, const char* allocation) {
}

void Son::SetTensorParametersReadWrite(
    int tensor_index, int type, const char* name, const size_t rank,
      const int* dims, int quantization,
      bool is_variable, const size_t rank_dims_signature,
      const int* dims_signature) {
}

void Son::SetExecutionPlan(const std::vector<int>& new_plan) {
}

void Son::SetNumThreads(int num_threads) {

}

void Son::SetAllowFp16PrecisionForFp32(bool allow) {

}
void Son::SetCancellationFunction(void* data,
                                          bool (*check_cancelled_func)(void*)) {
}

bool Son::IsCancelled() { return true; }

void Son::ModifyGraphWithDelegate(TfLiteDelegate* delegate) {
}

void Son::RemoveAllDelegates() {
}

bool Son::HasDelegates() { return true; }

void Son::SetBufferHandle(int tensor_index,
                               char buffer_handle,
                               TfLiteDelegate* delegate) {
}

void Son::GetBufferHandle(int tensor_index,
                               char buffer_handle,
                               TfLiteDelegate** delegate) {
}

void Son::SetProfiler(char* profiler) {
}

void Son::SetProfiler(std::unique_ptr<char*> profiler) {
}

void Son::SetSubgraphProfiler() {
}

char* Son::GetProfiler() {
  return (char*)"hhhhh";
}

void SonBuilder::AddInterpreter(
    std::unique_ptr<Son>* son) {
    son->reset(new Son(error_reporter_));
}

int test_cpp() {
  std::vector<int> myVec;
  myVec.reserve(10);
  eapp_print("myVec.reserve(10);\n");   
  for(int i = 0; i < 300; i++){
    myVec.push_back(1);
  }
  eapp_print("myVec.push_back(1) * 300\n");   
  for(int i = 0; i < 8000; i++){
    myVec.push_back(1);
  }
  return 0;
}

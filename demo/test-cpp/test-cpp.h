#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <map>
#include <stddef.h>
#include <utility>
#include <stdint.h>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <functional>

#include "./common.h"

class ErrorReporter{
 public:
  int a;
};

ErrorReporter* DefaultErrorReporter();

class GrandFather {
 public:
    virtual const char* FindOp(const char* op, int version) const = 0;
    virtual const char* FindOp(int op, int version) const = 0;

    using TfLiteDelegatePtrVector = std::vector<std::unique_ptr<char , void (*)(char*)>>;
    virtual TfLiteDelegatePtrVector GetDelegates(int num_threads) const {
      return TfLiteDelegatePtrVector();
    }

    virtual ~GrandFather() {}
};

class Father : public GrandFather {
public:
  const char* FindOp(const char* op, int version) const override;
  const char* FindOp(int op, int version) const override;
private:
  typedef std::pair<std::string, int> BuiltinOperatorKey;
  typedef std::pair<std::string, int> CustomOperatorKey;

  std::map<BuiltinOperatorKey, char> builtins_;
  std::map<CustomOperatorKey, char> custom_ops_;
};

class SonBuilder;

class Son{
public:
  explicit Son(ErrorReporter* error_reporter  = DefaultErrorReporter());
  ~Son();
  Son(const Son&) = delete;
  Son& operator=(const Son&) = delete;
// private:
//   ErrorReporter* error_reporter_ = nullptr;
#ifndef DOXYGEN_SKIP
  void SetInputs(std::vector<int> inputs);
  void SetOutputs(std::vector<int> outputs);
  void SetVariables(std::vector<int> variables);
  void ReserveNodes(int count);
  void AddNodeWithParameters(const std::vector<int>& inputs,
                                     const std::vector<int>& outputs,
                                     const char* init_data,
                                     size_t init_data_size, void* builtin_data,
                                     const char* registration,
                                     int* node_index = nullptr);
  void AddTensors(int tensors_to_add,
                          int* first_new_tensor_index = nullptr);
  void SetTensorParametersReadOnly(
      int tensor_index, int type, const char* name,
      const std::vector<int>& dims, char* quantization,
      const char* buffer, size_t bytes, const char* allocation = nullptr);
  inline void SetTensorParametersReadOnly(
      int tensor_index, int type, const char* name,
      const std::vector<int>& dims, int quantization,
      const char* buffer, size_t bytes,
      const char* allocation = nullptr) {
    SetTensorParametersReadOnly(tensor_index, type, name, dims.size(),
                                       dims.data(), quantization, buffer, bytes,
                                       allocation);
  }

  void SetTensorParametersReadOnly(
      int tensor_index, int type, const char* name, const size_t rank,
      const int* dims, int quantization,
      const char* buffer, size_t bytes, const char* allocation = nullptr);

  void SetTensorParametersReadWrite(int tensor_index, int type,
                                            const char* name,
                                            const std::vector<int>& dims,
                                            char quantization,
                                            bool is_variable = false);

  inline void SetTensorParametersReadWrite(
      int tensor_index, int  type, const char* name,
      const std::vector<int>& dims, char quantization,
      bool is_variable = false,
      const std::vector<int>* dims_signature = nullptr) {
    size_t rank_dims_signature = 0;
    const int* dims_signature_pointer = nullptr;
    if (dims_signature) {
      rank_dims_signature = dims_signature->size();
      dims_signature_pointer = dims_signature->data();
    }
    SetTensorParametersReadWrite(
        tensor_index, type, name, dims.size(), dims.data(), quantization,
        is_variable, rank_dims_signature, dims_signature_pointer);
  }
  void SetTensorParametersReadWrite(
      int tensor_index, int type, const char* name, const size_t rank,
      const int* dims, int quantization,
      bool is_variable = false, const size_t rank_dims_signature = 0,
      const int* dims_signature = nullptr);
#endif  // DOXYGEN_SKIP
  const char* inputs() const { return (char*)"hhh"; }
  const char* GetInputName(int index) const {
    return (char*)"hhh";
  }
  const char* outputs() const {
    return (char*)"hhh";
  }
  const char* variables() const {
    return (char*)"hhh";
  }
  const char* GetOutputName(int index) const {
    return (char*)"hhh";
  }
  size_t tensors_size() const { return 0; }
  size_t nodes_size() const { return 0; }
  const char* execution_plan() const {
    return (char*)"hhh";
  }

#ifndef DOXYGEN_
  void SetExecutionPlan(const std::vector<int>& new_plan);
#endif  // DOXYGEN_SKIP

  void tensor(int tensor_index) {
  }
  const void tensor(int tensor_index) const {
  }

  const std::pair<char, char>* node_and_registration(
      int node_index) const {
    return NULL;
  }

  template <class T>
  T* typed_tensor(int tensor_index) {
    return nullptr;
  }

  template <class T>
  const T* typed_tensor(int tensor_index) const {
    return nullptr;
  }

  std::vector<const std::string*> signature_def_names() const {
    std::vector<const std::string*> method_names;
    method_names.reserve(signature_defs_.size());
    for (const auto& sig_def : signature_defs_) {
      method_names.emplace_back(&sig_def.method_name);
    }
    return method_names;
  }

  const std::map<std::string, uint32_t>& signature_inputs(
      const char* method_name) const {
    for (const auto& sig_def : signature_defs_) {
      if (sig_def.method_name == method_name) return sig_def.inputs;
    }
    static const std::map<std::string, uint32_t>* default_empty_list =
        new std::map<std::string, uint32_t>();
    return *default_empty_list;
  }

  const std::map<std::string, uint32_t>& signature_outputs(
      const char* method_name) const {
    for (const auto& sig_def : signature_defs_) {
      if (sig_def.method_name == method_name) return sig_def.outputs;
    }
    static const std::map<std::string, uint32_t>* default_empty_list =
        new std::map<std::string, uint32_t>();
    return *default_empty_list;
  }

  void input_tensor_by_signature_name(
      const char* signature_input_name, const char* signature_method_name) {
    const int tensor_index = GetTensorIndexFromSignatureDefName(
        signature_input_name, signature_method_name, /*is_input=*/true);
    
  }

  const void output_tensor_by_signature_name(
      const char* signature_output_name,
      const char* signature_method_name) const {
    const int tensor_index = GetTensorIndexFromSignatureDefName(
        signature_output_name, signature_method_name, /*is_input=*/false);
  
  }

  void input_tensor(size_t index) { }

  const void input_tensor(size_t index) const {

  }

  template <class T>
  T* typed_input_tensor(int index) {
    return typed_tensor<T>(inputs()[index]);
  }

  template <class T>
  const T* typed_input_tensor(int index) const {
    return typed_tensor<T>(inputs()[index]);
  }

  void output_tensor(size_t index) {  }

  const void output_tensor(size_t index) const {

  }

  template <class T>
  T* typed_output_tensor(int index) {
    return typed_tensor<T>(outputs()[index]);
  }

  template <class T>
  const T* typed_output_tensor(int index) const {
    return typed_tensor<T>(outputs()[index]);
  }

  void ResizeInputTensor(int tensor_index,
                                 const std::vector<int>& dims);

  void ResizeInputTensorStrict(int tensor_index,
                                       const std::vector<int>& dims);

  void ReleaseNonPersistentMemory();

  void AllocateTensors();

  void Invoke();

  void SetNumThreads(int num_threads);

  void SetAllowFp16PrecisionForFp32(bool allow);

  bool GetAllowFp16PrecisionForFp32() const {
    return false;
  }

  void SetCancellationFunction(void* data, bool (*check_cancelled_func)(void*));
  void ModifyGraphWithDelegate(TfLiteDelegate* delegate);

 using TfLiteDelegatePtr =
      std::unique_ptr<TfLiteDelegate, void (*)(TfLiteDelegate*)>;

  template <typename Delegate, typename Deleter>
  inline void ModifyGraphWithDelegate(
      std::unique_ptr<Delegate, Deleter> delegate) {
    Deleter deleter = std::move(delegate.get_deleter());

    owned_delegates_.emplace_back(
        delegate.release(), [deleter](TfLiteDelegate* delegate_to_delete) {
          deleter(
              static_cast<typename std::unique_ptr<Delegate, Deleter>::pointer>(
                  delegate_to_delete));
        });
  }

  void ModifyGraphWithDelegate(
      std::unique_ptr<TfLiteDelegate> delegate) = delete;

  void EnsureTensorDataIsReadable(int tensor_index) {
    
  }

  void SetBufferHandle(int tensor_index,
                               char buffer_handle,
                               TfLiteDelegate* delegate);

  void GetBufferHandle(int tensor_index,
                               char buffer_handle,
                               TfLiteDelegate** delegate);

  void SetProfiler(char* profiler);

  void SetProfiler(std::unique_ptr<char*> profiler);

  char* GetProfiler();

  static constexpr int kTensorsReservedCapacity = 128;
  static constexpr int kTensorsCapacityHeadroom = 16;

  void SetAllowBufferHandleOutput(bool allow_buffer_handle_output) {
    allow_buffer_handle_output_ = allow_buffer_handle_output;
  }

  void ResetVariableTensors();

  const char* OpProfilingString(const char& op_reg,
                                const char* node) const {
    return (char*)"hhh";
  }

  void SetExternalContext(int type,
                          char* ctx);

  void SetCustomAllocationForTensor(
      int tensor_index, const char& allocation);

#ifndef DOXYGEN_SKIP
  void AddSubgraphs(int subgraphs_to_add,
                    int* first_new_subgraph_index = nullptr);

  size_t subgraphs_size() const { return 0; }

  char* subgraph(int subgraph_index) {
      return (char*)"hhh";
  }

  void primary_subgraph() {
    
  }

  const void primary_subgraph() const {
  }

  ErrorReporter* error_reporter() const { return error_reporter_; }

#endif  // DOXYGEN_SKIP

 private:
  struct SignatureDef {
    std::map<std::string, uint32_t> inputs;
    std::map<std::string, uint32_t> outputs;
    std::string method_name;
    std::string signature_def_key;
  };
  friend class SonBuilder;

  static void SetExternalContext(struct TfLiteContext* context,
                                 int type,
                                 char* ctx);

  int GetTensorIndexFromSignatureDefName(const char* signature_tensor_name,
                                         const char* signature_method_name,
                                         bool is_input) const {
    for (const auto& signature : signature_defs_) {
      if (signature.method_name != signature_method_name) continue;
      auto& signature_list = (is_input ? signature.inputs : signature.outputs);
      auto tensor_iter = signature_list.find(signature_tensor_name);
      if (tensor_iter == signature_list.end()) return -1;
      return tensor_iter->second;
    }
    return -1;
  }

  void SetSubgraphProfiler();

  void RemoveAllDelegates();

  bool HasDelegates();

  bool IsCancelled();

  void SetSignatureDef(std::vector<SignatureDef> signature_defs) {
    signature_defs_ = std::move(signature_defs);
  }

  TfLiteContext* context_ = nullptr;

  ErrorReporter* error_reporter_ = nullptr;

  std::vector<
      std::unique_ptr<TfLiteDelegate, std::function<void(TfLiteDelegate*)>>>
      owned_delegates_;

  std::unique_ptr<char> owned_profiler_;

  char* installed_profiler_ = nullptr;

  bool allow_buffer_handle_output_ = false;

  char* external_contexts_[20];

  std::unique_ptr<char> own_external_cpu_backend_context_;

  std::vector<std::unique_ptr<char>> subgraphs_;

  std::vector<TfLiteDelegatePtr> lazy_delegate_providers_;

  std::vector<SignatureDef> signature_defs_;
};

class SonBuilder{
public:
  void AddInterpreter(std::unique_ptr<Son>* son);
private:
  ErrorReporter* error_reporter_;
};

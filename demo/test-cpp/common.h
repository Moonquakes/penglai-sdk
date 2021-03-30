#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern "C" {
typedef struct TfLiteDelegate {
  void* data_;
  void (*Prepare)(char* context,
                          struct TfLiteDelegate* delegate);

  void (*CopyFromBufferHandle)(char* context,
                                       struct TfLiteDelegate* delegate,
                                       char buffer_handle,
                                       char* tensor);
  void (*CopyToBufferHandle)(char* context,
                                     struct TfLiteDelegate* delegate,
                                     char buffer_handle,
                                     char* tensor);
  void (*FreeBufferHandle)(char* context,
                           struct TfLiteDelegate* delegate,
                           char* handle);

  int64_t flags;
} TfLiteDelegate;

TfLiteDelegate TfLiteDelegateCreate();
}
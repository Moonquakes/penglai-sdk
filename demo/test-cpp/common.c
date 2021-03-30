#include "./common.h"
TfLiteDelegate TfLiteDelegateCreate() {
  TfLiteDelegate d = {
      .data_ = NULL,
      .Prepare = NULL,
      .CopyFromBufferHandle = NULL,
      .CopyToBufferHandle = NULL,
      .FreeBufferHandle = NULL,
      .flags = NULL,
  };
  return d;
}
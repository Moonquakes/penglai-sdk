#include "eapp.h"
#include "print.h"
#include <string.h>
#include <stdlib.h>
#include "image_data.cc"
#include "labels.cc"

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;

  eapp_print("label image caller begin to run!\n");

  char server_name[16];
  strcpy(server_name, "test-server");
  unsigned long server_handle = acquire_enclave(server_name);
  if(server_handle == -1UL)
  {
    EAPP_RETURN(-1UL);
  }

  unsigned long arg0 = 0x19960000UL;
  unsigned long size = 4*150528;
  int *nums = eapp_mmap(NULL, size);
  for(int i = 0; i < size/sizeof(int); i++)
  {
    nums[i] = imported_image[i];
  }

  struct call_enclave_arg_t call_arg;
  call_arg.req_arg = arg0;
  call_arg.req_vaddr = nums;
  call_arg.req_size = size;

  call_enclave(server_handle, &call_arg);

  int label_index = call_arg.resp_val;
  eapp_print("label image caller: get server retval: %d\n", label_index);
  eapp_print("laber = %s\n", imported_labels[label_index]);
  EAPP_RETURN(0);
}

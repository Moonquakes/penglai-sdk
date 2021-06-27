#include "eapp.h"
#include "print.h"

int EAPP_ENTRY main(){
  unsigned long* args;
  EAPP_RESERVE_REG;
  unsigned long arg0 = args[10];
  void* vaddr = (void*)args[11];
  unsigned long size = args[12];
  eapp_print("label image server begin to run!\n");

  struct call_enclave_arg_t ret_arg;
  int label_index = 0;
  if(vaddr){
    int* imported_image = (int*)vaddr;
    label_index = __main_label_image_server(imported_image);
  }

  ret_arg.req_vaddr = vaddr;
  ret_arg.req_size = size;
  ret_arg.resp_val = label_index;
  eapp_print("label image server is exiting with ret: %d\n", ret_arg.resp_val);
  SERVER_RETURN(&ret_arg);
}

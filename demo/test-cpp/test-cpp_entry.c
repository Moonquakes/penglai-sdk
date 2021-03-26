#include "eapp.h"
#include "print.h"

int EAPP_ENTRY main(){
  unsigned long * args;
  EAPP_RESERVE_REG;
  eapp_print("%s is running\n", "test-cpp");
  test_cpp();
  EAPP_RETURN(0);
}
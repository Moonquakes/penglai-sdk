#include "./test-cpp.h"
#include <stddef.h>
#include <stdint.h>

extern "C" void eapp_print(const char*s, ...);
extern "C" int test_cpp();

size_t CombineHashes(std::initializer_list<size_t> hashes) {
  // size_t result = 0;
  // // Hash combiner used by TensorFlow core.
  // for (size_t hash : hashes) {
  //   result = result ^
  //            (hash + 0x9e3779b97f4a7800ULL + (result << 10) + (result >> 4));
  // }
  // return result;
    return 0;
}

namespace a {
  const char* Father::FindOp(const char* op, int version) const {
    return (char *)"hello";
  }
  const char* Father::FindOp(int op, int version) const {
    return (char *)"hello";
  }
namespace b {
namespace c {
    Son::Son(){
        eapp_print("this is son!\n");
    }

    GrandFather::TfLiteDelegatePtrVector Son::GetDelegates(int num_threads) const {
      GrandFather::TfLiteDelegatePtrVector delegates;
      return delegates;
    }
}
}
}

int test_cpp() {
    a::Father father;
    a::b::c::Son son;
}
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <map>
#include <stddef.h>
#include <utility>

size_t CombineHashes(std::initializer_list<size_t> hashes);

namespace a {

namespace op_resolver_hasher {

template <typename T>
struct OperatorKeyHasher {
  size_t operator()(const T& x) const {
    return 0;
    // size_t a = ValueHasher<typename T::first_type>()(x.first);
    // size_t b = ValueHasher<typename T::second_type>()(x.second);
    // return CombineHashes({a, b});
  }
};
}

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

namespace b {
namespace c {

class Son : public Father {
public:
    Son();
    GrandFather::TfLiteDelegatePtrVector GetDelegates(int num_threads) const override;
};
}
}
}

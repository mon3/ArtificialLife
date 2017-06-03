#include <cassert>
#include <cstdint>
#include <iostream>
using namespace std;

template<typename valtype, valtype minval, valtype maxval>
class ConstrainedValue
{
  valtype val;

  template<typename T> static bool lt(valtype v, T other) {
    if (v <= 0) {
        if (other >= 0) return true;
        else return static_cast<long>(v) <= static_cast<long>(other);
    }
    else {
        if (other <= 0) return false;
        else  return static_cast<unsigned long>(v)
            <= static_cast<unsigned long>(other);
    }
}


template <typename T> static bool checkval (T val)
{
    return lt(minval, val) && (! lt(maxval, val));
}

public:
  ConstrainedValue() : val{minval}
  {
    assert(checkval(val));
  }

  template <typename T>
  ConstrainedValue(T val) : val{val}
  {
    assert(checkval(val));
  }

  template <typename T>
  ConstrainedValue &operator = (T val)
  {
    assert(checkval(val));
    this->val = val;
    return *this;
  }

  operator const valtype&()
  {
    return val;
  }

  friend ostream &operator << (ostream& out, const ConstrainedValue& v)
  {
    out << +v.val;
    return out;
  }

  friend istream &operator >> (istream& in, ConstrainedValue& v)
  {
    auto hlp = +v.val; // I think it's safe to assume that hlp will have at least as much precision as v.val?
    in >> hlp;
    assert(in.good()); // In case of input overflow this fails.
    assert(checkval(hlp));
    v.val = hlp;
    return in;
  }
};



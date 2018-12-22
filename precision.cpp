#include <iostream>
#include <algorithm>
#include <cmath>

double floor(double v, int pos) {
  // May overflow! Is there any better algorithm??
  return floor(v * pow(10, pos)) * pow(10, -pos);
}

template <int prec> class Double {
private:
  double val; // 0 <= val < 10
  int exp;

public:
  Double(double _val) {    
    double sign = double(1);

    if (_val < double(0)) {
      _val *= -1;
      sign = double(-1);
    }

    if (_val == double(0)) {
      val = 0;
      exp = 0;
    }
    else if (_val > double(1)) {
      int n = 0;
      while(++n) {
	if (_val < pow(10, n))
	  break;
      }
      this->exp = n-1;
      this->val = _val / pow(10, n-1);
    }
    else if (_val < double(1) && _val > double(0)) {
      int n = 0;
      while(--n) {
	if (_val > pow(10, n))
	  break;
      }
      this->exp = n;
      this->val = _val / pow(10, n);
    }

    this->val = floor(this->val, prec-1);
    this->val *= sign;
  }

  int precision() const {
    return prec;
  }

  double value() const {
    return (this->val) * pow(10, this->exp);
  }

  double get_val() const {
    return this->val;
  }

  int get_exp() const {
    return this->exp;
  }
};


template <int prec1, int prec2> Double<std::min(prec1,prec2)>
operator+(const Double<prec1>& v1, const Double<prec2>& v2) {
  double value = v1.value() + v2.value();
  return Double<std::min(prec1,prec2)>(value);
}

template <int prec> auto&
operator<<(decltype(std::cout)& out, const Double<prec>& v) {
  return (out << v.get_val() << " * 10^" << v.get_exp());
}

int main() {
  auto v1 = Double<3>(1.11);
  auto v2 = Double<4>(12.34);
  auto v3 = v1 + v2;

  // Output: "1.11 * 10^0 + 1.234 * 10^1 = 1.34 * 10^1"
  std::cout << v1 << " + " << v2 << " = " << v3 << std::endl;

  return 0;
}

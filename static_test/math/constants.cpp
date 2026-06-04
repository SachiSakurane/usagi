#include <usagi/math/constants.hpp>
#include <usagi/usagi.hpp>

#include <type_traits>

namespace {
template <class Type>
constexpr auto nearly_equal(Type lhs, Type rhs, Type epsilon) -> bool {
  return lhs > rhs ? lhs - rhs <= epsilon : rhs - lhs <= epsilon;
}

static_assert(std::is_same_v<decltype(usagi::math::pi<float>), const float>);
static_assert(std::is_same_v<decltype(usagi::math::pi<double>), const double>);

static_assert([] {
  constexpr auto epsilon = 1.0e-12;

  static_assert(nearly_equal(usagi::math::e<double>, 2.718281828459045, epsilon));
  static_assert(nearly_equal(usagi::math::pi<double>, 3.141592653589793, epsilon));
  static_assert(nearly_equal(usagi::math::two_pi<double>, usagi::math::pi<double> * 2.0, epsilon));
  static_assert(nearly_equal(usagi::math::half_pi<double>, usagi::math::pi<double> * 0.5, epsilon));
  static_assert(nearly_equal(usagi::math::quarter_pi<double>, usagi::math::pi<double> * 0.25, epsilon));
  static_assert(nearly_equal(usagi::math::inv_pi<double>, 1.0 / usagi::math::pi<double>, epsilon));
  static_assert(nearly_equal(usagi::math::inv_two_pi<double>, 1.0 / usagi::math::two_pi<double>, epsilon));
  static_assert(nearly_equal(usagi::math::inv_half_pi<double>, 1.0 / usagi::math::half_pi<double>, epsilon));
  static_assert(nearly_equal(usagi::math::inv_quarter_pi<double>, 1.0 / usagi::math::quarter_pi<double>, epsilon));
  static_assert(nearly_equal(usagi::math::root_two<double>, 1.414213562373095, epsilon));
  static_assert(nearly_equal(usagi::math::inv_root_two<double>, 1.0 / usagi::math::root_two<double>, epsilon));
  static_assert(nearly_equal(usagi::math::ln_two<double>, 0.6931471805599453, epsilon));
  static_assert(nearly_equal(usagi::math::ln_ten<double>, 2.302585092994046, epsilon));

  return nearly_equal(usagi::math::pi<float>, 3.1415927F, 1.0e-6F) &&
         nearly_equal(usagi::math::two_pi<float>, usagi::math::pi<float> * 2.0F, 1.0e-6F);
}());
} // namespace

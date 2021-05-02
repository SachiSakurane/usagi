#pragma once

#include <type_traits>

#define USAGI_UNPACK(x) x

#define USAGI_CONCEPT_WRAPPER(name, template_types, types, predicate) \
  template <class>                                                    \
  struct name##_impl : std::false_type                                \
  {                                                                   \
  };                                                                  \
  template <>                                                         \
  struct name##_impl<void> : std::true_type                           \
  {                                                                   \
  };                                                                  \
  template <USAGI_UNPACK template_types>                              \
  struct name : name##_impl<std::enable_if_t<predicate>>              \
  {                                                                   \
  };                                                                  \
  template <USAGI_UNPACK template_types>                              \
  inline constexpr bool name##_v = name<types>::value;

#define USAGI_CONCEPT(name, predicate) USAGI_CONCEPT_WRAPPER(name, (class Type), Type, (predicate))
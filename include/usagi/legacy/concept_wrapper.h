#pragma once

#include <type_traits>

#define USAGI_UNPACK(x) x

#define USAGI_CONCEPT_WRAPPER(name, template_types, types, predicate)     \
  template <USAGI_UNPACK template_types, class = void>                    \
  struct name##_impl : std::false_type                                    \
  {                                                                       \
  };                                                                      \
  template <USAGI_UNPACK template_types>                                  \
  struct name##_impl<types, std::enable_if_t<predicate>> : std::true_type \
  {                                                                       \
  };                                                                      \
  template <USAGI_UNPACK template_types>                                  \
  struct name : name##_impl<types>                                        \
  {                                                                       \
  };                                                                      \
  template <USAGI_UNPACK template_types>                                  \
  inline constexpr bool name##_v = name<types>::value;

#define USAGI_CONCEPT(name, predicate) USAGI_CONCEPT_WRAPPER(name, (class Type), Type, (predicate))
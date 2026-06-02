#pragma once

namespace usagi::utility {
/// Base class that deletes copy construction and copy assignment for derived types.
///
/// @tparam Type Derived type tag used to make the base distinct per owner.
template <class Type>
class noncopyable {
protected:
  /// Allows derived types to construct the base.
  noncopyable() = default;
  /// Allows derived types to destroy through their own destructor.
  virtual ~noncopyable() = default;

private:
  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
};

} // namespace usagi::utility

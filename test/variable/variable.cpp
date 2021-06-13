#include <gtest/gtest.h>
#include <usagi/variable/variable.h>

TEST(VariableTest, ConstantCase)
{
  ASSERT_TRUE(usagi::variable{42}() == 42);
  auto va = usagi::variable{42};
  ASSERT_TRUE(va() == 42);
  auto v = 42;
  ASSERT_TRUE(usagi::variable{v}() == 42);
}

TEST(VariableTest, FunctionCase)
{
  ASSERT_TRUE(usagi::variable{[]()
                              { return 42; }}() == 42);
  auto va = usagi::variable{[]()
                            { return 42; }};
  ASSERT_TRUE(va() == 42);
  auto v = []()
  { return 42; };
  ASSERT_TRUE(usagi::variable{v}() == 42);
}

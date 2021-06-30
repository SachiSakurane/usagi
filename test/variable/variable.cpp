#include <gtest/gtest.h>
#include <usagi/variable/variable.h>

TEST(VariableTest, ConstantCase)
{
  ASSERT_EQ(usagi::variable{42}(), 42);
  auto va = usagi::variable{42};
  ASSERT_EQ(va(), 42);
  auto v = 42;
  ASSERT_EQ(usagi::variable{v}(), 42);

  ASSERT_EQ(usagi::variable{std::string{"42"}}(), "42");
}

TEST(VariableTest, FunctionCase)
{
  ASSERT_EQ(usagi::variable{[]()
                            { return 42; }}(), 42);
  auto va = usagi::variable{[]()
                            { return 42; }};
  ASSERT_EQ(va(), 42);
  auto v = []()
  { return 42; };
  ASSERT_EQ(usagi::variable{v}(), 42);

  ASSERT_EQ(usagi::variable{[]()
                            { return std::string{"42"}; }}(),
            "42");
}

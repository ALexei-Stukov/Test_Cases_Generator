#include "function_test.h"

#include <limits.h>

#include "gtest/gtest.h"

namespace {
/*
  add test on here

  TEST( session_name , topic_name ) { // "session_name" can't be a class name

    //use some assert to test something
  
  }

*/
  TEST(INTERVAL_test, build_and_check_is_valid) {
    EXPECT_EQ(true, build_and_check_is_valid());
  }

  TEST(INTERVAL_test, set_close) {
    EXPECT_EQ(true, set_close());
  }

  TEST(INTERVAL_test, invert) {
    EXPECT_EQ(true, invert());
  }
  
  TEST(INTERVAL_test, random_in_range) {
    EXPECT_EQ(true, random_in_range());
  }
  
  TEST(INTERVAL_test, critical_random_in_range) {
    EXPECT_EQ(true, critical_random_in_range());
  }

}  // namespace


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
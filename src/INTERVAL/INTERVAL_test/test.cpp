#include "function_test.h"

#include <limits.h>

#include "gtest/gtest.h"

namespace {
/*
  add test on here

  TEST( Session_name , topic_name ) {

    //use some assert to test something
  
  }

*/
  TEST(build_and_check_isValid, normal) {
    EXPECT_EQ(true, build_and_check_isValid());
  }

  TEST(set_close, normal) {
    EXPECT_EQ(true, set_close());
  }

  TEST(invert, normal) {
    EXPECT_EQ(true, invert());
  }
  
  TEST(random_in_range, normal) {
    EXPECT_EQ(true, random_in_range());
  }
  
  TEST(critical_random_in_range, normal) {
    EXPECT_EQ(true, critical_random_in_range());
  }

}  // namespace


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
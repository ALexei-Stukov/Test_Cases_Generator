#include "function_test.h"
#include <random>
#include <iostream>
using namespace TEST_CASES_GENERATOR;
    
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::numeric_limits;

Interval get_a_valid_range()
{
  Interval range;
  //直到构造出一个合规的区间
  do{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> Left_distrib(numeric_limits<double>::lowest(),0);
    uniform_real_distribution<> Right_distrib(0,numeric_limits<double>::max());
    double left_value = Left_distrib(gen);
    double right_value = Right_distrib(gen);
    
    range.set_leftval(left_value);
    range.set_rightval(right_value);

    if(numeric_limits<double>::lowest() < left_value )
    {
      range.set_leftclosed(((int)left_value)%2 == 0);
    }
  }while( !range.is_valid() );

  return range;
}

bool build_and_check_is_valid()
{
  bool check_range=true;
  for(int i=0;i<1000000;i++)
  {
    Interval t = get_a_valid_range();
    check_range &= t.is_valid();
  }
  
  Interval default_range;
  check_range &= default_range.is_valid() && (!default_range.is_leftclosed()) && (!default_range.is_rightclosed());
  return check_range;
}

bool set_close()
{
  Interval t1,t2;
  t1.set_leftclosed(true);
  t1.set_rightclosed(true);

  t2.set_leftclosed(false);
  t2.set_rightclosed(false);

  return t1.is_leftclosed() && t1.is_rightclosed() && !(t2.is_rightclosed()) && !(t2.is_rightclosed());
}

bool invert_count_and_is_valid(Interval t,int count)
{
  auto res = t.invert();
  bool count_check = (res.size() == count);

  bool range_check = true;
  for(auto it = res.begin();it<res.end();it++)
  {
    range_check *= it->is_valid();
  }
  return count_check && range_check;
}

bool invert()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> Left_distrib(numeric_limits<double>::lowest()/2, 0);
  double left_value = Left_distrib(gen);

  uniform_real_distribution<> Right_distrib(0,numeric_limits<double>::max()/2);
  double right_value = Right_distrib(gen);
  
  Interval All_Real_Number; //All_Real_Number can't be revert，so the result count is 0

  Interval Left_Empty;  // result count is 1
  Left_Empty.set_leftval(left_value);
  
  Interval Right_Empty; // result count is 1
  Right_Empty.set_rightval(right_value);

  Interval Both_Empty;// result count is 2
  Both_Empty.set_leftval(left_value);
  Both_Empty.set_rightval(right_value);

  return  invert_count_and_is_valid(All_Real_Number,0) && \
          invert_count_and_is_valid(Left_Empty,1) && \
          invert_count_and_is_valid(Right_Empty,1) && \
          invert_count_and_is_valid(Both_Empty,2);
}

bool random_in_range()
{
  //这个函数会出问题，输出的结果是 -1.62361e+308  inf  1.1185e+308
  Interval range = get_a_valid_range();

  bool range_check = true;
  for(int i=0;i<10000000;i++)
  {
    long long int result = range.generate_random_int();
    range_check &= (( range.get_leftval() <= result ) && ( result <= range.get_rightval() ));
    if( !range_check ){
      std::cout<<range.get_leftval()<<"  "<<result<<"  "<<range.get_rightval()<<"\n";
      range_check != range_check;
    }
  }
  
  for(int i=0;i<10000000;i++)
  {
    double result = range.generate_random_double();
    range_check &= (( range.get_leftval() <= result ) && ( result <= range.get_rightval() ));

    if( !range_check ){
      std::cout<<range.get_leftval()<<"  "<<result<<"  "<<range.get_rightval()<<"\n";
      range_check != range_check;
    }
  }

  return range_check;
}

bool critical_random_in_range()
{
  Interval range = get_a_valid_range();
  
  bool range_check = true;
  for(int i=0;i<1000000;i++)
  {
    long long int result = range.generate_critical_int(true);
    bool distence = (abs(result - range.get_leftval()) <= 1);
    // std::cout<<range.get_leftval()<<"  "<<result<<"  "<<range.get_rightval()<<"\n";
    range_check &= (( range.get_leftval() <= result ) && ( result <= range.get_rightval() ));
  }
  
  for(int i=0;i<1000000;i++)
  {
    double result = range.generate_critical_double(false);
    bool distence_check = (abs(result - range.get_rightval()) <= 1);
    range_check &= (distence_check && ( range.get_leftval() <= result ) && ( result <= range.get_rightval() ));
  }

  return range_check;
}
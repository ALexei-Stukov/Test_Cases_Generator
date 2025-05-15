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
    
    range.setLeftVal(left_value);
    range.setRightVal(right_value);

    if(numeric_limits<double>::lowest() < left_value )
    {
      range.setLeftClosed(((int)left_value)%2 == 0);
    }
  }while( !range.isValid() );

  return range;
}

bool build_and_check_isValid()
{
  bool check_range=true;
  for(int i=0;i<1000000;i++)
  {
    Interval t = get_a_valid_range();
    check_range &= t.isValid();
  }
  
  Interval default_range;
  check_range &= default_range.isValid() && (!default_range.isLeftClosed()) && (!default_range.isRightClosed());
  return check_range;
}

bool set_close()
{
  Interval t1,t2;
  t1.setLeftClosed(true);
  t1.setRightClosed(true);

  t2.setLeftClosed(false);
  t2.setRightClosed(false);

  return t1.isLeftClosed() && t1.isRightClosed() && !(t2.isRightClosed()) && !(t2.isRightClosed());
}

bool invert_count_and_isValid(Interval t,int count)
{
  auto res = t.invert();
  bool count_check = (res.size() == count);

  bool range_check = true;
  for(auto it = res.begin();it<res.end();it++)
  {
    range_check *= it->isValid();
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
  Left_Empty.setLeftVal(left_value);
  
  Interval Right_Empty; // result count is 1
  Right_Empty.setRightVal(right_value);

  Interval Both_Empty;// result count is 2
  Both_Empty.setLeftVal(left_value);
  Both_Empty.setRightVal(right_value);

  return  invert_count_and_isValid(All_Real_Number,0) && \
          invert_count_and_isValid(Left_Empty,1) && \
          invert_count_and_isValid(Right_Empty,1) && \
          invert_count_and_isValid(Both_Empty,2);
}

bool random_in_range()
{
  Interval range = get_a_valid_range();

  bool range_check = true;
  for(int i=0;i<10000000;i++)
  {
    long long int result = range.generateRandomInt();
    range_check &= (( range.getLeftVal() <= result ) && ( result <= range.getRightVal() ));
    if( !range_check ){
      std::cout<<range.getLeftVal()<<"  "<<result<<"  "<<range.getRightVal()<<"\n";
      range_check != range_check;
    }
  }
  
  for(int i=0;i<10000000;i++)
  {
    double result = range.generateRandomDouble();
    range_check &= (( range.getLeftVal() <= result ) && ( result <= range.getRightVal() ));

    if( !range_check ){
      std::cout<<range.getLeftVal()<<"  "<<result<<"  "<<range.getRightVal()<<"\n";
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
    long long int result = range.generateCriticalInt(true);
    bool distence = (abs(result - range.getLeftVal()) <= 1);
    // std::cout<<range.getLeftVal()<<"  "<<result<<"  "<<range.getRightVal()<<"\n";
    range_check &= (( range.getLeftVal() <= result ) && ( result <= range.getRightVal() ));
  }
  
  for(int i=0;i<1000000;i++)
  {
    double result = range.generateCriticalDouble(false);
    bool distence_check = (abs(result - range.getRightVal()) <= 1);
    range_check &= (distence_check && ( range.getLeftVal() <= result ) && ( result <= range.getRightVal() ));
  }

  return range_check;
}
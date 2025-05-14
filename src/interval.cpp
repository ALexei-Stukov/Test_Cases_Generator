#include "interval.h"
#include <cfloat>   //for DBL_MAX and DBL_MIN
#include <algorithm>  // For std::swap
#include <random>
#include <iostream>
namespace TEST_CASE_GENERATOR
{
    using std::swap;
    using std::random_device;
    using std::mt19937;
    using std::uniform_real_distribution;
    using std::uniform_int_distribution;
    using std::numeric_limits;

    Interval::Interval()
    {
        left_closed = true;
        right_closed = true;
        left_val = numeric_limits<double>::lowest(); //最小double值
        right_val = numeric_limits<double>::max();    //最大double值
        std::cout<<"what?? "<<left_val<<" "<<right_val<<std::endl;
    }

    //检查区间是否合法
    bool Interval::isValid() 
    {
        //  范围检查，左侧必须小于右侧。
        //  不支持 left = right 的区间。对于left = right的区间，要么是不合理的区间 (3,3) (3,3] [3,3) ，要么退化成了点 [3,3]。这些情况一概认为不是正常区间。
        // bool left_LT_right = (left_val < right_val);

        //  因为我们已经规定了 left != right ，所以区间的开闭判断就不再重要了。
        // return left_LT_right;
        return (left_val < right_val);
    }

    // 数据访问函数
    bool Interval::isLeftClosed() const {return left_closed; }
    void Interval::setLeftClosed(bool closed) { left_closed = closed; }

    bool Interval::isRightClosed() const { return right_closed; }
    void Interval::setRightClosed(bool closed) { right_closed = closed; }

    double Interval::getLeftVal() const { return left_val; }
    void Interval::setLeftVal(double val) { left_val = val; }

    double Interval::getRightVal() const { return right_val; }
    void Interval::setRightVal(double val) { right_val = val; }

    // 区间相对于 全体实数范围 取反，将产生2个区间。
    vector<Interval> Interval::invert()
    {
        vector<Interval> ret;
        Interval left_to_min;
        // [DBL_MIN,left_value) or [DBL_MIN,left_value] 
        left_to_min.setLeftClosed(true);
        left_to_min.setLeftVal(DBL_MIN);
        left_to_min.setRightClosed( !(this->isLeftClosed()) );
        left_to_min.setRightVal( this->getLeftVal() );
        ret.push_back(left_to_min);

        Interval right_to_max;
        // (right_value,DBL_MAX] or [right_value,DBL_MAX] 
        right_to_max.setRightClosed(true);
        right_to_max.setRightVal(DBL_MAX);
        right_to_max.setLeftClosed( !(this->isRightClosed()) );
        right_to_max.setLeftVal( this->getRightVal() );
        ret.push_back(right_to_max);

        return ret;
    }

    // 生成整数随机数（处理闭开区间边界）
    long long int Interval::generateRandomInt() const 
    {
        long long int minVal = left_closed ? ceil(left_val) : floor(left_val) + 1;
        long long int maxVal = right_closed ? floor(right_val) : ceil(right_val) - 1;
        
        if (minVal > maxVal) return numeric_limits<int>::quiet_NaN();

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(minVal, maxVal);
        long long int ret = distrib(gen);        
        return ret;
    }

    // 生成浮点数随机数（精确处理开闭区间）
    double Interval::generateRandomDouble() const 
    {
        double minVal = left_closed ? left_val : nextafter(left_val, numeric_limits<double>::max());
        double maxVal = right_closed ? right_val : nextafter(right_val, numeric_limits<double>::lowest());

        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> distrib(minVal, maxVal);
        return distrib(gen);
    }

    long long int Interval::generateCriticalInt(bool is_left) const
    {
        //需要针对左右区间的不同情况，分别指定参与计算的变量。
        long long int offset = is_left ? +1 : -1;
        bool is_closed = is_left ? left_closed : right_closed;
        double target_value = is_left ? left_val : right_val;
        std::cout<<"the real target_value is "<<target_value<<std::endl;
        if( is_closed )
        {
            return (long long int)target_value;
        }
        else
        {
            return ((long long int)target_value + offset);
        }
    }
    double Interval::generateCriticalDouble(bool is_left) const
    {
        //需要针对左右区间的不同情况，分别指定参与计算的变量。
        bool is_closed = is_left ? left_closed : right_closed;
        double target_value = is_left ? left_val : right_val;

        //对于不同量级的范围，自然也需要不同量级的偏移。
        double offset = is_left? (target_value/100)*1 : (target_value/100)*-1;
        
        if( is_closed )
        {
            return target_value;
        }
        else
        {
            return (target_value + offset);
        }
    }
}
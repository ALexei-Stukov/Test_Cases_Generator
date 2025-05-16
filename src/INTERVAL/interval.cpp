#include "interval.h"
// #include <cfloat>   //for DBL_MAX and DBL_MIN
#include <algorithm>  // For std::swap
#include <random>
#include <iostream>
namespace TEST_CASES_GENERATOR
{
    using std::swap;
    using std::random_device;
    using std::mt19937;
    using std::uniform_real_distribution;
    using std::uniform_int_distribution;
    using std::numeric_limits;

    Interval::Interval()
    {
        left_closed = false;
        right_closed = false;
        left_val = numeric_limits<double>::lowest(); //最小double值
        right_val = numeric_limits<double>::max();    //最大double值
        // std::cout<<"what?? "<<left_val<<" "<<right_val<<std::endl;
    }

    //检查区间是否合法
    bool Interval::is_valid() 
    {
        //  范围检查，左侧必须小于右侧。
        //  不支持 left = right 的区间。对于left = right的区间，要么是不合理的区间 (3,3) (3,3] [3,3) ，要么退化成了点 [3,3]。这些情况一概认为不是正常区间。
        // bool left_LT_right = (left_val < right_val);

        //  因为我们已经规定了 left != right ，所以区间的开闭判断就不再重要了。
        // return left_LT_right;
        return (left_val < right_val);
    }

    // 数据访问函数
    bool Interval::is_leftclosed() const {return left_closed; }
    void Interval::set_leftclosed(bool closed) { left_closed = closed; }

    bool Interval::is_rightclosed() const { return right_closed; }
    void Interval::set_rightclosed(bool closed) { right_closed = closed; }

    double Interval::get_leftval() const { return left_val; }
    void Interval::set_leftval(double val) { left_val = val; }

    double Interval::get_rightval() const { return right_val; }
    void Interval::set_rightval(double val) { right_val = val; }

    // 区间相对于 全体实数范围 取反，将产生2个区间。
    vector<Interval> Interval::invert()
    {
        vector<Interval> ret;
        Interval left_to_min;
        // [DBL_MIN,left_value) or [DBL_MIN,left_value] 
        left_to_min.set_leftclosed(false);
        left_to_min.set_leftval(numeric_limits<double>::lowest());

        left_to_min.set_rightclosed( !(this->is_leftclosed()) );
        left_to_min.set_rightval( this->get_leftval() );
        // remove the [DBL_MIN,DBL_MIN]
        if(left_to_min.is_valid())
        {
            ret.push_back(left_to_min);
        }

        Interval right_to_max;
        // (right_value,DBL_MAX] or [right_value,DBL_MAX] 
        right_to_max.set_rightclosed(false);
        right_to_max.set_rightval(numeric_limits<double>::max());

        right_to_max.set_leftclosed( !(this->is_rightclosed()) );
        right_to_max.set_leftval( this->get_rightval() );
 
        if(right_to_max.is_valid())
        {
            ret.push_back(right_to_max);
        }

        return ret;
    }

    // 生成整数随机数（处理闭开区间边界）
    long long int Interval::generate_random_int() const 
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
    double Interval::generate_random_double() const 
    {
        double minVal = left_closed ? left_val : nextafter(left_val, numeric_limits<double>::max());
        double maxVal = right_closed ? right_val : nextafter(right_val, numeric_limits<double>::lowest());
        // std::cout<<"minVal = "<<minVal<<"  "<<"maxVal = "<<maxVal<<"\n";
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> distrib(0, 1.0);  // 生成 [0,1] 范围的随机数
        double rand = distrib(gen);

        //把[0,1]缩放到大区间。使用一些手法确保不会出现越界。
        return  minVal*(1-rand) + maxVal*rand;
        // return minVal + (maxVal - minVal) * rand;

        /*
            不能直接使用
                uniform_real_distribution<> distrib(minVal, maxVal);
                return distrib(gen);
            当minVal和maxVal过大，可能会导致 distrib(gen) 的内部运算出现inf，进而导致最终运算结果出错。
            区间放缩是一个比较好用的手法。
        */
    }

    long long int Interval::generate_critical_int(bool is_left) const
    {
        //需要针对左右区间的不同情况，分别指定参与计算的变量。
        long long int offset = is_left ? +1 : -1;
        bool is_closed = is_left ? left_closed : right_closed;
        double target_value = is_left ? left_val : right_val;
        // std::cout<<"the real target_value is "<<target_value<<std::endl;
        if( is_closed )
        {
            return (long long int)target_value;
        }
        else
        {
            return ((long long int)target_value + offset);
        }
    }
    double Interval::generate_critical_double(bool is_left) const
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
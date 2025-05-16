#ifndef INTERVAL
#define INTERVAL

#include <vector>
namespace TEST_CASES_GENERATOR{
    using std::vector;
    
    //区间类型
    class Interval {
    public:
        Interval();

        //检查区间是否合法
        bool is_valid();

        // 读写区间的开闭类型
        bool is_leftclosed() const;
        void set_leftclosed(bool closed);

        bool is_rightclosed() const;
        void set_rightclosed(bool closed);

        // 读写左右端点的值
        double get_leftval() const;
        void set_leftval(double val);

        double get_rightval() const;
        void set_rightval(double val);

        // 区间取反（相对于全体实数范围）,将产生1或2个区间。
        vector<Interval> invert();

        //区间内随机数生成，可以生成int型或者double型
        long long int generate_random_int() const;
        double generate_random_double() const;

        //区间内临界值生成，可以生成int型或者double型。在开区间的情况下，左右临界值的处理方法稍有不同。
        long long int generate_critical_int(bool is_left) const;
        double generate_critical_double(bool is_left) const;

    private:
        bool left_closed;
        bool right_closed;
        double left_val;
        double right_val;
    };
}

#endif
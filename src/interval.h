#ifndef INTERVAL
#define INTERVAL

#include <vector>
namespace TEST_CASE_GENERATOR{
    using std::vector;
    
    //区间类型
    class Interval {
    public:
        Interval();

        //检查区间是否合法
        bool isValid();

        // 读写区间的开闭类型
        bool isLeftClosed() const;
        void setLeftClosed(bool closed);

        bool isRightClosed() const;
        void setRightClosed(bool closed);

        // 读写左右端点的值
        double getLeftVal() const;
        void setLeftVal(double val);

        double getRightVal() const;
        void setRightVal(double val);

        // 区间取反（相对于全体实数范围）,将产生2个区间。
        vector<Interval> invert();

        //区间内随机数生成，可以生成int型或者double型
        long long int generateRandomInt() const;
        double generateRandomDouble() const;

        //区间内临界值生成，可以生成int型或者double型。在开区间的情况下，左右临界值的处理方法稍有不同。
        long long int generateCriticalInt(bool is_left) const;
        double generateCriticalDouble(bool is_left) const;

    private:
        bool left_closed;
        bool right_closed;
        double left_val;
        double right_val;
    };
}

#endif
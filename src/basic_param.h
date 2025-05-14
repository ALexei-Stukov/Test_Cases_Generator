#ifndef BASIC_PARAM
#define BASIC_PARAM

#include "interval.h"
#include <unordered_set>

namespace TEST_CASE_GENERATOR
{
    using std::string;
    using std::unordered_set;

    class test_param
    {
    public:    
        int type = 0;   /*
                            这个值将决定最终打印(print)的参数
                            0(only Int)
                            1(only Double)
                            2(Int or Double by Randomly)
                            otherwise(nothing can be provide)
                        */
        long long int int_value = 0;   //int类型的值
        double lf_value = 0;    //double类型的值
    };

    class basic_param
    {
    public:
        virtual int generate_test_params()=0;
        virtual void read_line(string str)=0;
        vector<test_param> param_list;    //当前参数所有可能的值
        int type;   /*
                        这个值将决定最终生成(generate)的参数
                        0(only Int)
                        1(only Double)
                        2(Int or Double by Randomly)
                    */
        string param_name;   // 当前参数的名称
    };

    class enum_type:public basic_param
    {
    public:
        enum_type(string str);
        int generate_test_params();
        void read_line(string str);

        unordered_set<long long int> inputs;   // 记录枚举类型的所有可能性
    };

    class range_type:public basic_param
    {
    public:
        range_type(string str);
        int generate_test_params();
        void read_line(string str);

        string trim(const string &s);   //  辅助解析字符串
        bool parseDouble(const string &s, double &val);
        vector<string> extractIntervalStrings(const string& s);
        vector<Interval> parseIntervals(const string &s);
        
        test_param get_random_value_from_Interval(string value_type,Interval& range);   //区间内随机值
        test_param get_left_critical_value_from_Interval(string value_type,Interval& range);    //左侧临界值
        test_param get_right_critical_value_from_Interval(string value_type,Interval& range);   //右侧临界值
        
        string type;    //类型，int double 或 mix。

        int param_count_level;  //一个0到3的整数。数值越大，执行generate_test_params()时能提供的测试参数数量就越多。
        int calculate_the_count(int N);
        
        vector<Interval> ranges;//记录所有区间
        vector<long long int> input_list;   // 记录所有int类型的可能性
        vector<double> input_lf_list;   // 记录所有lf类型的可能性
    };
}

#endif
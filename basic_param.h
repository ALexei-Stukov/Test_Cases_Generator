#ifndef BASIC_PARAM
#define BASIC_PARAM

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
    size_t int_value = 0;   //int类型的值
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

    vector<size_t> input_list;   // 记录枚举类型的所有可能性
};

//区间类型
struct Interval {
    bool left_closed;
    bool right_closed;
    double left_val;
    double right_val;

    bool isValid() const {
        if (left_val > right_val) return false;
        if (left_val < right_val) return true;
        return left_closed && right_closed;
    }
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
    int generateRandomInt(double left, bool leftClosed, double right, bool rightClosed);
    double generateRandomDouble(double left, bool leftClosed, double right, bool rightClosed);
    
    string type;    //类型

    vector<Interval> ranges;//记录所有区间
    vector<size_t> input_list;   // 记录所有int类型的可能性
    vector<double> input_lf_list;   // 记录所有lf类型的可能性
};

#endif
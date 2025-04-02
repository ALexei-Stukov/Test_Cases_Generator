#ifndef INPUT_TYPE
#define INPUT_TYPE

class test_case{
public:
    test_case(string input_str)
    {
        name = input_str;
    }
    size_t int_value = 0;   //int类型的值
    string name = "no_name";    //测试用例的具体含义。如果为空，则视为无含义。
    double lf_value = 0;    //double类型的值
    int type = 0;   //测试用例的类型 // 0(only int) 1(only double) 2(both int and double)
};

class input_type{
public:
    virtual void generate_test_cases()=0;
    virtual void read_input()=0;
    vector<test_case> case_list;
    int value_type; // 0(only int) 1(only double) 2(both int and double)
    string name;   // 该输入的名称
};

class enum_type:public input_type{
public:
    enum_type(string str);
    void generate_test_cases();
    void read_input();

    vector<size_t> input_list;   // 记录所有枚举的可能性
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

class range_type:public input_type{
public:
    range_type(string str);
    void generate_test_cases();
    void read_input();

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
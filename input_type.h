#ifndef INPUT_TYPE
#define INPUT_TYPE

class test_case{
public:
    test_case(size_t input_value,string input_str)
    {
        value = input_value;
        name = input_str;
    }
    size_t value;   //测试用例的值
    string name;    //测试用例的具体含义。如果为空，则视为无含义。
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

#endif
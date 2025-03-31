#ifndef INPUT_TYPE
#define INPUT_TYPE

class test_case{
    size_t value;   //测试用例的值
    string name;    //测试用例的具体含义。如果为空，则视为无含义。
};

class input_type{
public:
    virtual void generate_test_cases()=0;
    virtual void read_input()=0;
    vector<test_case> case_list;
};

class enum_type:public input_type{
public:
    void generate_test_cases();
    void read_input();
};

#endif
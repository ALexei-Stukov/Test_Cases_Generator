#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using std::vector;
using std::string;
using std::exception;
using std::cerr;
using std::cout;
using std::istringstream;
using std::endl;

#include "input_type.h"

void enum_type::generate_test_cases()
{
    for (auto it = input_list.begin();it < input_list.end();it++)
    {
        // test_case case_unit;
        // case_unit.value = *it;
        // case_unit.name = this->name;
        // case_list.push_back(case_unit);

        test_case case_unit(*it,name);
        case_list.push_back(case_unit);
    }

    cout << case_list.size()<<endl;
    
    return;   
}

void enum_type::read_input()
{
    return;   
}

enum_type::enum_type(string str)
{
    try{

        if(str.find("enum") == string::npos)
        {
            throw std::runtime_error("字符串"+str+"没有枚举标记");
        }

        //提取大括号内的内容
        size_t start = str.find('{');
        size_t end = str.find('}', start);
        if (start == string::npos || end == string::npos) {
            throw std::runtime_error("字符串"+str+"未找到有效的大括号结构");
        }
        string content = str.substr(start + 1, end - start - 1);

        //简单判断大括号数量是否异常
        start = content.find('{');
        end = content.find('}', start);
        if (start != string::npos || end != string::npos) {
            throw std::runtime_error("字符串"+str+"大括号数量异常");
        }

        //开始解析
        size_t colon_pos = content.find(':');
        if (colon_pos == string::npos) {
            throw std::runtime_error("字符串"+str+"缺少:分隔符");
        }

        // 3. 提取键名
        string key_part = content.substr(0, colon_pos);
        string str_name;
        // 移除双引号（如果有）
        if (key_part.front() == '"' && key_part.back() == '"') {
            str_name = key_part.substr(1, key_part.length() - 2);
        }

        // 处理数值部分
        vector<size_t> numbers;
        string values_part = content.substr(colon_pos + 1);
        
        // 将逗号替换为空格以便流处理
        replace(values_part.begin(), values_part.end(), ',', ' ');
        
        istringstream iss(values_part);
        int num;
        while (iss >> num) {
            numbers.push_back(num);
        }
        input_list = numbers;  //完成处理

        // 输出结果
        cout << "string str = \"" << str_name << "\"" << endl;
        cout << "vector<int> = { ";
        for (int n : numbers) {
            cout << n << " ";
        }
        cout << "}" << endl;
        
    }catch(const exception& e){
        cerr << "[捕获到exception]" << e.what() << endl;
        cerr << "程序终止" << endl;
        exit(1);
    }
}
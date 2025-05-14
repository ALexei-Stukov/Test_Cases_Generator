#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "basic_param.h"
namespace TEST_CASE_GENERATOR
{
    using namespace std;

    int enum_type::generate_test_params()
    {
        for (auto& it : inputs) 
        {
            test_param unit;
            unit.type = 0; //int类型
            unit.int_value = it;
            this->param_list.push_back(unit);
        }

        return param_list.size();
    }

    void enum_type::read_line(string str)
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

            //提取键名
            string key_part = content.substr(0, colon_pos);
            string str_name;
            //移除双引号（如果有）
            if (key_part.front() == '"' && key_part.back() == '"') {
                str_name = key_part.substr(1, key_part.length() - 2);
            }
            this->param_name = str_name;

            //处理数值部分
            unordered_set<long long int> numbers;
            string values_part = content.substr(colon_pos + 1);
            
            //将逗号替换为空格以便流处理
            replace(values_part.begin(), values_part.end(), ',', ' ');
            
            istringstream iss(values_part);
            int num;
            while (iss >> num) {
                numbers.emplace(num);
            }
            inputs = numbers;  //完成处理        
        }catch(const exception& e){
            cerr << "[捕获到exception]" << e.what() << endl;
            cerr << "程序终止" << endl;
            exit(1);
        }

        return;   
    }

    enum_type::enum_type(string str)
    {
        read_line(str);
        //输出结果，尽可能确保在一行内完成
        cout << "enum_type | \"" << param_name << "\""<<"\t| ";
        cout << "vector<int> = { ";
        for (int n : this->inputs) {
            cout << n << " ";
        }
        cout << "}" << endl;
    }
}
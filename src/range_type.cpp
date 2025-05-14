#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cfloat>

#include <cctype>
#include <random>
#include <cmath>
#include <limits>

#include "basic_param.h"
namespace TEST_CASE_GENERATOR
{
    using namespace std;

    test_param range_type::get_random_value_from_Interval(string value_type,Interval& range)
    {
        test_param ret;
        if(value_type == "int")
        {
            ret.type = 0;
            ret.int_value = range.generateRandomInt();
        }
        else if(value_type == "double")
        {
            ret.type = 1;
            ret.lf_value = range.generateRandomDouble();
        }
        else    // mix
        {   
            //通过随机数的方式，概率均等地生成多种类型的参数。
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> distrib(0,8192);
            
            int flag = distrib(gen);
            if( flag % 2 == 0)
            {   // int
                ret.type = 0;
                ret.int_value = range.generateRandomInt();
            }
            else
            {   // double
                ret.type = 1;
                ret.lf_value = range.generateRandomDouble();
            }
        }
        return ret;
    }

    test_param range_type::get_left_critical_value_from_Interval(string value_type,Interval& range)
    {
        test_param ret;
        if(value_type == "int")
        {
            ret.type = 0;
            ret.int_value = range.generateCriticalInt(true);
        }
        else if(value_type == "double")
        {
            ret.type = 1;
            ret.lf_value = range.generateCriticalDouble(true);
        }
        else    // mix
        {   
            //通过随机数的方式，概率均等地生成多种类型的参数。
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> distrib(0,8192);
            
            int flag = distrib(gen);
            if( flag % 2 == 0)
            {   // int
                ret.type = 0;
                ret.int_value = range.generateCriticalInt(true);
            }
            else
            {   // double
                ret.type = 1;
                ret.lf_value = range.generateCriticalDouble(true);
            }
        }
        return ret;
    }

    test_param range_type::get_right_critical_value_from_Interval(string value_type,Interval& range)
    {
        test_param ret;
        if(value_type == "int")
        {
            ret.type = 0;
            ret.int_value = range.generateCriticalInt(false);
        }
        else if(value_type == "double")
        {
            ret.type = 1;
            ret.lf_value = range.generateCriticalDouble(false);
        }
        else    // mix
        {   
            //通过随机数的方式，概率均等地生成多种类型的参数。
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> distrib(0,8192);
            
            int flag = distrib(gen);
            if( flag % 2 == 0)
            {   // int
                ret.type = 0;
                ret.int_value = range.generateCriticalInt(false);
            }
            else
            {   // double
                ret.type = 1;
                ret.lf_value = range.generateCriticalDouble(false);
            }
        }
        return ret;
    }

    /**
    * @brief 生成测试输入的函数
    * 
    * @param[in]  a   第一个加数，支持整型数据
    * @param[in]  b   第二个加数，应与第一个加数类型相同
    * @param[out] sum 计算结果输出参数
    * 
    * @return 执行状态
    * @retval 0  成功完成计算
    * @retval -1 输入参数不合法
    * 
    * @note 此函数不处理数值溢出情况
    * @warning 禁止传入NULL指针作为sum参数
    * 
    * @code
    *   int result;
    *   if(add(5, 3, &result) == 0) {
    *       printf("5+3=%d", result);
    *   }
    * @endcode
    */
    int range_type::generate_test_params()
    {
        //需要逐个处理区间
        for (auto& it : ranges)
        // for (auto it = ranges.begin();it < ranges.end();it++)
        {
            //在目前的设计中，count_limit必然 >= 2 
            size_t count_limit = calculate_the_count(this->param_count_level);
            
            //针对边缘值专门构造2个测试用例
            test_param range_limit_left = get_left_critical_value_from_Interval(type,it);
            test_param range_limit_right = get_right_critical_value_from_Interval(type,it);
            param_list.push_back(range_limit_left);
            param_list.push_back(range_limit_right);

            for(int i = 2;i < count_limit;i++)
            {
                test_param case_unit = get_random_value_from_Interval(type,it);
                param_list.push_back(case_unit);
            }
        }
        return param_list.size();
    }

    void range_type::read_line(string str)
    {
        try{

            if(str.find("range") == string::npos)
            {
                throw std::runtime_error("字符串"+str+"没有范围标记");
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
            this->param_name = str_name;

            //更新':'标记的位置,检查类型
            content = content.substr(colon_pos+1,content.length());
            colon_pos = content.find(':');

            this->type = trim(content.substr(0, colon_pos));
            
            if (
                this->type != "int" &&
                this->type != "double" &&
                this->type != "mix"
            ) {
                throw std::runtime_error(str+"的类型不支持，请检查类型");
            }

            //更新':'标记的位置,检查参数生成的强度。
            content = content.substr(colon_pos+1,content.length());
            colon_pos = content.find(':');
            string count_of_params = trim(content.substr(0, colon_pos));
            this->param_count_level = stoi(count_of_params);    //这里可能会报stoi异常。

            string intervals_str = content.substr(colon_pos + 1);
            ranges = parseIntervals(intervals_str);

        }catch(const exception& e){
            cerr << "[捕获到exception]" << e.what() << endl;
            cerr << "程序终止" << endl;
            exit(1);
        }
        return;   
    }

    string range_type::trim(const string &s) {
        size_t first = s.find_first_not_of(" \t\n\r");
        if (first == string::npos) return "";
        size_t last = s.find_last_not_of(" \t\n\r");
        return s.substr(first, (last - first + 1));
    }

    bool range_type::parseDouble(const string &s, double &val) {
        /*
            此处需要处理特例。
            字符串MIN 和 字符串MAX 是无法通过输入流赋值给val的。因此需要单独处理。
        */
        if( s == "MIN" )
        {
            // val = DBL_MIN;
            val = numeric_limits<double>::lowest();
            return true;
        }
        else if( s == "MAX" )
        {
            // val = DBL_MAX;
            val = numeric_limits<double>::max();
            return true;
        }

        istringstream iss(s);
        iss >> val;
        char c;
        return !iss.fail() && !iss.get(c);
    }


    vector<string> range_type::extractIntervalStrings(const string& s) {
        vector<string> intervals;
        size_t start = 0;
        const size_t len = s.size();

        while (start < len) {
            // 跳过空格
            while (start < len && isspace(s[start])) start++;
            if (start >= len) break;

            char start_char = s[start];
            if (start_char != '(' && start_char != '[') {
                start++;
                continue;
            }

            // 查找下一个出现的闭合符号
            size_t end = s.find_first_of(")]", start + 1);
            if (end == string::npos) {
                start++;
                continue;
            }

            intervals.push_back(s.substr(start, end - start + 1));
            start = end + 1; // 移动到闭合括号之后的位置
        }
        return intervals;
    }

    vector<Interval> range_type::parseIntervals(const string &s) {
        vector<Interval> res;
        vector<string> intervalStrings = extractIntervalStrings(s);

        for (const string& intervalStr : intervalStrings) {
            string trimmed = trim(intervalStr);
            if (trimmed.empty()) continue;

            char front = trimmed[0];
            char back = trimmed.back();

            // 此处进行括号格式的严格校验
            if ((front != '(' && front != '[') || (back != ')' && back != ']'))
                continue;

            string content = trimmed.substr(1, trimmed.size() - 2);
            size_t commaPos = content.find(',');
            if (commaPos == string::npos) continue;

            string leftStr = trim(content.substr(0, commaPos));
            string rightStr = trim(content.substr(commaPos + 1));

            double left, right;
            if (!parseDouble(leftStr, left) || !parseDouble(rightStr, right))
                continue;

            Interval intv;
            intv.setLeftClosed(front == '[');
            intv.setRightClosed(back == ']');
            intv.setLeftVal(left);
            intv.setRightVal(right);

            if (intv.isValid())
                res.push_back(intv);
        }
        return res;
    }

    range_type::range_type(string str)
    {
        read_line(str);  
        cout << "range_type | \"" << param_name << "\"" << "\t | ";
        cout << "前缀标记: " << type << "\t | ";
        cout << "有效区间: ";
        for (const auto &intv : ranges) {
        cout << (intv.isLeftClosed() ? '[' : '(') 
            << intv.getLeftVal() << ", " 
            << intv.getRightVal() 
            << (intv.isRightClosed() ? ']' : ')') << " ";
        }
        cout<<endl;
    }

    int range_type::calculate_the_count(int N)
    {
        N = N % 4;  //确保N一定在0到3之间。
        /*
            目前用于计算数量的公式是：
            f(x) = 12x² - 4x + 2
            x = 0 时 数量为 2
            x = 1 时 数量为 10
            x = 2 时 数量为 42
            x = 3 时 数量为 98
            算式简单，不容易越界，产生的数量也符合预期，后续拓展到 x >= 4 时也比较方便。

            用秦九韶写法重写成:
            (12*x-4)*x+2
            可以用2次乘法+2次加法解决问题。
        */
        return  (12*N-4)*N+2;
    }
}
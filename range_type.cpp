#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include <cctype>
#include <random>
#include <cmath>
#include <limits>

using namespace std;

#include "basic_param.h"

int range_type::generate_test_params()
{
    //需要逐个处理区间
    for (auto& it : ranges)
    // for (auto it = ranges.begin();it < ranges.end();it++)
    {
        test_param case_unit;
        size_t L_NUMBER = it.left_val;
        size_t R_NUMBER = it.right_val;
        bool L_CLOSE = it.left_closed;
        size_t R_CLOSE = it.right_closed;
        if(type == "int")
        {
            case_unit.type = 0;
            case_unit.int_value = generateRandomInt(L_NUMBER,L_CLOSE,R_NUMBER,R_CLOSE);
        }
        else    //double
        {
            case_unit.type = 1;
            case_unit.lf_value = generateRandomDouble(L_NUMBER,L_CLOSE,R_NUMBER,R_CLOSE);
        }
        param_list.push_back(case_unit);
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

        //更新:标记的位置
        content = content.substr(colon_pos+1,content.length());
        colon_pos = content.find(':');

        this->type = trim(content.substr(0, colon_pos));

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
        intv.left_closed = (front == '[');
        intv.right_closed = (back == ']');
        intv.left_val = left;
        intv.right_val = right;

        if (intv.isValid())
            res.push_back(intv);
    }
    return res;
}


// 生成整数随机数（处理闭开区间边界）
int range_type::generateRandomInt(double left, bool leftClosed, double right, bool rightClosed) {
    int minVal = leftClosed ? ceil(left) : floor(left) + 1;
    int maxVal = rightClosed ? floor(right) : ceil(right) - 1;
    
    if (minVal > maxVal) return numeric_limits<int>::quiet_NaN();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);
    return distrib(gen);
}

// 生成浮点数随机数（精确处理开闭区间）
double range_type::generateRandomDouble(double left, bool leftClosed, double right, bool rightClosed) {
    double minVal = leftClosed ? left : nextafter(left, numeric_limits<double>::max());
    double maxVal = rightClosed ? right : nextafter(right, numeric_limits<double>::lowest());

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(minVal, maxVal);
    return distrib(gen);
}

range_type::range_type(string str)
{
    read_line(str);  
    cout << "range_type | \"" << param_name << "\"" << "\t | ";
    cout << "前缀标记: " << type << "\t | ";
    cout << "有效区间: ";
    for (const auto &intv : ranges) {
    cout << (intv.left_closed ? '[' : '(') 
         << intv.left_val << ", " 
         << intv.right_val 
         << (intv.right_closed ? ']' : ')') << " ";
    }
    cout<<endl;
}
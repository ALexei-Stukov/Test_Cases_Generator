#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <string>
using std::vector;
using std::string;
using std::cout;

#include "basic_param.h"
#include "dag.hpp"

using namespace TEST_CASE_GENERATOR;

/** 
 * @file generator.cpp 
 * @brief 主文件文档（文件级文档会生成独立链接） 
 */


/**
* @brief 主函数示例
*/
int main(int argc,char**argv)
{
    if(argc < 2)
    {
        cout<<"输入不足";
        return 1;
    }
    vector<basic_param*> all_param_list;

    // 创建文件输入流对象
    std::ifstream file(argv[1]);

    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件" + string(argv[1]) << std::endl;
        return 1;
    }

    std::string line;
    // 逐行读取文件内容
    while (std::getline(file, line)) {
        if( line.find('#') != string::npos )
        {
            // 被注释的输入
        }
        else if( line.find("enum") != string::npos )
        {
            enum_type* unit = new enum_type(line);
            all_param_list.push_back(unit);
        }
        else if( line.find("range") != string::npos)
        {
            range_type* unit = new range_type(line);
            all_param_list.push_back(unit);
            // cout<<"执行1次range type"<<std::endl;
        }
    }
    // 关闭文件
    file.close();
    // exit(0);    //
    cout<<"参数总个数: "<<all_param_list.size()<<std::endl;

    // 针对每个输入条目，生成参数列表
    for(auto it = all_param_list.begin();it < all_param_list.end();it++)
    {
        (*it)->generate_test_params();
    }

    // 填充进DAG图
    DAG<test_param> graph;
    test_param root_unit;   //根节点
    auto root_node = graph.add_node(root_unit);   //添加虚拟的根节点，方便处理。
 
    for(auto it = all_param_list.begin();it < all_param_list.end();it++)
    {
        //遍历DAG图，找到所有出度为0的点。这些出度为0的点会依次作为新节点的父节点。
        auto temp = graph.get_all_outdegree_zero_nodes();
        //又是技术债务，这里有一些类型问题还需要处理。
        auto new_node_list = temp;
        new_node_list.clear();

        for(auto case_it = (*it)->param_list.begin();case_it < (*it)->param_list.end();case_it++)
        {
            // cout<<"the type of tase_case is "<<(*case_it).type<<"\n";
            auto new_node = graph.add_node(*case_it); 
            // cout<<"the type of node is "<<(new_node->value).type<<"\n";
            for(auto temp_it = temp.begin();temp_it < temp.end();temp_it++)
            {
                graph.add_edge(*temp_it,new_node);
            }
        }
    }

    
    std::cout << "Now begin to build test case:"<<std::endl;
    for (auto it = graph.begin(root_node); it != graph.end(); ++it) {
        // 开始深度优先搜索，递归输出测试参数
        // 每当遍历到一个出度为0的节点，说明已经到了终点，DAG图会自动输出节点id序列。也就是产生测试用例
    }

    return 0;
}
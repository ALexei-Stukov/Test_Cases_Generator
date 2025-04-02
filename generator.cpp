#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <string>
using std::vector;
using std::string;
using std::cout;

#include "input_type.h"
#include "dag.hpp"

void deep_search(vector<input_type*>& input);

int main(int argc,char**argv)
{
    if(argc < 2)
    {
        cout<<"输入不足";
        return 1;
    }
    vector<input_type*> all_list;

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
            all_list.push_back(unit);
        }
        else if( line.find("range") != string::npos)
        {
            range_type* unit = new range_type(line);//类型要改
            all_list.push_back(unit);
            cout<<"执行1次range type"<<std::endl;
        }
    }
    // 关闭文件
    file.close();
    // exit(0);    //
    cout<<all_list.size()<<std::endl;

    // 针对每个输入条目，生成参数列表
    for(auto it = all_list.begin();it < all_list.end();it++)
    {
        (*it)->generate_test_cases();
    }

    // 填充进DAG图
    DAG<test_case> graph;
    test_case root_item("root");
    auto root_node = graph.add_node(root_item);   //添加虚拟的根节点，方便处理。
 
    for(auto it = all_list.begin();it < all_list.end();it++)
    {
        //遍历DAG图，找到所有出度为0的点。这些出度为0的点会依次作为新节点的父节点。
        auto temp = graph.get_all_outdegree_zero_nodes();
        //又是技术债务，这里有一些类型问题还需要处理。
        auto new_node_list = temp;
        new_node_list.clear();

        for(auto case_it = (*it)->case_list.begin();case_it < (*it)->case_list.end();case_it++)
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

    // 开始深度优先搜索，递归输出测试用例
    // 每当遍历到一个出度为0的节点，说明已经到了终点，DAG图会自动输出节点id序列。
    std::cout << "First traversal path:\n";
    for (auto it = graph.begin(root_node); it != graph.end(); ++it) {
        // 普通遍历仍正常输出每个节点的值
        // std::cout << "Visiting node: " << *it << std::endl;  --因为节点无法cout，所以这段代码取消。
    }

    return 0;
}
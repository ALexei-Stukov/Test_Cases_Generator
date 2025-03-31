#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
using std::vector;
using std::string;
using std::cout;

#include "input_type.h"

int main(int argc,char**argv)
{
    enum_type x;
    cout<<x.case_list.size()<<"";
    return 0;
}
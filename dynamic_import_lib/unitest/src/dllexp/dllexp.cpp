/*************************************************************************
	> File Name: dllexp.cpp
	> Author: wanghaiqing
	> Mail: wanghaiqing@lv.com
	> Created Time: 2019年05月13日 星期一 17时13分20秒
 ************************************************************************/
#include "../../include/dllexp/dllexp.h"
#include<iostream>
using namespace std;

namespace test 
{
    Dllexp::Dllexp()
    {

    }

    void Dllexp::hello()
    {
        std::cout<< "hello, i am dll example" << std::endl;
    }

    Strategy* create()
    {
        return new Dllexp();
    }

    void free(Strategy* strategy)
    {
        delete strategy;
    }

}

extern "C" Strategy* create_dll_example_strategy()
{
    return new test::Dllexp();
}

extern "C" void free_dll_example_strategy(Strategy* strategy)
{
    delete strategy;
}

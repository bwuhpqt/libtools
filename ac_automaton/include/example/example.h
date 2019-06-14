/*************************************************************************
	> File Name: example.cpp
	> Author: wanghaiqing
	> Mail: wanghaiqing@lv.com
	> Created Time: 2019年05月16日 星期四 11时03分49秒
 ************************************************************************/

#include<iostream>
#include "automaton/ac.h"
#include <assert.h>
#include <vector>
using namespace std;
namespace lib_tools
{
    class Example
    {
        public:
            Example()
            {
                
            }

            int32_t build()
            {
                vector<string> pattern1 = {"1", "2"};
                vector<string> pattern2 = {"23", "34"};
                vector<string> pattern3 = {"1", "2", "3","4"};
                vector<string> pattern4 = {"我","不知道", "你"};
                
                int32_t ret = 0;
                
                ret += _ac_automation.insert(pattern1);
                ret += _ac_automation.insert(pattern2);
                ret += _ac_automation.insert(pattern3);
                ret += _ac_automation.insert(pattern4);
                
                ret +=  _ac_automation.build();

                assert(ret == 0);
                
                return  ret;    
            }

            int32_t search()
            {
                //vector<string> pattern = {"23", "34","4", "5"};
                vector<string> pattern = {"我","不知道", "你", "是", "de", "1", "2", "3", "4", "5"};
                vector<vector<string>> response = _ac_automation.search(pattern);

                for (auto pattern : response)
                {
                    std::cout << "find pattern : " << std::endl;
                    for (auto str : pattern)
                    {
                        std::cout << str << " ";
                    }
                    std::cout << std::endl;
                }
                return  0;    
            }

        private:
            ACAutomaton<std::string> _ac_automation;
    };
}


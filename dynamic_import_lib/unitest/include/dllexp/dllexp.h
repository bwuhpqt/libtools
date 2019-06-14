/*************************************************************************
	> File Name: dllexp.h
	> Author: wanghaiqing
	> Mail: wanghaiqing@lv.com
	> Created Time: 2019年05月13日 星期一 16时09分44秒
 ************************************************************************/

#ifndef _DLLEXP_H
#define _DLLEXP_H

#include <string>
#include <strategy/strategy.h>

using namespace std;
using namespace lib_tools;

namespace test 
{
    class Dllexp : public Strategy
    {
        public:
            Dllexp();

            void hello();

            static Strategy* create();

            static void free(Strategy* strategy);

        private:
    };
}

#endif

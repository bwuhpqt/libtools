/*************************************************************************
	> File Name: utils.h
	> Author: wanghaiqing
	> Mail: wanghaiqing@lv.com
	> Created Time: 2019年06月18日 星期二 19时19分45秒
 ************************************************************************/

#ifndef _UTILS_UTILS_H
#define _UTILS_UTILS_H
#include <string>
#include <exception>
namespace lib_tools
{
class Predictions
{
    public:
        static void param_check(bool value, std::string exp_msg = "invalid param")
        {
            if (value)
            {
                return;
            }

            throw Exception(exp_msg);
        }

        class Exception : public std::exception
        {
            public:
                Exception(std::string msg)
                {
                    this->msg = msg;
                }  


                const char * what() const noexcept
                {
                    return msg.c_str();
                }

            private:
                std::string msg;
        };
};
}
#endif

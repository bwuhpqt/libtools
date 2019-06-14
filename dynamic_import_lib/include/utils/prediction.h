#ifndef _UTILS_PREDICTION_H_
#define _UTILS_PREDICTION_H_

#include <exception>
#include <string>

namespace lib_tools
{
    class Precondition
    {
        public:
            static void AssertTrue(bool expr)
            {
                if (!expr)
                {
                    throw Exception(std::string(EXPRESSION_NOT_TRUE));
                }
            }

            static void AssertNotNull(void* ptr)
            {
                if (nullptr == ptr)
                {
                    throw Exception(POINTER_SHOULDNOT_NULL);
                }
            }

        public:
            class Exception : public std::exception
            {
                public:
                    Exception(std::string error_msg)
                    {
                        _error_msg = error_msg;
                    }

                    virtual const char* what() const noexcept
                    {
                        return _error_msg.c_str();
                    }
                private:
                    std::string _error_msg;                
            };
        
        private:
            static const char* POINTER_SHOULDNOT_NULL;// = "pointer should not be null";
            static const char* EXPRESSION_NOT_TRUE; //= "expression value is not true";
    };
}
#endif

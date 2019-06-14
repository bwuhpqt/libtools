#ifndef INCLUDE_STRATEGY_STRATEGY_H
#define INCLUDE_STRATEGY_STRATEGY_H

#include <iostream>
#include <exception>

namespace lib_tools
{
    class Strategy
    {
        public:
            Strategy(){}
            virtual ~Strategy(){}
            virtual void hello()
            {
                std::cout << "i am basic strategy" << std::endl;
            }

        public:
        class StrategyException : public std::exception
        {
            public:

                StrategyException(std::string error_msg)
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
    };
    extern "C" Strategy* create();

    typedef Strategy* (*StrategyCreatePtr)();
    typedef void (*StrategyFreePtr)(Strategy*);
}


#endif

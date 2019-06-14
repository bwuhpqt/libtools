#ifndef INCLUDE_IMPORTER_IMPORTER_H
#define INCLUDE_IMPORTER_IMPORTER_H
#include <string>
#include <dlfcn.h>
#include "strategy/strategy.h"
namespace lib_tools
{
    class Importer
    {
        public:
            
            Importer(std::string lib_file_name, std::string create_function_name,
                std::string free_function_name);
            
            ~Importer();

            Strategy* get_strategy();

            void free(Strategy*);
        
        private:

            StrategyCreatePtr get_create_function();

            StrategyFreePtr get_free_function();

        private:
            StrategyCreatePtr _create_func;
            StrategyFreePtr _free_func;
            void* _handler;
    };
}


#endif

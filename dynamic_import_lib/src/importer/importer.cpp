#include "importer/importer.h"
#include "utils/prediction.h"
#include "dlfcn.h"
namespace lib_tools
{
    Importer::Importer(std::string lib_file_name, std::string create_function_name,
        std::string free_function_name) : _create_func(nullptr), _free_func(nullptr),
        _handler(nullptr)
    {
        _handler = dlopen(lib_file_name.c_str(), RTLD_LAZY|RTLD_GLOBAL);

        if (_handler == nullptr)
        {
            const char* error_msg = dlerror();
            throw Strategy::StrategyException(std::string("open lib file ")
                    .append(lib_file_name).append(" failed, ")
                    .append(error_msg == nullptr ? "unknow error" : error_msg));
        }

        this->_create_func = (StrategyCreatePtr) dlsym(_handler, create_function_name.c_str());
        this->_free_func = (StrategyFreePtr) dlsym(_handler, free_function_name.c_str());
        
        if (this->_create_func == nullptr || 
                this->_free_func == nullptr)
        {
            const char* error_msg = dlerror();
            throw Strategy::StrategyException(std::string("get create or free function with ")
                    .append(create_function_name).append(" and ").append(free_function_name)
                    .append(" from lib ").append(lib_file_name).append(" failed, ")
                    .append(error_msg == nullptr ? "unknow error" : error_msg));
        }
    }

    Importer::~Importer()
    {
        if (_handler  != nullptr)
        {
            dlclose(_handler);
        }
    }

    Strategy* Importer::get_strategy()
    {
        StrategyCreatePtr creater = get_create_function();
        Precondition::AssertNotNull((void*)creater);
        
        Strategy* strategy = creater();
        Precondition::AssertNotNull(strategy);

        return strategy;
    }

    void Importer::free(Strategy* strategy)
    {
        Precondition::AssertNotNull(strategy);
       StrategyFreePtr free_func = get_free_function();
       
       Precondition::AssertNotNull((void*)free_func);
       free_func(strategy);

    }

    StrategyCreatePtr Importer::get_create_function()
    {
        return this->_create_func;
    }

    StrategyFreePtr Importer::get_free_function()
    {
        return this->_free_func;
    }
}



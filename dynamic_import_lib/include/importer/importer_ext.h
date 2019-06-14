/*************************************************************************
	> File Name: importer_ext.h
	> Author: wanghaiqing
	> Mail: wanghaiqing@lv.com
	> Created Time: 2019年05月14日 星期二 10时49分05秒
 ************************************************************************/

#ifndef _IMPORTER_EXT_H
#define _IMPORTER_EXT_H

#include <string>
#include <typeinfo>
#include "importer/importer.h"
#include "utils/prediction.h"

namespace lib_tools
{
    template <typename StrategyType>
    class ImporterExt
    {
        public:
            ImporterExt(std::string lib_file_name, std::string create_function_name,
                std::string free_function_name) : 
                _importer(lib_file_name, create_function_name,
                        free_function_name)
            {}

            /*
             * shared libarary object imported, not contain type_info struct,
             * could not use dynamic_cast with rtti.
             * */
            StrategyType* get_strategy()
            {
                Strategy* org_res = _importer.get_strategy();
                Precondition::AssertNotNull(org_res);

                StrategyType* res = (StrategyType*)(org_res);
                if (res == nullptr)
                {
                   /* throw Strategy::StrategyException(std::string("strategy type ")
                            .append(typeid(org_res).name())
                            .append("could not be transformed to type ")
                            .append(typeid(res).name()));*/
                    throw Strategy::StrategyException("get strategy failed");
                }

                return res;
            }

            void free(Strategy* strategy)
            {
                Precondition::AssertNotNull(strategy);
                _importer.free(strategy);
            }

        private:
            Importer _importer;
    };
}
#endif

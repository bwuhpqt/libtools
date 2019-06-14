/*************************************************************************
	> File Name: dlltest.cpp
	> Author: wanghaiqing
	> Mail: wanghaiqing@lv.com
	> Created Time: 2019年05月13日 星期一 19时58分56秒
 ************************************************************************/

#include <iostream>
#include "gtest/gtest.h"
#include <string>
#include "importer/importer.h"
#include "importer/importer_ext.h"
#include "strategy/strategy.h"
#include "../../include/dllexp/dllexp.h"

using namespace std;
using namespace lib_tools;

namespace test
{
    class DllTest : public testing::Test
	{
		public:
            DllTest() : _strategy(nullptr), _importer(nullptr)
            {
                _lib_name = "./lib/libdllexp.so";
                _create_function = "create_dll_example_strategy";
                _free_function = "free_dll_example_strategy";

                std::cout << "start load with libname " << _lib_name << std::endl;
            }

			virtual void SetUp()
			{
                try 
                {
                    _importer = new ImporterExt<Dllexp>(_lib_name,
                            _create_function, _free_function);

                    _strategy = _importer->get_strategy();
                }
                catch (const std::exception& e)
                {
                    std::cout << "set up failed, " << e.what() << std::endl;
                    return;
                }
                catch (...)
                {
                    std::cout << "set up failed, " << dlerror() << std::endl;
                    return;
                }
                
                std::cout << "set up success with libname " << _lib_name << std::endl;
			}

			virtual void TearDown()
			{

			}

		public:
            std::string _lib_name;
            std::string _create_function;
            std::string _free_function;
            Dllexp* _strategy;
            ImporterExt<Dllexp>* _importer;

	};

	TEST_F(DllTest, Test1)
	{
		EXPECT_TRUE(_importer != nullptr);
		EXPECT_TRUE(_strategy != nullptr);
        _strategy->hello();
        _importer->free(_strategy);
	} 
}

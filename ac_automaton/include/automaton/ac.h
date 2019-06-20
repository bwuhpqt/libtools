/*************************************************************************
	> File Name: ac.h
	> Author: wanghaiqing
	> Mail: wanghaiqing@lv.com
	> Created Time: 2019年05月14日 星期二 20时18分21秒
 ************************************************************************/

#ifndef _AC_H
#define _AC_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <fstream>
#include "utils/utils.h"

namespace lib_tools
{
    template<typename KT, typename VT>
    using Map = std::unordered_map<KT, VT>;
    using std::vector;
    using std::queue;
    template <typename Type>
    class ACAutomaton
    {
        public:

            ACAutomaton();

            int32_t insert(const vector<Type>& elements);

            int32_t build();

            vector<vector<Type>> search(const vector<Type>& elements);

            bool store(std::string file_name);
            bool load(std::string file_name);

        private:
            int32_t build_goto_table();
            int32_t build_fail_table();
            int32_t build_output_table();

            /*
             * @param:
             * @return:  next node found from current witch edge,
             *           -1 when fail to find
             * */
            int64_t find_node_with_edge(int64_t current_node,
                    Type edge);

            bool is_final_stage_node(int64_t node_id);

            bool store_org_input_elements(std::ofstream& ofs);

            bool load_org_input_elements(std::ifstream& ifs);
            
        private:
            Map<int64_t, Map<Type, int64_t>>  _goto_table;
            Map<int64_t, int64_t> _fail_table;
            Map<int64_t, vector<int64_t>> _output_table;
            Map<int64_t, vector<Type>> _org_input_elements;
            int64_t _current_max_node_id;
            bool _build_start;

    };
}

#include "ac.hpp"

#endif


namespace lib_tools
{
    template <typename Type>
    ACAutomaton<Type>::ACAutomaton()
    {
        _current_max_node_id = 0;
        _build_start = false;
    } 

    template <typename Type>
    int32_t ACAutomaton<Type>::insert(const vector<Type>& elements)
    {
        Predictions::param_check(!_build_start, "build has start, could not insert");
        int64_t current_node = 0;

        for (Type element : elements)
        {
            int64_t next_node = find_node_with_edge(current_node, element);
            if (next_node == -1)
            {
                _current_max_node_id += 1;
                _goto_table[current_node][element] = _current_max_node_id;
                next_node = _current_max_node_id;
            }

            current_node = next_node;
        }

        _org_input_elements[current_node] = elements;
        //std::cout << "org input element " << current_node << std::endl;

        return 0;
    }

    template <typename Type>
    int32_t ACAutomaton<Type>::build()
    {
        Predictions::param_check(!_build_start, "build has start, could not build again");
        
        _build_start = true;

        int32_t ret = build_goto_table();
        if (ret != 0)
        {
            return -1;
        }

        ret = build_fail_table();
        if (ret != 0)
        {
            return -1;
        }

        ret = build_output_table();
        if (ret != 0)
        {
            return -1;
        }

        return 0;
    }

    template <typename Type>
    vector<vector<Type>> ACAutomaton<Type>::search(const vector<Type>& elements)
    {
        
        vector<vector<Type>> response;
        auto save_cur_id_with_final_stage = [&response, this](int64_t cur_id) -> void
        {
            if (is_final_stage_node(cur_id))
            {
                //std::cout << "start save output for " << cur_id << std::endl;
                for (int64_t node_id : this->_output_table[cur_id])
                {
                    response.push_back(_org_input_elements[node_id]);
                    //std::cout << "save output " << node_id << std::endl;
                }
            }
        };

        int64_t cur_id = 0;

        auto itr = elements.begin();
        
        while(itr != elements.end())
        {
            Type element = *itr;
            if (_goto_table[cur_id].find(element) != _goto_table[cur_id].end())
            {
                cur_id = _goto_table[cur_id][element];
                itr++;
                
                //save cur id if it is final stage
                save_cur_id_with_final_stage(cur_id);
            }
            else
            {
                cur_id = _fail_table[cur_id];
                if (cur_id == 0)
                {
                    itr++;
                }
            }
        }

        return response;
        
    }

    template <typename Type>
    int32_t ACAutomaton<Type>::build_goto_table()
    {
        /*
         * goto table has been built in inset
         * */
        return 0;
    }

    template <typename Type>
    int32_t ACAutomaton<Type>::build_fail_table()
    {
        queue<int64_t> node_queue;
        auto build_root_child_fail_table = [this, &node_queue] () -> void
        {
            auto child_itr = this->_goto_table[0].begin();
            while (child_itr != this->_goto_table[0].end())
            {
                this->_fail_table[child_itr->second] = 0;
                node_queue.push(child_itr->second);
                child_itr++;
            }
        };

        build_root_child_fail_table();

        auto build_fail_table_recurve = [this, &node_queue] () -> void
        {
            while(!node_queue.empty())
            {
                int64_t cur_node_id = node_queue.front();
                node_queue.pop();

                auto child_itr= this->_goto_table[cur_node_id].begin();

                while(child_itr != this->_goto_table[cur_node_id].end())
                {
                    if (this->_goto_table[this->_fail_table[cur_node_id]].find(child_itr->first) !=
                        this->_goto_table[this->_fail_table[cur_node_id]].end())
                    {
                        this->_fail_table[child_itr->second] =
                            this->_goto_table[this->_fail_table[cur_node_id]][child_itr->first];
                        //std::cout << "node " << child_itr->second << " fail point to " <<  
                        //    this->_goto_table[this->_fail_table[cur_node_id]][child_itr->first] << std::endl;
                    }
                    else
                    {
                        this->_fail_table[child_itr->second] = 0;
                        //std::cout << "node " << child_itr->second << " fail point to " <<  0 << std::endl;
                    }
                    
                    node_queue.push(child_itr->second);
                    
                    child_itr++;
                }
            }
        };

        build_fail_table_recurve();

        return 0;
    }

    template <typename Type>
    int32_t ACAutomaton<Type>::build_output_table()
    {
        auto build_output_table = [this](int64_t node_id) -> void
        {
            int64_t cur_id = node_id;

            this->_output_table[node_id].push_back(node_id);

            //std::cout << "in put ouput table for " << node_id << std::endl;
            int64_t next_id = _fail_table[cur_id];
            while(next_id !=  0)
            {
                //std::cout << "cur id " << cur_id << " fail point to " << next_id << std::endl;
                cur_id = next_id;
                if (is_final_stage_node(next_id))
                {
                    this->_output_table[node_id].push_back(next_id);
                    //std::cout << "in put ouput table " << next_id << std::endl;
                }

                next_id = _fail_table[cur_id];
            }
        };

        auto final_stage_itr = _org_input_elements.begin();
        while(final_stage_itr != _org_input_elements.end())
        {
            build_output_table(final_stage_itr->first);
            final_stage_itr++;
        }

        return 0;
    }

    template <typename Type>
    int64_t ACAutomaton<Type>::find_node_with_edge(int64_t current_node,
                    Type edge)
    {
        if (_goto_table.find(current_node) ==  _goto_table.end())
        {
            _goto_table[current_node];
        }

        if (_goto_table[current_node].find(edge) == _goto_table[current_node].end())
        {
            return -1;
        }

        return _goto_table[current_node][edge];
    }

    template <typename Type>
    bool ACAutomaton<Type>::is_final_stage_node(int64_t node_id)
    {
        return _org_input_elements.find(node_id) != 
            _org_input_elements.end();
    }

    template <typename Type>
    bool ACAutomaton<Type>::store(std::string file_name)
    {
        Predictions::param_check(file_name.size() != 0, "store file name size could not be empty");

        std::ofstream ofs(file_name);

        Predictions::param_check(ofs.is_open(), "ofs must be open");

        return store_org_input_elements(ofs);
    }

    template <typename Type>
    bool ACAutomaton<Type>::store_org_input_elements(std::ofstream& ofs)
    {

        for (typename Map<int64_t, vector<Type>>::iterator itr = _org_input_elements.begin();
                itr != _org_input_elements.end(); itr++)
        {
            ofs << itr->second.size() << std::endl;
            for (Type v : itr->second)
            {
                ofs << v << std::endl;
            }
        }

        return true;
    }

    template <typename Type>
    bool ACAutomaton<Type>::load(std::string file_name)
    {
        Predictions::param_check(file_name.size() != 0, "load file name must be not empty");
        Predictions::param_check(!_build_start, "load ac must be clean");

        std::ifstream ifs(file_name);

        Predictions::param_check(ifs.is_open(), "ifs must be open");

        return load_org_input_elements(ifs);
    }

    template <typename Type>
    bool ACAutomaton<Type>::load_org_input_elements(std::ifstream& ifs)
    {
        while (!ifs.eof())
        {
            size_t count = 0;
            ifs >> count;
            std::vector<Type> values;
            while (values.size() < count)
            {
                Type value;
                ifs >> value;
                values.push_back(value);
            }
            this->insert(values);
        }

        this->build();

        return true;
    }

}

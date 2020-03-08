#ifndef PARAMSET_HPP
#define PARAMSET_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace rt3 {

    using std::unique_ptr;
    using std::shared_ptr;
    using std::vector;
    using std::unordered_map;
    using std::string;

    class ParamSetItem
    {
    public:
        const unique_ptr <string []> values;
        const size_t size;

        ParamSetItem(unique_ptr<string[]> v, size_t sz = 1) : values(std::move(v)), size(sz) {}        
        ~ParamSetItem(){}
    };

    class ParamSet
    {
    public:
        unordered_map<string, std::shared_ptr<void>> params;

        ParamSet() {}
        ~ParamSet() {}

        inline void add(const string &new_key, unique_ptr<string[]> values, size_t size) {
            shared_ptr<ParamSetItem> sptr = std::make_shared<ParamSetItem>(std::move(values), 1);
            shared_ptr<void> vptr = std::move(sptr);
            params.insert({new_key, vptr});
        }
        
        inline bool erase(const string $target_key) { 
             params.clear();
             return true;
        }
        // inline const string * find_array(const string &target_key, size_t &size) const {}
        inline const string & find_one(const string &target_key, const string &d) const { 
            auto pit = params.find(target_key);

            if( pit == params.end()) return d;  // não encontrou a chave
            
            std::shared_ptr<ParamSetItem> sptr = std::static_pointer_cast<ParamSetItem>(pit->second);
            return sptr->values[0];
        }

        inline void clear() {params.clear();}
        // inline std::vector <std::string> report_unsued() const
    };

}

#endif
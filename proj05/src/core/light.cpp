#include "light.hpp"

namespace rt3 {
    bool is_ambient(int flag) {
        return flag & (int)light_flag_e::ambient;
    }

    void Light::preprocess(const Scene&) {}

}
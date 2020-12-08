#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "core/surfel.hpp"
#include "core/scene.hpp"
#include "core/visibility_tester.hpp"

namespace rt3 {

    enum class light_flag_e : int {
        point = 1,
        directional = 2,
        area = 4,
        ambient = 8,
        spot = 16
    };

    bool is_ambient(int flag);

    class Light {
    public:
        light_flag_e flags;
        Vector3 L;
    
        Light() {};
        Light(light_flag_e flag) : flags(flag) {};
        virtual ~Light() {};
        /// Retorna a intensidade da luz, direção e o teste oclusão.
        virtual rgb sample_Li(const Surfel& hit , Vector3* wi, VisibilityTester* vis) = 0;
        virtual void preprocess(const Scene&);
    };

}

#include "light/point_light.hpp"

#endif
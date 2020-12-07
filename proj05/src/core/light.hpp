#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "core/surfel.hpp"
#include "core/visibility_tester.hpp"

namespace rt3 {

    class Scene;

    enum class light_flag_e : int {
        point = 1,
        directional = 2,
        area = 4,
        ambient = 8,
        spot = 16
    };

    bool is_ambient(int flag) ;

    class Light {
    public:
        light_flag_e flags;
    public:
        virtual ~Light() {};
        Light(int flags);
        /// Retorna a intensidade da luz, direção e o teste oclusão.
        virtual rgb sample_Li(const Surfel& hit /*in*/,
            Vector3* wi/*out*/,
            VisibilityTester* vis/*out*/) = 0;
        virtual void preprocess(const Scene&) {};
    };

}

#endif
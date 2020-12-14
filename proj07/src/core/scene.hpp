#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "background.hpp"
#include "primitive.hpp"
#include "light.hpp"

namespace rt3 {
    class Light;
    
    class Scene
    {
    public:
        std::shared_ptr<Background> background;
        std::shared_ptr<Primitive> primitive;
        std::vector<std::shared_ptr<Light>> lights;

        Scene() {}
        Scene(std::shared_ptr<Background> bg) : background(bg) {}
        Scene(std::shared_ptr<Background> bg, std::shared_ptr<Primitive> prim) : background(bg), primitive(prim) {}
        Scene(std::shared_ptr<Background> bg, std::shared_ptr<Primitive> prim, std::vector<std::shared_ptr<Light>>& ls ) : background(bg), primitive(prim), lights(ls) {}
        ~Scene() {}

        // bool intersect( const Ray& r, Surfel *isect ) const;
        bool intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const;

        /*! A faster version that only determines whether there is an intersection or not;
         * it doesn't calculate the intersection info.
         */
        bool intersect_p(const Ray& ray, float& t_min, float& t_max) const;

        // bool intersect_p( const Ray& r ) const;

        void print();
    };

}

#endif
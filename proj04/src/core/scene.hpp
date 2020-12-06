#ifndef SCENE_HPP
#define SCENE_HPP

#include <forward_list>

#include "background.hpp"
#include "primitive.hpp"

namespace rt3 {
    class Scene
    {
    public:
        std::shared_ptr<Background> background;
        std::shared_ptr<Primitive> primitive;

        Scene() {}
        Scene(std::shared_ptr<Background> bg) : background(bg) {}
        Scene(std::shared_ptr<Background> bg, std::shared_ptr<Primitive> prim) : background(bg), primitive(prim) {}
        ~Scene() {}

        bool intersect( const Ray& r, Surfel *isect ) const;
        /*! A faster version that only determines whether there is an intersection or not;
         * it doesn't calculate the intersection info.
         */
        bool intersect_p( const Ray& r ) const;

        void print();
    };

}

#endif
#ifndef AGGREGATE_PRIMITIVE_HPP
#define AGGREGATE_PRIMITIVE_HPP

#include "core/primitive.hpp"
#include <stdexcept>

namespace rt3 {
    class AggregatePrimitive : public Primitive {
    public:
        AggregatePrimitive() {};
        virtual ~AggregatePrimitive() = default;

        const Material* get_material() const { 
            throw std::logic_error("An aggregate must not have an material associated with it;"); 
        }
    };
}

#endif
#include "BVHAccel.hpp"

namespace rt3 {

    inline int random_int(int min, int max) {
        // Returns a random integer in [min,max].
        return static_cast<int>(min + (max + 1 - min) * rand() / (RAND_MAX + 1.0));
    }

    BVHAccel::BVHAccel(
        const std::vector<std::shared_ptr<Primitive>>& src_objects,
        size_t start, size_t end) {
        auto objects = src_objects; // Create a modifiable array of the source scene objects

        int axis = random_int(0, 2);
        auto comparator = (axis == 0) ? box_x_compare
            : (axis == 1) ? box_y_compare
            : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            left = right = objects[start];
        }
        else if (object_span == 2) {
            if (comparator(objects[start], objects[start + 1])) {
                left = objects[start];
                right = objects[start + 1];
            }
            else {
                left = objects[start + 1];
                right = objects[start];
            }
        }
        else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + object_span / 2;
            left = std::make_shared<BVHAccel>(objects, start, mid);
            right = std::make_shared<BVHAccel>(objects, mid, end);
        }

        aabb box_left, box_right;
        float hit1=0.f, hit2=0.f;

        if (!left->bounding_box(hit1, hit2, box_left)
            || !right->bounding_box(hit1, hit2, box_right)
            )
            std::cerr << "No bounding box in bvh_node constructor.\n";

        box = surrounding_box(box_left, box_right);
    }

    bool BVHAccel::intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const {
        if (!box.intersect_p(ray, t_min, t_max))
            return false;

        bool hit_left = left->intersect(ray, t_min, t_max, sf);
        bool hit_right = right->intersect(ray, t_min, (hit_left ? ray.t_max : t_max), sf);

        return hit_left || hit_right;
    }

    bool BVHAccel::intersect_p(const Ray& ray, float& t_min, float& t_max) const {
        if (!box.intersect_p(ray, t_min, t_max))
            return false;

        bool hit_left = left->intersect_p(ray, t_min, t_max);
        bool hit_right = right->intersect_p(ray, t_min, (hit_left ? ray.t_max : t_max));

        return hit_left || hit_right;
    }

    bool BVHAccel::bounding_box(float time0, float time1, aabb& output_box) const {
        output_box = box;
        return true;
    }

    bool box_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b, int axis) {
        aabb box_a;
        aabb box_b;

        if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
            std::cerr << "No bounding box in bvh_node constructor.\n";

        return box_a.min().e[axis] < box_b.min().e[axis];
    }

    bool box_x_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
        return box_compare(a, b, 0);
    }

    bool box_y_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
        return box_compare(a, b, 1);
    }

    bool box_z_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
        return box_compare(a, b, 2);
    }
   
    Point3 BVHAccel::world_bounds() const {
        std::cerr << "not implemented\n";
        throw std::logic_error("not implemented");
    }

    // bool BVHAccel::bounding_box(float t0, float t1, aabb& box) const {
    //     std::cerr << "not implemented\n";
    //     throw std::logic_error("not implemented");
    // }

    // bool BVHAccel::intersect(const Ray& ray, Surfel* sf) const {

    //     bool result = false;

    //     for (auto prim : primitives) {
    //         if (prim->intersect(ray, sf)) {
    //             result = true;
    //         }
    //     }
    //     return result;

    // }

    // bool BVHAccel::intersect_p(const Ray& ray, float& hit1, float& hit2) const {
    //     for (auto p : primitives) {
    //         if (p->intersect_p(ray, hit1, hit2)) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }
}
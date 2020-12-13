#ifndef PRIMITIVE_TRIANGLE_HPP
#define PRIMITIVE_TRIANGLE_HPP

#include <vector>
#include <memory>
#include <ctime>
#include <chrono>
#include <iterator>

using std::vector;
using std::shared_ptr;

#include "shape.hpp"
#include "core/paramset.hpp"
#include "core/parser_tags.hpp"



#include "external/tiny_obj_loader.hpp"
// #include "core/surfel.hpp"
// #include "core/ray.hpp"

namespace rt3 {

    using std::vector;
    using std::shared_ptr;

    // // class Primitive;
    // class Triangle : public Shape {
    // public:


    //     // Sphere(string type, float r, Point3 c) : Shape(type), r(r), c(c) {}
    //     Triangle(bool flip_n) : Shape(flip_n) {}
    //     virtual ~Triangle() = default;

    //     Point3 world_bounds() const;

    //     bool intersect(const Ray& ray, float* t_hit, Surfel* sf) const;
    //     bool intersect_p(const Ray& ray) const;

    //     void print();
    // };


/// This struct implements an indexd triangle mesh database.
    struct TriangleMesh {
        int n_triangles; //!< # of triangles in the mesh.
        // The size of the three lists below should be 3 * nTriangles. Every 3 values we have a triangle.
        std::vector< int > vertex_indices;  //!< The list of indices to the vertex list, for each individual triangle.
        std::vector< int > normal_indices;  //!< The list of indices to the normals list, for each individual triangle.
        std::vector< int > uvcoord_indices; //!< The list of indices to the UV coord list, for each individual triangle.

        // Here comes the data associated with each vertex. WARNING: The length of the vectors below may differ.
        std::vector< Point3 > vertices;  //!< The 3D geometric coordinates
        std::vector< Point3 > normals;  //!< The 3D normals.
        std::vector< Point2 > uvcoords; //!< The 2D texture coordinates.

        // Regular constructor (almost all data is imported via move semantics).
        TriangleMesh() {/*empty*/ };
        /// Copy constructor disabled
        TriangleMesh(const TriangleMesh&) = delete;
        /// Assign operator disabled.
        TriangleMesh& operator=(const TriangleMesh&) = delete;
        /// Move constructor.
        TriangleMesh(TriangleMesh&& other) = delete;
    };


    /// Represents a single triangle.
    class Triangle : public Shape {
    public:
        int* v; //!< Pointer to the vertex index array stored in the triangle mesh database. 
        // After the proper triangle initialization, we may access vertices with v[0], v[1], and v[2]
        int* n; //!< Pointer to the normal index array stored in the triangle mesh database.
        // After the proper triangle initialization, we may access normals with n[0], n[1], and n[2]
        int* uv;//!< Pointer to the UV coord index array stored in the triangle mesh database.
        // After the proper triangle initialization, we may access UV coords with uv[0], uv[1], and uv[2]

        std::shared_ptr<TriangleMesh> mesh; //!< This is the **indexed triangle mesh database** this triangle is linked to.
        bool backface_cull;            //!< Set it `true` to activate backface culling.

        // The single constructor, that receives the mesh, this triangle id, and an indication for backface culling.
        Triangle(std::shared_ptr<TriangleMesh> mesh, int tri_id, bool bfc = true)
            : Shape("triangle"), mesh{ mesh }, backface_cull{ bfc }
        {
            // This is just a shortcut to access this triangle's data stored in the mesh database.
            v = &mesh->vertex_indices[3 * tri_id];
            n = &mesh->normal_indices[3 * tri_id];
            uv = &mesh->uvcoord_indices[3 * tri_id];
        }
        /// Return the triangle's bounding box.
        Point3 world_bounds() const;

        /// The regular intersection methods, as defined in the Shape parent class.
        bool intersect(const Ray& ray, float* thit, Surfel* isect) const;
        bool intersect_p(const Ray& ray) const;

        /// This friend function helps us debug the triangles, if we want to.
        friend std::ostream& operator<<( std::ostream& os, const Triangle & t );
        void print();

    };
}
/// This is the entry point for the client. This function begins the process of reading a triangle mesh.
std::vector<std::shared_ptr<rt3::Shape>>
create_triangle_mesh_shape(bool flip_normals, const rt3::ParamSet& ps);

/// This is the function that actually creates the mesh database and the triangles, ans store them in a Shape list.
std::vector<std::shared_ptr<rt3::Shape>> create_triangle_mesh(std::shared_ptr<rt3::TriangleMesh>, bool);

/// Internal function that calls the tinyobjloader api to read the OBJ data into memory.
bool load_mesh_data(const std::string& filename, bool rvo, bool cn, bool fn, std::shared_ptr<rt3::TriangleMesh> md);

/// This function essentially convertes the mesh data from the tinyobjloader internal data structure to our mesh data structure.
void extract_obj_data( const tinyobj::attrib_t& attrib,
                       const std::vector<tinyobj::shape_t>& shapes,
                       bool rvo, bool cn, bool fn, std::shared_ptr<rt3::TriangleMesh> md );



#endif
#include "triangle.hpp"

using rt3::Triangle;
using rt3::TriangleMesh;
using rt3::Shape;
using rt3::ParamSet;

bool maxHigherPoint(const Vector3& v1, const Vector3& v2) {
    constexpr short Y{ 1 };

    return v1[Y] > v2[Y];
}

namespace rt3 {

    Point3 Triangle::world_bounds() const { throw std::logic_error("not implemented"); }

    bool Triangle::bounding_box(float t0, float t1, aabb& box) const {
        Vector3 p0 = mesh->vertices[v[0]];
        Vector3 p1 = mesh->vertices[v[1]];
        Vector3 p2 = mesh->vertices[v[2]];

        std::vector<Vector3> points{ p0, p1, p2 };
        std::sort(points.begin(), points.end(), maxHigherPoint);
        box = aabb(points[0], points[1]);
        return true;
    }


    bool Triangle::intersect(const Ray& ray, float& hit1, float& hit2, Surfel* sf) const {
        constexpr short X{ 0 };
        constexpr short Y{ 1 };
        constexpr short Z{ 2 };

        float a = mesh->vertices[v[0]][X] - mesh->vertices[v[1]][X];
        float b = mesh->vertices[v[0]][Y] - mesh->vertices[v[1]][Y];
        float c = mesh->vertices[v[0]][Z] - mesh->vertices[v[1]][Z];

        float d = mesh->vertices[v[0]][X] - mesh->vertices[v[2]][X];
        float e = mesh->vertices[v[0]][Y] - mesh->vertices[v[2]][Y];
        float f = mesh->vertices[v[0]][Z] - mesh->vertices[v[2]][Z];

        float g = ray.d[X];
        float h = ray.d[Y];
        float i = ray.d[Z];

        float j = mesh->vertices[v[0]][X] - ray.o[X];
        float k = mesh->vertices[v[0]][Y] - ray.o[Y];
        float l = mesh->vertices[v[0]][Z] - ray.o[Z];

        float M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

        if (M == 0.f) {
            // std::cout << "[Triangle::intersect] division by 0\n";
            // throw std::logic_error("division by 0");
            return false;
        }

        // compute t
        float t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c));
        t = t / M;
        // if (t < ray.t_min || (ray.t_max > 0.f && t > ray.t_max)) {
        //     return false;
        // }

        if (t < ray.t_min || t > ray.t_max) {
            // if (!(t > ray.t_min && (ray.t_max <= 0.f || t <= ray.t_max))) {
            return false;
        }

        // compute gama
        float gama = i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c);
        gama = gama / M;
        if (gama < 0.f || gama > 1.f) {
            return false;
        }

        // compute beta
        float beta = j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g);
        beta = beta / M;
        if (beta < 0.f || beta >(1.f - gama)) {
            return false;
        }

        // update surfel/ray
        ray.t_max = t;
        sf->t = t;
        sf->p = ray(t);

        // TODO calcular a normal
        Vector3 normal = mesh->normals[n[0]];
        sf->n = normal;

        return true;
    }

    bool Triangle::intersect_p(const Ray& ray, float& hit1, float& hit2) const {
        aabb box;
        bounding_box(0.f, 0.f, box);
        return (box.intersect_p(ray, hit1, hit2));
    }

    void Triangle::print() {
    }
}

/// To help debug triangles.
std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
    constexpr short X{ 0 };
    constexpr short Y{ 1 };
    constexpr short Z{ 2 };

    os << "    + V0: ("
        << t.mesh->vertices[t.v[0]][X] << ", "
        << t.mesh->vertices[t.v[0]][Y] << ", "
        << t.mesh->vertices[t.v[0]][Z] << ")\n"
        << "    + V1: ("
        << t.mesh->vertices[t.v[1]][X] << ", "
        << t.mesh->vertices[t.v[1]][Y] << ", "
        << t.mesh->vertices[t.v[1]][Z] << ")\n"
        << "    + V2: ("
        << t.mesh->vertices[t.v[2]][X] << ", "
        << t.mesh->vertices[t.v[2]][Y] << ", "
        << t.mesh->vertices[t.v[2]][Z] << ")\n"

        << "    + N0: ("
        << t.mesh->normals[t.n[0]][X] << ", "
        << t.mesh->normals[t.n[0]][Y] << ", "
        << t.mesh->normals[t.n[0]][Z] << ")\n"
        << "    + N1: ("
        << t.mesh->normals[t.n[1]][X] << ", "
        << t.mesh->normals[t.n[1]][Y] << ", "
        << t.mesh->normals[t.n[1]][Z] << ")\n"
        << "    + N2: ("
        << t.mesh->normals[t.n[2]][X] << ", "
        << t.mesh->normals[t.n[2]][Y] << ", "
        << t.mesh->normals[t.n[2]][Z] << ")\n"

        << "    + UV0: ("
        << t.mesh->uvcoords[t.uv[0]].first << ", "
        << t.mesh->uvcoords[t.uv[0]].second << ")\n"
        << "    + UV1: ("
        << t.mesh->uvcoords[t.uv[1]].first << ", "
        << t.mesh->uvcoords[t.uv[1]].second << ")\n"
        << "    + UV2: ("
        << t.mesh->uvcoords[t.uv[2]].first << ", "
        << t.mesh->uvcoords[t.uv[2]].second << ")\n";

    // << "    + UV0: ("
    // << t.mesh->uvcoords[ t.uv[0] ][X] << ", "
    // << t.mesh->uvcoords[ t.uv[0] ][Y] << ")\n"
    // << "    + UV1: ("
    // << t.mesh->uvcoords[ t.uv[1] ][X] << ", "
    // << t.mesh->uvcoords[ t.uv[1] ][Y] << ")\n"
    // << "    + UV2: ("
    // << t.mesh->uvcoords[ t.uv[2] ][X] << ", "
    // << t.mesh->uvcoords[ t.uv[2] ][Y] << ")\n";

    return os;
}


// This is the function called by the API to create a triangle mesh shape.
/*
 * This is the entry-point function for the client code.
 * This function decodes the `ParamSet` data and, based on that, it either
 * (1) creates a triangle mesh manually (from the XML attributes), or
 * (2) calls another function to load an OBJ file and create the triangle mesh.
 *
 * @param flip_normals This flag asks to invert the normal of all triangles. This is a global flag, set by a API command.
 * @param ps The ParamSet object sent from the client code with all the information related to the triangle mesh read from the scene file.
 *
 * @return The list of Shape (triangles) that we read from the scene file.
 */
vector< shared_ptr<Shape> >
create_triangle_mesh_shape(bool flip_normals, const ParamSet& ps)
{
    bool bkfc_on{ true };                 // Controls whether the backface cull should be done or not.
    bool reverse_vertex_order{ false };   // If this is true, we store vertices in reverse order inside the mesh.
    bool compute_normals{ false };        // Indicate whether we need to calculate the triangle's normals manually.

    // This is a collection of data structures passed between function calls.
    // This structure may be filled in with information from a OBJ file
    // or from the XML attributes extracted from the scene file itself.
    shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(); // Default Ctro.

    // Retrieve filename.
    string filename = ps.find_one<string>(ParserTags::INCLUDE_FILENAME, ""); // Retrieving data associated with 'filename' attrib.
    // Retrieve backface ON/OFF
    bkfc_on = ps.find_one<bool>(ParserTags::OBJECT_TMESH_BCULL, true);
    // Retrieve Reverse vertex order ON/OFF
    reverse_vertex_order = ps.find_one<bool>(ParserTags::OBJECT_TMESH_RVO, false);
    // Retrieve compute normals flag
    compute_normals = ps.find_one<bool>(ParserTags::OBJECT_TMESH_CNOR, true);

    // Here we have only two option: read mehs data from OBJ file or from the ParamSet.
    if (filename != "") { // Read mesh data from an OBJ file provided in the scene file.
        // Call our auxiliary function that interfaces with tinyobjloader API.
        if (load_mesh_data(filename, reverse_vertex_order, compute_normals, flip_normals, mesh)) {

            std::cout << ">>> Mesh data successfuly loaded!\n";
        }
        else {

            std::cout << ">>> Mesh data loading failed!\n";
        }
        // std::cerr << "read .obj: not implemented\n";
        // throw std::logic_error("read .obj: not implemented");
    }
    else { // This means we must read the mesh data from the scene file, not from the OBJ file.

        // TODO: retrieve the attributes of the triangle mesh present in the XML scene file.
        // 
        // Here you must retrieve from the ParamSet all the data that might appear in a trianglemesh object.
        // Usually these are the vertices, normals, and indices.
        // 
        // You should read all the data into the `tri_mesh_data` object so that the function call below works,
        // regardless if the data came from the OBJ file or was read directly from the scene file.


        mesh->n_triangles = ps.find_one<int>(ParserTags::OBJECT_TMESH_NTRIANGLES, 0);

        std::stringstream sstr;

        sstr << ps.find_one<string>(ParserTags::OBJECT_TMESH_VERTICES, "");
        while (sstr) {
            float x, y, z;
            sstr >> x >> y >> z;
            mesh->vertices.push_back(Vector3(x, y, z));
        }

        sstr.clear();
        sstr << ps.find_one<string>(ParserTags::OBJECT_TMESH_NORMALS, "");
        while (sstr) {
            float x, y, z;
            sstr >> x >> y >> z;
            mesh->normals.push_back(Vector3(x, y, z));
        }

        sstr.clear();
        sstr << ps.find_one<string>(ParserTags::OBJECT_TMESH_UV, "");
        while (sstr) {
            float x, y;
            sstr >> x >> y;
            mesh->uvcoords.push_back(std::pair<int, int>(x, y));
        }

        // INDICES ===============================================================
        sstr.clear();
        sstr << ps.find_one<string>(ParserTags::OBJECT_TMESH_INDICES, "");
        while (sstr) {
            int v1;
            sstr >> v1;
            mesh->normal_indices.push_back(v1);
            mesh->vertex_indices.push_back(v1);
            mesh->uvcoord_indices.push_back(v1);
        }


    }

    // At this point, the tri_mesh_data object has already been filled in with data coming either from a OBJ file or from the scene file.
    return create_triangle_mesh(mesh, bkfc_on); // Note the use of move semantics here.
}


/// This function calls the basic tinyobjloader loading function and stores all the data into the tinyobjloader's internal data structures.
bool load_mesh_data(const std::string& filename, bool rvo, bool cn, bool fn, shared_ptr<TriangleMesh> md)
{
    // Default load parameters
    const char* basepath = NULL;
    bool triangulate = true;

    std::cout << "Loading " << filename << std::endl;

    // This is the tinyobj internal data structures.
    tinyobj::attrib_t attrib; // Hold all the data, such as vertex, normals, UV coords
    std::vector<tinyobj::shape_t> shapes; // Represents a collection of faces, grouped in a unit.
    std::vector<tinyobj::material_t> materials; // Materials, NOT USED HERE.

    // Warnings and Error values.
    std::string warn;
    std::string err;

    // Timing loading.
    //================================================================================
    auto start = std::chrono::steady_clock::now();
    //================================================================================
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(),
        basepath, triangulate);
    //================================================================================
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    //Store the time difference between start and end
    std::chrono::duration<double> diff = end - start;

    // Milliseconds (10^-3)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::milli>(diff).count()
        << " ms" << std::endl;

    // Nanoseconds (10^-9)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::nano>(diff).count()
        << " ns" << std::endl;

    // Seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    std::cout << "\t\t>>> " << diff_sec.count() << " s" << std::endl;
    //================================================================================

    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }

    if (!ret) {
        std::cout << "Failed to load/parse .obj.\n";
        return false;
    }

    // Let us now "convert" or "migrate" the data from tinyobjloader data structure into out mesh data.
    extract_obj_data(attrib, shapes, // TinyObjeLoader data structures (IN)
        rvo, cn, fn,    // Mesh modifiers (IN)
        md);           // Reference to the mesh data to fill in. (OUT)

    return true;
}

/// This is the function that converts from the tinyobjloader's internal storage to our mesh data organization.
void extract_obj_data(const tinyobj::attrib_t& attrib,
    const std::vector<tinyobj::shape_t>& shapes,
    bool rvo, bool cn, bool fn, /* OUT */ shared_ptr<TriangleMesh> md)
{
    std::cout << "-- SUMMARY of the OBJ file --\n";
    std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
    std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
    std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2) << std::endl;
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "-----------------------------\n";

    // Retrieve the complete list of vertices.
    auto n_vertices{ attrib.vertices.size() / 3 };
    for (auto idx_v{ 0u }; idx_v < n_vertices; idx_v++)
    {
        std::cout << "   v[" << static_cast<long>(idx_v) << "] = ( "
            << static_cast<double>(attrib.vertices[3 * idx_v + 0]) << ", "
            << static_cast<double>(attrib.vertices[3 * idx_v + 1]) << ", "
            << static_cast<double>(attrib.vertices[3 * idx_v + 2]) << " )\n";

        // Store the vertex in the mesh data structure.
        md->vertices.push_back(Point3{ attrib.vertices[3 * idx_v + 0],
                                        attrib.vertices[3 * idx_v + 1],
                                        attrib.vertices[3 * idx_v + 2] });
    }


    // Read the normals
    // TODO: flip normals if requested.
    float flip = (fn) ? -1 : 1;
    auto n_normals{ attrib.normals.size() / 3 };

    // Do we need to compute the normals? Yes only if the user requeste or there are no normals in the file.
    // if ( cn == true or n_normals == 0)
    // {
    //    // TODO: COmpute normals here.
    //    // compute_normals();
    // }
    //else {// Read normals from file. This corresponds to the entire 'for' below.

    // Traverse the normals read from the OBJ file.
    for (auto idx_n{ 0u }; idx_n < n_normals; idx_n++)
    {
        std::cout << "   n[" << static_cast<long>(idx_n) << "] = ( "
            << static_cast<double>(attrib.normals[3 * idx_n + 0]) << ", "
            << static_cast<double>(attrib.normals[3 * idx_n + 1]) << ", "
            << static_cast<double>(attrib.normals[3 * idx_n + 2]) << " )\n";

        // Store the normal.
        md->normals.push_back(Vector3{ attrib.normals[3 * idx_n + 0] * flip,
                                        attrib.normals[3 * idx_n + 1] * flip,
                                        attrib.normals[3 * idx_n + 2] * flip });
    }

    // Read the complete list of texture coordinates.
    auto n_texcoords{ attrib.texcoords.size() / 2 };
    for (auto idx_tc{ 0u }; idx_tc < n_texcoords; idx_tc++)
    {
        std::cout << "   t[" << static_cast<long>(idx_tc) << "] = ( "
            << static_cast<double>(attrib.texcoords[2 * idx_tc + 0]) << ", "
            << static_cast<double>(attrib.texcoords[2 * idx_tc + 1]) << " )\n";

        // Store the texture coords.
        md->uvcoords.push_back(Point2f{ attrib.texcoords[2 * idx_tc + 0],
                                         attrib.texcoords[2 * idx_tc + 1] });
    }

    // Read mesh connectivity and store it as lists of indices to the real data.
    auto n_shapes{ shapes.size() };
    md->n_triangles = 0; // We must reset this here.
    // In case the OBJ file has the triangles organized in several shapes or groups, we
    // ignore this and store all triangles as a single mesh dataset.
    // This is why we need to reset the triangle count here.
    for (auto idx_s{ 0u }; idx_s < n_shapes; idx_s++)
    {
        std::cout << "The shape[" << idx_s << "].name = " << shapes[idx_s].name << '\n';
        std::cout << "Size of shape[" << idx_s << "].mesh.indices: "
            << static_cast<unsigned long>(shapes[idx_s].mesh.indices.size()) << '\n';
        std::cout << "shape[" << idx_s << "].num_faces: "
            << static_cast<unsigned long>(shapes[idx_s].mesh.num_face_vertices.size()) << '\n';

        // For each face print out the indices lists.
        size_t index_offset = 0;
        // # of triangles for this "shape" (group).
        // NOTE that we are accumulate the number of triangles coming from the shapes present in the OBJ file.
        md->n_triangles += shapes[idx_s].mesh.num_face_vertices.size();
        for (auto idx_f{ 0 }; idx_f < md->n_triangles; idx_f++)
        {
            // Number of vertices per face (always 3, in our case)
            size_t fnum = shapes[idx_s].mesh.num_face_vertices[idx_f];

            std::cout << "  face[" << idx_f << "].fnum = " << static_cast<unsigned long>(fnum) << '\n';

            // TODO: Invert order of vertices if flag is on. (DONE!)
            if (rvo == true) {
                std::cout << "Reverse order\n";
                // For each vertex in the face print the corresponding indices
                for (int v = fnum - 1; v >= 0; v--)
                {
                    tinyobj::index_t idx = shapes[idx_s].mesh.indices[index_offset + v];
                    std::cout << "    face[" << idx_f << "].v[" << v << "].indices = "
                        << idx.vertex_index << "/" << idx.normal_index << "/" << idx.texcoord_index << '\n';
                    // Add the indices to the global list of indices we need to pass on to the mesh object.
                    md->vertex_indices.push_back(idx.vertex_index);
                    md->normal_indices.push_back(idx.normal_index);
                    md->uvcoord_indices.push_back(idx.texcoord_index);
                }
            }
            else { // Keep the original vertex order
                // For each vertex in the face get the corresponding indices
                for (size_t v = 0; v < fnum; v++)
                {
                    tinyobj::index_t idx = shapes[idx_s].mesh.indices[index_offset + v];
                    std::cout << "    face[" << idx_f << "].v[" << v << "].indices = "
                        << idx.vertex_index << "/" << idx.normal_index << "/" << idx.texcoord_index << '\n';
                    // Add the indices to the global list of indices we need to pass on to the mesh object.
                    // This goes to the mesh data structure.
                    md->vertex_indices.push_back(idx.vertex_index);
                    md->normal_indices.push_back(idx.normal_index);
                    md->uvcoord_indices.push_back(idx.texcoord_index);
                }
            }

            // Advance over to the next triangle.
            index_offset += fnum;
        }
    }

    std::cout << "This is the list of indices: \n";

    std::cout << "   + Vertices [ ";
    std::copy(md->vertex_indices.begin(), md->vertex_indices.end(), std::ostream_iterator< int >(std::cout, " "));
    std::cout << "]\n";

    std::cout << "   + Normals [ ";
    std::copy(md->normal_indices.begin(), md->normal_indices.end(), std::ostream_iterator< int >(std::cout, " "));
    std::cout << "]\n";

    std::cout << "   + UV coords [ ";
    std::copy(md->uvcoord_indices.begin(), md->uvcoord_indices.end(), std::ostream_iterator< int >(std::cout, " "));
    std::cout << "]\n";
}

/// This function creates the internal data structure, required by the RT3.
vector<shared_ptr<Shape>>
create_triangle_mesh(shared_ptr<TriangleMesh> mesh, bool backface_cull)
{
    // List of shapes (triangles) we need to return to the client.
    vector<shared_ptr<Shape>> tris;
    // Create the triangles, which are just references to the mesh database.
    for (int i = 0; i < mesh->n_triangles; ++i)
        tris.push_back(std::make_shared<Triangle>(mesh, i, backface_cull));

    return tris;
}

#pragma once
#include <vector>
#include <tuple>
#include "Common.h"

class Face {
public:
    Face() = default;
    Face(int a, int b, int c, int d) {
        v[0] = a;
        v[1] = b;
        v[2] = c;
        v[3] = d;
    }

    int v[4] = { -1, -1, -1, -1 };   // The vertex index of the face
 
    int& operator [] (int i) {
        return v[i];
    }

    int operator [] (int i) const {
        return v[i];
    }
};

// -----------------------------------------------------------------------------
// Mesh: The class that keeps the geometric information
// -----------------------------------------------------------------------------
class Mesh {
public:
    // ----------------
    // Main functions
    // ----------------
    Mesh();
    // FaceIntersection: return the tuple of (intersected_face_index, intersected_point)
    // If no intersection is found, interseted_face_index is -1.
    std::tuple<int, glm::vec3> FaceIntersection(const glm::vec3& o, const glm::vec3& d);

    void Draw();
    void ApplyTransform(const glm::mat4x4& transform);
    void ApplyTransform(const float* transform);
    void ApplyFaceTransform(int face_index, const glm::mat4x4& transform);
    void ApplyFaceTransform(int face_index, const float* transform);
    void CommitTransform();
    void UpdateInformation(bool commit = false);

    void SubdivideFace(const glm::vec3& o, const glm::vec3& d);
    void GenExtrudeFace(const glm::vec3& o, const glm::vec3& d);

    // Public members
    std::vector<glm::vec3> vertices_;
    std::vector<Face> faces_;
    glm::vec3 center_ = glm::vec3(0.f, 0.f, 0.f);

    // No need to use the following members
private:
    glm::vec3 local_x_ = glm::vec3(1.f, 0.f, 0.f);
    glm::vec3 local_y_ = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 local_z_ = glm::vec3(0.f, 0.f, 1.f);
    glm::mat3x3 local_base_ = glm::mat3x3(1.f);

    glm::vec3 local_coord_min_ = glm::vec3(-1.f, -1.f, -1.f);
    glm::vec3 local_coord_max_ = glm::vec3( 1.f,  1.f,  1.f);
    glm::vec3 local_bound_vertices_[8];

    glm::vec3 world_coord_min_ = glm::vec3(-1.f, -1.f, -1.f);
    glm::vec3 world_coord_max_ = glm::vec3(-1.f, -1.f, -1.f);
    glm::vec3 world_bound_vertices_[8];

    glm::mat4x4 active_transform_ = glm::mat4x4(1.f);

    int active_face_index_ = -1;
    glm::mat4x4 active_face_transform_ = glm::mat4x4(1.f);
    
    glm::vec3 translation_drag_point_;
    float translation_drag_depth_ = -1.f;

    const glm::vec3 light_direction_ = glm::vec3(0.26726124f, 0.5345225f, 0.8017837f); // Constant light direction for simple illumination.
};
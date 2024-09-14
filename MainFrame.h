#pragma once
#include "Common.h"
#include "Mesh.h"
#include "Camera.h"

// -----------------------------------------------------------------------------
// Editing mode definition
// -----------------------------------------------------------------------------
#define OBJ_ROTATION 1                          // object rotation
#define OBJ_TRANSLATION 2                       // object translation
#define OBJ_SUBDIVIDE 3                         // object face subdivision
#define OBJ_EXTRUDE 4                           // object face extrusion

// -----------------------------------------------------------------------------
// MainFrame: The class controlling the overall rendering & interaction logic
// -----------------------------------------------------------------------------
class MainFrame {
public:
    // ---------------
    // Main functions
    // ---------------
    MainFrame() = default;

    void ProcessInput(GLFWwindow* window);                                          // Function to handle all user inputs

    void LeftMouseClick(float x, float y);                                          // Called once left mouse clicked
    void LeftMouseMove(float start_x, float start_y, float end_x, float end_y);     // Called once left mouse moving
    void LeftMouseRelease();                                                        // Called once left mouse released
    void RightMouseClick(float x, float y);                                         // Similar as the above
    void RightMouseMove(float start_x, float start_y, float end_x, float end_y);
    void RightMouseRelease();

    void DrawScene();
    void VisualizeWorldSpace();
    void MainLoop();
    
    // ---------------------------
    // Some other useful functions
    // ---------------------------
    glm::vec3 Camera2World(const glm::vec3& x, float w = 1.f);                       // Transform the coordinate from camera/eye space to world space
    glm::vec3 World2Camera(const glm::vec3& x, float w = 1.f);                       // Transform the coordinate from world space to camera/eye space
    glm::vec3 Screen2World(float scr_x, float scr_y, float camera_z = -1.f);         // Transform the coordinate from screen space to world space (needs the expected z_value in camera space)
    glm::vec3 Screen2World(const glm::vec2& v, float depth = 1.f);
    // Return a tuple (o, v), where (R = o + tv) is the ray that goes through the corresponding scree point.
    // Example usage:
    //     glm::vec3 o, v; 
    //     std::tie(o, v) = Screen2WorldRay(...)
    std::tuple<glm::vec3, glm::vec3> Screen2WorldRay(float scr_x, float scr_y); 

    // Members
    Mesh mesh_;                                                                      // mesh_ keeps the geometry information of the object
    Camera camera_;                                                                  // camera_ keeps the intrinsic/extrinsic camera parameters

    // Some states
    int l_mouse_state_ = GLFW_RELEASE;
    int r_mouse_state_ = GLFW_RELEASE;

    int modeling_state_ = OBJ_ROTATION;

    float last_cursor_x_ = 0;
    float last_cursor_y_ = 0;
    float l_click_cursor_x_ = 0;
    float l_click_cursor_y_ = 0;
};

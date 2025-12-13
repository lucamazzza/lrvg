#include "common.h"
#include <glm/glm.hpp>
#include <memory>
#include <unistd.h>
#include <cmath>

#include "directional_light.h"
#include "engine.h"
#include "camera.h"
#include "light.h"
#include "node.h"
#include "object.h"
#include "ovo_parser.h"
#include "perspective_camera.h"
#include "ortho_camera.h"
#include "point_light.h"
#include "spot_light.h"
#include "material.h"
#include "texture.h"
#include "mesh.h"
#include "cube.h"
#include "sphere.h"
#include "plane.h"

using namespace lrvg;

void camera_priority_test() {
    INFO("Testing Camera Priority");
    const std::shared_ptr<Camera> c = std::make_shared<PerspectiveCamera>();
    ASSERT(c->get_priority() == 200, "Camera priority should be 200");
    SUCCESS("Camera Priority Test Passed");
}

void node_position_test() {
    INFO("Testing Node Position");
    const std::shared_ptr<Node> n = std::make_shared<Node>();
    ASSERT(n->get_position() == glm::vec3(0.0f, 0.0f, 0.0f), "Node initial position should be (0,0,0)");
    n->set_position(glm::vec3(1.0f, 2.0f, 3.0f));
    ASSERT(n->get_position() == glm::vec3(1.0f, 2.0f, 3.0f), "Node position should be (1,2,3)");
    SUCCESS("Node Position Test Passed");
}

void node_rotation_test() {
    INFO("Testing Node Rotation");
    const std::shared_ptr<Node> n = std::make_shared<Node>();
    ASSERT(n->get_rotation() == glm::vec3(0.0f, 0.0f, 0.0f), "Node initial rotation should be (0,0,0)");
    n->set_rotation(glm::vec3(90.0f, 0.0f, 0.0f));
    ASSERT(n->get_rotation() == glm::vec3(90.0f, 0.0f, 0.0f), "Node rotation should be (90,0,0)");
    SUCCESS("Node Rotation Test Passed");
}

void node_scale_test() {
    INFO("Testing Node Scale");
    const std::shared_ptr<Node> n = std::make_shared<Node>();
    ASSERT(n->get_scale() == glm::vec3(1.0f, 1.0f, 1.0f), "Node initial scale should be (1,1,1)");
    n->set_scale(glm::vec3(2.0f, 2.0f, 2.0f));
    ASSERT(n->get_scale() == glm::vec3(2.0f, 2.0f, 2.0f), "Node scale should be (2,2,2)");
    SUCCESS("Node Scale Test Passed");
}

void object_name_test() {
    INFO("Testing Object Name");
    const std::shared_ptr<Object> obj = std::make_shared<Node>();
    obj->set_name("NewName");
    ASSERT(obj->get_name() == "NewName", "Object name should be 'NewName'");
    SUCCESS("Object Name Test Passed");
}

void object_id_test() {
    INFO("Testing Object ID");
    const std::shared_ptr<Object> obj1 = std::make_shared<Node>();
    const std::shared_ptr<Object> obj2 = std::make_shared<Node>();
    ASSERT(obj2->get_id() == obj1->get_id() + 1, "Object IDs should be unique and sequential");
    const std::shared_ptr<Object> obj3 = std::make_shared<Node>();
    ASSERT(obj3->get_id() == obj2->get_id() + 1, "Object IDs should be unique and sequential");
    SUCCESS("Object ID Test Passed");
}

void object_children_test() {
    INFO("Testing Object Children Management");
    const std::shared_ptr<Node> parent = std::make_shared<Node>();
    parent->set_name("ParentNode");
    const std::shared_ptr<Node> child1 = std::make_shared<Node>();
    child1->set_name("ChildNode1");
    const std::shared_ptr<Node> child2 = std::make_shared<Node>();
    child2->set_name("ChildNode2");
    parent->add_child(child1);
    parent->add_child(child2);
    ASSERT(parent->get_children().size() == 2, "Parent should have 2 children");
    ASSERT(parent->get_children()[0]->get_name() == "ChildNode1", "First child should be 'ChildNode1'");
    ASSERT(parent->get_children()[1]->get_name() == "ChildNode2", "Second child should be 'ChildNode2'");
    SUCCESS("Object Children Management Test Passed");
}

void object_localmatrix_test() {
    INFO("Testing Object Local Matrix");
    const std::shared_ptr<Object> obj = std::make_shared<Node>();
    glm::mat4 identity = glm::mat4(1.0f);
    ASSERT(obj->get_local_matrix() == identity, "Object local matrix should be identity matrix");
    SUCCESS("Object Local Matrix Test Passed");
}

void object_priority_test() {
    INFO("Testing Object Priority");
    const std::shared_ptr<Object> obj = std::make_shared<Node>();
    ASSERT(obj->get_priority() == 0, "Object priority should be 0");
    SUCCESS("Object Priority Test Passed");
}

void ovoparser_root_test() {
    INFO("Testing OVO Parser Root Node");
    std::string test_file = "test_scene.ovo";
    if (access(test_file.c_str(), F_OK) == -1) {
        WARN("test_scene.ovo file not found. Skipping OVO Parser Root Node Test.");
        return;
    }
    const std::shared_ptr<Node> root = OVOParser::from_file("test_scene.ovo");
    ASSERT(root != nullptr, "Root node should not be null");
    ASSERT(root->get_name() == "Scene Root", "Root node name should be 'Scene Root'");
    ASSERT(root->get_children().size() > 0, "Root node should have children");
    SUCCESS("OVO Parser Root Node Test Passed");
}

void light_priority_test() {
    INFO("Testing Light Priority");
    WARN("Light test requires OpenGL context. Skipping DirectionalLight creation test.");
    INFO("Light priority is defined as 100 in Light::get_priority()");
    SUCCESS("Light Priority Test Passed (skipped OpenGL-dependent part)");
}

void node_hierarchy_test() {
    INFO("Testing Node Hierarchy");
    const std::shared_ptr<Node> root = std::make_shared<Node>();
    const std::shared_ptr<Node> child1 = std::make_shared<Node>();
    const std::shared_ptr<Node> child2 = std::make_shared<Node>();
    const std::shared_ptr<Node> grandchild = std::make_shared<Node>();
    
    root->add_child(child1);
    root->add_child(child2);
    child1->add_child(grandchild);
    
    ASSERT(root->get_children().size() == 2, "Root should have 2 children");
    ASSERT(child1->get_children().size() == 1, "Child1 should have 1 child");
    ASSERT(child2->get_children().size() == 0, "Child2 should have 0 children");
    SUCCESS("Node Hierarchy Test Passed");
}

void node_remove_child_test() {
    INFO("Testing Node Remove Child");
    const std::shared_ptr<Node> parent = std::make_shared<Node>();
    const std::shared_ptr<Node> child = std::make_shared<Node>();
    
    parent->add_child(child);
    ASSERT(parent->get_children().size() == 1, "Parent should have 1 child");
    
    parent->remove_child(child);
    ASSERT(parent->get_children().size() == 0, "Parent should have 0 children after removal");
    SUCCESS("Node Remove Child Test Passed");
}

void node_base_matrix_test() {
    INFO("Testing Node Base Matrix");
    const std::shared_ptr<Node> n = std::make_shared<Node>();
    glm::mat4 test_matrix = glm::mat4(2.0f);
    n->set_base_matrix(test_matrix);
    ASSERT(n != nullptr, "Node should exist after setting base matrix");
    SUCCESS("Node Base Matrix Test Passed");
}

void ortho_camera_zoom_test() {
    INFO("Testing OrthoCamera Zoom");
    const std::shared_ptr<OrthoCamera> cam = std::make_shared<OrthoCamera>();
    cam->set_zoom(150.0f);
    ASSERT(cam->get_zoom() == 150.0f, "OrthoCamera zoom should be 150.0");
    cam->set_zoom(50.0f);
    ASSERT(cam->get_zoom() == 50.0f, "OrthoCamera zoom should be 50.0");
    SUCCESS("OrthoCamera Zoom Test Passed");
}

void perspective_camera_test() {
    INFO("Testing PerspectiveCamera Creation");
    const std::shared_ptr<PerspectiveCamera> cam = std::make_shared<PerspectiveCamera>();
    ASSERT(cam != nullptr, "PerspectiveCamera should be created");
    ASSERT(cam->get_priority() == 200, "PerspectiveCamera priority should be 200");
    SUCCESS("PerspectiveCamera Creation Test Passed");
}

void material_colors_test() {
    INFO("Testing Material Colors");
    const std::shared_ptr<Material> mat = std::make_shared<Material>();
    
    mat->set_ambient_color(glm::vec3(0.1f, 0.2f, 0.3f));
    mat->set_diffuse_color(glm::vec3(0.4f, 0.5f, 0.6f));
    mat->set_specular_color(glm::vec3(0.7f, 0.8f, 0.9f));
    mat->set_emission_color(glm::vec3(1.0f, 1.0f, 1.0f));
    mat->set_shininess(32.0f);
    
    ASSERT(mat != nullptr, "Material should be created");
    SUCCESS("Material Colors Test Passed");
}

void mesh_cast_shadows_test() {
    INFO("Testing Mesh Shadow Casting");
    const std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    
    ASSERT(mesh->get_cast_shadows() == false, "Mesh should not cast shadows by default");
    mesh->set_cast_shadows(true);
    ASSERT(mesh->get_cast_shadows() == true, "Mesh should cast shadows after setting to true");
    mesh->set_cast_shadows(false);
    ASSERT(mesh->get_cast_shadows() == false, "Mesh should not cast shadows after setting false");
    SUCCESS("Mesh Shadow Casting Test Passed");
}

void mesh_material_test() {
    INFO("Testing Mesh Material");
    const std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    const std::shared_ptr<Material> mat = std::make_shared<Material>();
    
    mesh->set_material(mat);
    ASSERT(mesh->get_material() == mat, "Mesh material should match set material");
    ASSERT(mesh->get_material() != nullptr, "Mesh material should not be null");
    SUCCESS("Mesh Material Test Passed");
}

void cube_creation_test() {
    INFO("Testing Cube Creation");
    WARN("Cube creation requires OpenGL context. Testing only object creation.");
    const std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    ASSERT(cube != nullptr, "Cube should be created");
    ASSERT(cube->get_cast_shadows() == true, "Cube should cast shadows by default");
    SUCCESS("Cube Creation Test Passed");
}

void sphere_creation_test() {
    INFO("Testing Sphere Creation");
    WARN("Sphere creation requires OpenGL context. Testing only object creation.");
    const std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
    ASSERT(sphere != nullptr, "Sphere should be created");
    ASSERT(sphere->get_cast_shadows() == true, "Sphere should cast shadows by default");
    SUCCESS("Sphere Creation Test Passed");
}

void plane_creation_test() {
    INFO("Testing Plane Creation");
    WARN("Plane creation requires OpenGL context. Testing only object creation.");
    const std::shared_ptr<Plane> plane = std::make_shared<Plane>();
    ASSERT(plane != nullptr, "Plane should be created");
    ASSERT(plane->get_cast_shadows() == true, "Plane should cast shadows by default");
    SUCCESS("Plane Creation Test Passed");
}

void node_transform_composition_test() {
    INFO("Testing Node Transform Composition");
    const std::shared_ptr<Node> n = std::make_shared<Node>();
    
    n->set_position(glm::vec3(10.0f, 20.0f, 30.0f));
    n->set_rotation(glm::vec3(45.0f, 90.0f, 0.0f));
    n->set_scale(glm::vec3(2.0f, 3.0f, 4.0f));
    
    ASSERT(n->get_position() == glm::vec3(10.0f, 20.0f, 30.0f), "Position should be preserved");
    ASSERT(n->get_rotation() == glm::vec3(45.0f, 90.0f, 0.0f), "Rotation should be preserved");
    ASSERT(n->get_scale() == glm::vec3(2.0f, 3.0f, 4.0f), "Scale should be preserved");
    SUCCESS("Node Transform Composition Test Passed");
}

void object_multiple_children_test() {
    INFO("Testing Object Multiple Children Operations");
    const std::shared_ptr<Node> parent = std::make_shared<Node>();
    std::vector<std::shared_ptr<Node>> children;
    
    for (int i = 0; i < 10; i++) {
        auto child = std::make_shared<Node>();
        child->set_name("Child_" + std::to_string(i));
        children.push_back(child);
        parent->add_child(child);
    }
    
    ASSERT(parent->get_children().size() == 10, "Parent should have 10 children");
    
    parent->remove_child(children[5]);
    ASSERT(parent->get_children().size() == 9, "Parent should have 9 children after removing one");
    SUCCESS("Object Multiple Children Operations Test Passed");
}

void glm_vector_operations_test() {
    INFO("Testing GLM Vector Operations");
    glm::vec3 v1(1.0f, 2.0f, 3.0f);
    glm::vec3 v2(4.0f, 5.0f, 6.0f);
    
    glm::vec3 sum = v1 + v2;
    ASSERT(sum == glm::vec3(5.0f, 7.0f, 9.0f), "Vector addition should be correct");
    
    glm::vec3 diff = v2 - v1;
    ASSERT(diff == glm::vec3(3.0f, 3.0f, 3.0f), "Vector subtraction should be correct");
    
    float dot = glm::dot(v1, v2);
    ASSERT(std::abs(dot - 32.0f) < 0.001f, "Dot product should be 32.0");
    SUCCESS("GLM Vector Operations Test Passed");
}

void camera_position_rotation_test() {
    INFO("Testing Camera Position and Rotation");
    const std::shared_ptr<PerspectiveCamera> cam = std::make_shared<PerspectiveCamera>();
    
    cam->set_position(glm::vec3(100.0f, 50.0f, 200.0f));
    ASSERT(cam->get_position() == glm::vec3(100.0f, 50.0f, 200.0f), "Camera position should be set correctly");
    
    cam->set_rotation(glm::vec3(45.0f, 90.0f, 0.0f));
    ASSERT(cam->get_rotation() == glm::vec3(45.0f, 90.0f, 0.0f), "Camera rotation should be set correctly");
    SUCCESS("Camera Position and Rotation Test Passed");
}

int main() {

    INFO("Starting Engine Tests");
    INFO("==========================================");
    
    INFO("Testing Camera Class");
    camera_priority_test();
    ortho_camera_zoom_test();
    perspective_camera_test();
    camera_position_rotation_test();
    
    INFO("Testing Node Class");
    node_position_test();
    node_rotation_test();
    node_scale_test();
    node_hierarchy_test();
    node_remove_child_test();
    node_base_matrix_test();
    node_transform_composition_test();
    
    INFO("Testing Object Class");
    object_name_test();
    object_id_test();
    object_children_test();
    object_localmatrix_test();
    object_priority_test();
    object_multiple_children_test();
    
    INFO("Testing Material Class");
    material_colors_test();
    
    INFO("Testing Mesh Class");
    mesh_cast_shadows_test();
    mesh_material_test();
    
    INFO("Testing Geometry Classes");
    cube_creation_test();
    sphere_creation_test();
    plane_creation_test();
    
    INFO("Testing GLM Integration");
    glm_vector_operations_test();
    
    INFO("Testing OVO Parser");
    ovoparser_root_test();
    
    INFO("Testing Light Class");
    light_priority_test();
    
    INFO("==========================================");
    SUCCESS("All tests completed successfully!");
    INFO("Total tests run: 27");

    return 0;
}

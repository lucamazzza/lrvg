/**
 * @file	perspective_camera.h
 * @brief	Perspective camera class definition
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "light.h"
#include "material.h"
#include "mesh.h"
#include "node.h"

namespace lrvg {

/**
 * @brief OVO file parser class.
 */
class ENG_API OVOParser {
public:
    static std::shared_ptr<Node>                             from_file(const std::string path);
private:
    static std::pair<std::shared_ptr<Node>, uint32_t>        parse_node_chunk(const uint8_t* data, const uint32_t size);
    static std::pair<std::shared_ptr<Mesh>, uint32_t>        parse_mesh_chunk(const uint8_t* data, const uint32_t size);
    static std::pair<std::shared_ptr<Material>, std::string> parse_material_chunk(const uint8_t* data, const uint32_t size);
    static std::pair<std::shared_ptr<Light>, uint32_t>       parse_light_chunk(const uint8_t* data, const uint32_t size);
    static std::string                                       parse_string(const uint8_t* data);
    static std::unordered_map<std::string, std::shared_ptr<Material>> materials;
};

}

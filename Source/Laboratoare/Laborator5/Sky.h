#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Sky
{

	Mesh* CreateSky(std::string name, glm::vec3 mapCenter, float length, glm::vec3 color, bool fill = false);

}


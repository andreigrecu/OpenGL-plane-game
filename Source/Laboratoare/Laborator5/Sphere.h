#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Sphere
{

	Mesh* CreateSphere(std::string name, glm::vec3 leftBottomCorner, float Stacks, int Slices, float Radius, glm::vec3 color, bool fill = false);

}


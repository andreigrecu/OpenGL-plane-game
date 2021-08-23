#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Plane
{

	Mesh* CreatePlane(std::string name, glm::vec3 mapCenter, float planeBodylength, float planeHeadlength, float lengthWing, float widthWing,
		float lengthTail, float heightTail, float widthTail, glm::vec3 color, bool fill = false);

}


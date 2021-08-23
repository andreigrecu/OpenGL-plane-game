#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Elice
{

	Mesh* CreateElice(std::string name, glm::vec3 centerMap, float lenthCorp, float lengthCap, float lengthSupport, 
		float heightSupport, float widthSupport, float lengthElice, float widthElice, glm::vec3 color, bool fill = false);

}


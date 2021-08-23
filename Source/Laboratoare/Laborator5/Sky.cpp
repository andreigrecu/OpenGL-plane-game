#include "Sky.h"

#include <Core/Engine.h>

Mesh* Sky::CreateSky(std::string name, glm::vec3 mapCenter, float length, glm::vec3 color, bool fill)
{

	////lengthCap e lungimea capului...planeHeadlength
	std::vector<VertexFormat> vertices =
	{


			VertexFormat(glm::vec3(-length / 2, -length / 2, length / 2), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(length / 2, -length / 2, length / 2), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-length / 2, length / 2, length / 2), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(length / 2, length / 2, length / 2), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-length / 2, - length / 2, -length / 2), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(length / 2, -length / 2, -length / 2), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-length / 2, length / 2, - length / 2), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(length / 2, length / 2, -length / 2), glm::vec3(0, 1, 1))
			
	};

	Mesh *sky = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		0, 1, 2,	
		1, 3, 2,	
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};
		
	sky->InitFromData(vertices, indices);
	return sky;
}
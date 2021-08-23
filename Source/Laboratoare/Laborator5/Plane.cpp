#include "Plane.h"

#include <Core/Engine.h>

Mesh* Plane::CreatePlane(std::string name, glm::vec3 mapCenter, float planeBodylength, float planeHeadlength, float lengthWing, float widthWing, 
	float lengthTail, float heightTail, float widthTail, glm::vec3 color, bool fill)
{

	
	std::vector<VertexFormat> vertices =
	{
		///corp avion
		VertexFormat(mapCenter + glm::vec3(0, 0, planeBodylength), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength, 0, planeBodylength), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(0, planeBodylength, planeBodylength), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength, planeBodylength, planeBodylength), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(0, planeBodylength, 0), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength, planeBodylength, 0), glm::vec3(1, 0, 0)),


		///cap avion
		////planeHeadlength e lungimea cubului care formeaza capul avionului
		////latimea este egala cu cea a corpului, la fel si inaltimea
		VertexFormat(mapCenter + glm::vec3(planeBodylength, 0, planeBodylength), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength, 0, 0), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength, planeBodylength, planeBodylength), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength, planeBodylength, 0), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + planeHeadlength, 0, planeBodylength), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + planeHeadlength, 0, 0), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + planeHeadlength, planeBodylength, planeBodylength), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + planeHeadlength, planeBodylength, 0), glm::vec3(1, 1, 1)),

		////aripi
		////lengthWing e lungimea aripii
		////widthWing e latimea aripii
		////inaltimea o aleg hardcodat mereu egala cu 1
		VertexFormat(mapCenter + glm::vec3(0.1, 0.3, planeBodylength + lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.3, planeBodylength + lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1, 0.4, planeBodylength + lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.4, planeBodylength + lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1, 0.3, planeBodylength), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.3, planeBodylength), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1, 0.4, planeBodylength), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.4, planeBodylength),glm::vec3(1, 1, 1)),

		
		VertexFormat(mapCenter + glm::vec3(0.1, 0.3, -lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.3, -lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1, 0.4, -lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.4, -lengthWing), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1, 0.3, 0), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.3, 0), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1, 0.4, 0), glm::vec3(1, 1, 1)),
		VertexFormat(mapCenter + glm::vec3(0.1 + widthWing, 0.4, 0), glm::vec3(1, 1, 1)),

		VertexFormat(mapCenter + glm::vec3(-lengthTail, 0.35, planeBodylength / 2 + widthTail/2), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(0, 0.35, planeBodylength / 2 + widthTail / 2), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(-lengthTail, 0.35 + heightTail, planeBodylength / 2 + widthTail / 2), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(0, 0.35 + heightTail, planeBodylength / 2 + widthTail / 2), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(-lengthTail, 0.35, planeBodylength / 2 - widthTail / 2), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(0, 0.35, planeBodylength / 2 - widthTail / 2), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(-lengthTail, 0.35 + heightTail, planeBodylength / 2 - widthTail / 2), glm::vec3(1, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(0, 0.35 + heightTail, planeBodylength / 2 - widthTail / 2), glm::vec3(1, 0, 0)),
		
		

	};

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
		0, 2, 4,
		
		8, 9, 10,
		9, 11, 10,
		10, 11, 15,
		10, 15, 14,
		9, 15, 11,
		9, 13, 15,
		14, 15, 12,
		15, 13, 12,
		8, 12, 9,
		9, 12, 13,
		10, 14, 12,
		8, 10, 12,

		16, 17, 18,
		17, 19, 18,
		18, 19, 23,
		18, 23, 22,
		17, 23, 19,
		17, 21, 23,
		22, 23, 20,
		23, 21, 20,
		16, 20, 17,
		17, 20, 21,
		18, 22, 20,
		16, 18, 20,

		24, 25, 26,
		25, 27, 26,
		26, 27, 31,
		26, 31, 30,
		25, 31, 27,
		25, 29, 31,
		30, 31, 28,
		31, 29, 28,
		24, 28, 25,
		25, 28, 29,
		26, 30, 28,
		24, 26, 28,

		32, 33, 34,
		33, 35, 34,
		34, 35, 39,
		34, 39, 38,
		33, 39, 35,
		33, 37, 39,
		38, 39, 36,
		39, 37, 36,
		32, 36, 33,
		33, 36, 37,
		34, 38, 36,
		32, 34, 36,
		
		
	};
		
	

	Mesh *plane = new Mesh(name);
	plane->InitFromData(vertices, indices);
	return plane;
}
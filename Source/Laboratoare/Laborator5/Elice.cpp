#include "Elice.h"

#include <Core/Engine.h>

Mesh* Elice::CreateElice(std::string name, glm::vec3 mapCenter, float planeBodylength, float lengthCap, float lengthSupport, 
	float heightSupport, float widthSupport, float lengthElice, float widthElice, glm::vec3 color, bool fill)
{

	////lengthCap e lungimea capului...planeHeadlength
	std::vector<VertexFormat> vertices =
	{
		////suport elice
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap, planeBodylength / 2 + heightSupport / 2, 
		planeBodylength / 2 - widthSupport / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 + heightSupport / 2, 
		planeBodylength / 2 - widthSupport / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap, planeBodylength / 2 - heightSupport / 2, 
		planeBodylength / 2 - widthSupport / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 - heightSupport / 2, 
		planeBodylength / 2 - widthSupport / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap, planeBodylength / 2 + heightSupport / 2, 
		planeBodylength / 2 + widthSupport / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 + heightSupport / 2, 
		planeBodylength / 2 + widthSupport / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap, planeBodylength / 2 - heightSupport / 2, 
		planeBodylength / 2 + widthSupport / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 - heightSupport / 2, 
		planeBodylength / 2 + widthSupport / 2), glm::vec3(0, 0, 0)),


		//elice 1
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, 0.0f, 
		planeBodylength / 2 - widthElice / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice, 0.0f,
		planeBodylength / 2 - widthElice / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength,
		planeBodylength / 2 - widthElice / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice, planeBodylength, 
		planeBodylength / 2 - widthElice / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, 0.0f, 
		planeBodylength / 2 + widthElice / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice,  0.0f, 
		planeBodylength / 2 + widthElice / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength, 
		planeBodylength / 2 + widthElice / 2), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice, planeBodylength, 
		planeBodylength / 2 + widthElice / 2), glm::vec3(0, 0, 0)),


		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 - widthSupport / 2,
		planeBodylength), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice, planeBodylength / 2 - widthSupport / 2,
		planeBodylength), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 + widthSupport / 2,
		planeBodylength), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice, planeBodylength / 2 + widthSupport / 2,
		planeBodylength), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 - widthSupport / 2,
		0.0f), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice, planeBodylength / 2 - widthSupport / 2,
		0.0f), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport, planeBodylength / 2 + widthSupport / 2,
		0.0f), glm::vec3(0, 0, 0)),
		VertexFormat(mapCenter + glm::vec3(planeBodylength + lengthCap + lengthSupport + lengthElice, planeBodylength / 2 + widthSupport / 2,
		0.0f), glm::vec3(0, 0, 0)),


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

	};



	Mesh *elice = new Mesh(name);



	elice ->InitFromData(vertices, indices);
	return elice;

}
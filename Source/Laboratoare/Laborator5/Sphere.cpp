#include "Sphere.h"

#include <Core/Engine.h>

Mesh* Sphere::CreateSphere(std::string name, glm::vec3 leftBottomCorner, float Stacks, int Slices, float Radius, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices;

	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(VertexFormat(glm::vec3(x, y, z) * Radius, color));
		}
	}

	Mesh *sphere = new Mesh(name);
	std::vector<unsigned short> indices;

	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		indices.push_back(i);
		indices.push_back(i + Slices + 1);
		indices.push_back(i + Slices);

		indices.push_back(i + Slices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	if (!fill) {
		sphere->SetDrawMode(GL_LINE_LOOP);
	}


	sphere->InitFromData(vertices, indices);
	return sphere;

}
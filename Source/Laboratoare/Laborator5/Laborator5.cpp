#include "Laborator5.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <Core/Engine.h>
#include "Transform3D.h"
#include "Plane.h"
#include "Elice.h"
#include "Sphere.h"
#include "RandomClass.h"
#include "Sky.h"

using namespace std;

Laborator5::Laborator5()
{
}
Laborator5::~Laborator5()
{
}
//functie care afiseaza fundalul din fata
glm::mat4 afisare_fundal_fata(glm::mat4 modelMatrix);
//functie care afiseaza fundalul din dreapta
glm::mat4 afisare_fundal_dreapta(glm::mat4 modelMatrix);
//functie pentru desenare cilindru care reprezinta marea
glm::mat4 draw_cylinder(glm::mat4 modelMatrix);
//functie pentru desenare sfera1 din viata
glm::mat4 draw_sphere1(glm::mat4 modelMatrix);
//functie pentru desenare sfera2 din viata
glm::mat4 draw_sphere2(glm::mat4 modelMatrix);
//functie pentru desenare sfera3 din viata
glm::mat4 draw_sphere3(glm::mat4 modelMatrix);
//functie pentru desenare sfera1 din FP
glm::mat4 draw_sphere1FP(glm::mat4 modelMatrix, float translateY);
//functie pentru desenare sfera2 din FP
glm::mat4 draw_sphere2FP(glm::mat4 modelMatrix, float translateY);
//functie pentru desenare sfera3 din FP
glm::mat4 draw_sphere3FP(glm::mat4 modelMatrix, float translateY);
//functii care ajuta la desenarea norilor pe ecran prin calcule de matrice de modelare
glm::mat4 draw_cube3(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky);
glm::mat4 draw_cube4(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky);
glm::mat4 draw_cube2(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky);
glm::mat4 draw_cube1(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky);
//help plane fall
glm::mat4 plane_fall_help(glm::mat4 modelMatrix, float planeYFall);
//ajuta randare avion
glm::mat4 draw_plane(glm::mat4 modelMatrix, float translateY, float planeBodylength, float rotateY);
////functie pentru maximul dintre doua numere reale
float getMaxim(float number1, float number2);
////minimul dintre doua numere reale
float getMinim(float number1, float number2);
//// testeaza daca exista coliziune intre o sfera si un paralelipiped
bool isCollision(glm::vec3 CenterCircle1, float lengthCircle1, float rectangleMinX, float rectangleMaxX, float rectangleMinY, float rectangleMaxY,
	float rectangleMinZ, float rectangleMaxZ);
void calculate_Collision_data(float length, float width, float pozX_RotationCenter, float pozY_RotationCenter, float pozZ_RotationCenter,
	float angle, float *diff_X, float *diff_Y);

void Laborator5::Init()
{

	//// ------------------------  camera  ---------------------- ////
	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 4.0f, 8.7f), glm::vec3(0, 4, 0), glm::vec3(0, 1, 0));
	//// ------------------------  camera  ---------------------- ////



	//// ------------------------  creare fundal  ---------------------- ////
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.55f, 0.47f, 0.14f)),
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0.55f, 0.47f, 0.14f)),
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0.55f, 0.47f, 0.14f)),
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0.55f, 0.47f, 0.14f)),

		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 3, 2

		};

		meshes["patrat"] = new Mesh("generated patrat");
		meshes["patrat"]->InitFromData(vertices, indices);

	}
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.55f, 0.47f, 0.14f)),
			VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0.55f, 0.47f, 0.14f)),
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0.55f, 0.47f, 0.14f)),
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0.55f, 0.47f, 0.14f)),

		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 3, 2

		};

		meshes["patrat1"] = new Mesh("generated patrat1");
		meshes["patrat1"]->InitFromData(vertices, indices);

	}
	//// ------------------------  creare fundal  ---------------------- ////




	//// ------------------------  conectare la shadere  ---------------------- ////
	{
		Shader *shader = new Shader("ShaderLab5");
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}



	//// ------------------------  creare mesh folosit la skies  ---------------------- ////
	{
		lengthSkyCube = 0.5f;
		Mesh* sky = Sky::CreateSky("sky", mapCenter, lengthSkyCube, glm::vec3(1, 0, 0), true);
		AddMeshToList(sky);
	}
	//// ------------------------  creare mesh folosit la skies  ---------------------- ////

	


	//// ------------------------  mesh teapot - pt combustibil  ---------------------- ////
	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	//// ------------------------  mesh teapot - pt combustibil  ---------------------- ////


	//// ------------------------  mesh cilindru - reprezinta marea  ---------------------- ////
	{
		Mesh* mesh = new Mesh("cylinder");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Props", "oildrum.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	//// ------------------------  mesh cilindru - reprezinta marea  ---------------------- ////


	//// ------------------------  mesh sfera - pentru obstacole ---------------------- ////
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	//// ------------------------  mesh sfera - pentru obstacole ---------------------- ////


	//// ------------------------  mesh combustibil - pt ThirdPerson ---------------------- ////
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(0.7, 0, 0)),
			VertexFormat(glm::vec3(0.7, 0.3, 0)),
			VertexFormat(glm::vec3(0, 0.3, 0)),

		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 3, 2

		};

		meshes["combustibil"] = new Mesh("generated combustibil");
		meshes["combustibil"]->InitFromData(vertices, indices);

	}
	//// ------------------------  mesh combustibil - pt ThirdPerson ---------------------- ////


	//// ------------------------  mesh combustibil1 - pt FirstPerson ---------------------- ////
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(0, 0, 0.7)),
			VertexFormat(glm::vec3(0, 0.3, 0.7)),
			VertexFormat(glm::vec3(0, 0.3, 0)),

		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 3, 2

		};

		meshes["combustibil1"] = new Mesh("generated combustibil1");
		meshes["combustibil1"]->InitFromData(vertices, indices);

	}
	//// ------------------------  mesh combustibil1 - pt FirstPerson ---------------------- ////


	//// ------------------------  creare mesh avion + elice ---------------------- ////
	//dimensiuni avion
	float lengthWing = 0.4f;  //lungime aripa
	float widthWing = 0.25f; //latime aripa
	float lengthTail = 0.2f; //lungime coada
	float heightTail = 0.3f; //inaltime coada
	float widthTail = 0.1f; //latime coada

	Mesh* plane = Plane::CreatePlane("plane", mapCenter, planeBodylength, planeHeadlength, lengthWing,
		widthWing, lengthTail, heightTail, widthTail, glm::vec3(1, 0, 0), true);
	AddMeshToList(plane);

	//dimensiuni elice
	float heightSupport = 0.1f;
	float widthSupport = 0.1f;
	float widthElice = 0.12f;

	Mesh* elice = Elice::CreateElice("elice", mapCenter, planeBodylength, planeHeadlength, lengthSupport,
		heightSupport, widthSupport, lengthElice, widthElice, glm::vec3(1, 0, 0), true);
	AddMeshToList(elice);
	//// ------------------------  creare mesh avion + elice ---------------------- ////


	////pozitiile initiale ale sferelor pe x
	////se modifica la fiecare reaparitie
	VECTOR[0] = 30;
	VECTOR[1] = 40;
	VECTOR[2] = 50;
	
	//// pozitiile initiale ale combustibilului pe x
	//// se modifica mereu
	VECTORCOMB[0] = 20.4f;
	VECTORCOMB[1] = 20.8f;
	VECTORCOMB[2] = 21.2f;
	VECTORCOMB[3] = 21.6f;
	VECTORCOMB[4] = 22.0f;
	VECTORCOMB[5] = 22.4f;
	VECTORCOMB[6] = 22.8f;
	VECTORCOMB[7] = 23.2f;
	VECTORCOMB[8] = 23.6f;
	VECTORCOMB[9] = 24.0f;


	//// vectori cu inaltimile combustibilului, initial sunt date, se modifica la fiecare reaparitie
	VECTOR_inaltimi_COMB[0] = 5.0f;
	VECTOR_inaltimi_COMB[1] = 4.9f;
	VECTOR_inaltimi_COMB[2] = 4.7f;
	VECTOR_inaltimi_COMB[3] = 4.55f;
	VECTOR_inaltimi_COMB[4] = 4.35f;
	VECTOR_inaltimi_COMB[5] = 4.13f;
	VECTOR_inaltimi_COMB[6] = 3.9f;
	VECTOR_inaltimi_COMB[7] = 3.7f;
	VECTOR_inaltimi_COMB[8] = 3.7f;
	VECTOR_inaltimi_COMB[9] = 3.75f;
	for (int i = 0; i <= 9; i++)
		isCollisionCOMB[i] = 0; //// verifica daca e coliziune cu combustibilul: 0 nu.. 1 da


	///// verificare coliziune sfera, se modifica daca exista
	isCollisionSphere[0] = 0;
	isCollisionSphere[1] = 0;
	isCollisionSphere[2] = 0;

	////inaltimile initiale ale sferelor, se modifica la fiecare reaparitie a sferelor
	Sphere_y[0] = 4.2f;
	Sphere_y[1] = 4.5f;
	Sphere_y[2] = 6.5f;

	////inaltimea si z ul primilor 3 nori
	inaltimeSky[0] = 5.0f;
	inaltimeSky[1] = 7.0f;
	inaltimeSky[2] = 6.0f;
	zSky[0] = 0.0f;
	zSky[1] = -4.0f;
	zSky[2] = -6.0f;


	//// rotatia primilor 3 nori
	rotateSky1[0] = rotateSky1[1] = rotateSky2[0] = rotateSky2[1] = rotateSky2[2] = rotateSky3[0] = rotateSky4[1] = rotateSky4[2] = 0;
	rotateSky1[2] = rotateSky3[1] = rotateSky3[2] = rotateSky4[0] = 1;

	//// matricea de proiectie
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	//viata
	hearts_x = 100.0f;

	//texturi
	const string textureLoc = "Source/Laboratoare/Laborator9/Textures/";
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "rock3.jpg").c_str(), GL_REPEAT);
		mapTextures["earth"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "marea2.jpg").c_str(), GL_REPEAT);
		mapTextures["marea"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "nori.jpg").c_str(), GL_REPEAT);
		mapTextures["nori"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pokeball.jpg").c_str(), GL_REPEAT);
		mapTextures["pokeball"] = texture;
	}

	{
		Shader *shader = new Shader("ShaderLab9");
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	
}


// la start dau clear la bufferul de culoare si setez view port-ul cu rezolutiile ecranului
void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Laborator5::Update(float deltaTimeSeconds)
{
	////--------------------  desenare fundal pe ecran --------------- ////
	{
		modelMatrix = afisare_fundal_fata(modelMatrix);
		RenderMesh_texture(meshes["patrat"], shaders["ShaderLab9"], modelMatrix, mapTextures["nori"]);
	}
	{
		modelMatrix = afisare_fundal_dreapta(modelMatrix);
		RenderMesh_texture(meshes["patrat1"], shaders["ShaderLab9"], modelMatrix, mapTextures["nori"]);
	}
	////--------------------  desenare fundal pe ecran --------------- ////


	////--------------------  desenare mare pe ecran --------------- ////
	{
		rotateCylinder += deltaTimeSeconds * 1;
		modelMatrix = draw_cylinder(modelMatrix);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 1, 1));
		modelMatrix = glm::rotate(modelMatrix, rotateCylinder, glm::vec3(0, 1, 0));
		RenderMesh_texture(meshes["cylinder"], shaders["ShaderLab9"], modelMatrix, mapTextures["marea"]);
	}
	////--------------------  desenare mare pe ecran --------------- ////


	//// se verifica ca avionul sa nu intre in apa
	if (translateY + 3.5 <= 1.75) {
		scufunda_avion = 2;
		isIn_water = 1;
	}

	//// desenare avion + animatie in timpul zborului si animatia daca ramane fara combustibil sau fara vieti
	{
		if (scufunda_avion == 0) //cand avionul e in "miscare"
		{
			rotateElice += deltaTimeSeconds * 5;
			modelMatrix = draw_plane(modelMatrix, translateY, planeBodylength, rotateY);
			RenderMesh(meshes["plane"], shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::translate(modelMatrix, glm::vec3((float)(mapCenter.x + 0.8), (float)(mapCenter.y + 0.25), (float)(mapCenter.z + 0.25)));
			modelMatrix = glm::rotate(modelMatrix, rotateElice, glm::vec3(1, 0, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3((float)(-mapCenter.x - 0.8), (float)(-mapCenter.y - 0.25), (float)(-mapCenter.z - 0.25)));
			RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix);
			save_translateY = translateY;
		}
		else if(scufunda_avion == 1) {  //cand se scufunda avionul - daca sunt in FP ma trece in TP
			if (ok1 == 1 && isThirdPerson == 1) {
				OnKeyPress(GLFW_KEY_C, 21);
				ok1 = 0;
			}
			translateY = 0;
			planeFall -= deltaTimeSeconds * 0.5f;
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, save_translateY, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 3.5, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(planeBodylength / 2, planeBodylength / 2, planeBodylength / 2));
			if (planeFall >= -0.8 && planeFall <= 0.0) {
				modelMatrix = glm::translate(modelMatrix, glm::vec3(planeBodylength / 2, planeBodylength / 2, planeBodylength / 2));
				modelMatrix = glm::rotate(modelMatrix, planeFall, glm::vec3(0, 0, 1)); 
				modelMatrix = glm::rotate(modelMatrix, -planeFall, glm::vec3(1, 0, 0)); 
			}
			else {
				ok = 1;
			}

			if (ok != 1) {
				modelMatrix = glm::translate(modelMatrix, glm::vec3(-planeBodylength / 2, -planeBodylength / 2, -planeBodylength / 2));
				RenderMesh(meshes["plane"], shaders["VertexColor"], modelMatrix);
				modelMatrix = glm::translate(modelMatrix, glm::vec3((float)(mapCenter.x + 0.8), (float)(mapCenter.y + 0.25), (float)(mapCenter.z + 0.25)));
				modelMatrix = glm::rotate(modelMatrix, rotateElice, glm::vec3(1, 0, 0));
				modelMatrix = glm::translate(modelMatrix, glm::vec3((float)(-mapCenter.x - 0.8), (float)(-mapCenter.y - 0.25), (float)(-mapCenter.z - 0.25)));
				RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix);
			}
			
			if (ok == 1) {
				planeYFall -= deltaTimeSeconds * 2;
				modelMatrix = plane_fall_help(modelMatrix, planeYFall);
				RenderMesh(meshes["plane"], shaders["VertexColor"], modelMatrix);
				modelMatrix = glm::translate(modelMatrix, glm::vec3((float)(mapCenter.x + 0.8), (float)(mapCenter.y + 0.25), (float)(mapCenter.z + 0.25)));
				modelMatrix = glm::rotate(modelMatrix, rotateElice, glm::vec3(1, 0, 0));
				modelMatrix = glm::translate(modelMatrix, glm::vec3((float)(-mapCenter.x - 0.8), (float)(-mapCenter.y - 0.25), (float)(-mapCenter.z - 0.25)));
				RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix);
			}

		}
		else if (scufunda_avion == 2) {
			numar_vieti = 0;
			translateY = 0;
		}
	}
	
	
	////----------------------- desenarea norilor pe ecran ------------------/////
	{
		rotateTest1 += 1 * deltaTimeSeconds;
		for (int i = 0; i < 3; i++)
			translateSky[i] -= deltaTimeSeconds * 8;

		//pentru cubul 3 din fiecare bucata de cer
		for (int i = 0; i < 3; i++) {
			modelMatrix = draw_cube3(modelMatrix, poz_third_cube, pas, i, inaltimeSky[i], zSky[i], translateSky[i]);
			if (rotateSky3[i] == 1)
				modelMatrix = glm::rotate(modelMatrix, rotateTest1, glm::vec3(1, 0, 0));
			RenderMesh_color(meshes["sky"], shaders["ShaderLab5"], modelMatrix, glm::vec3(1, 1, 1));
		}

		////pentru cubul 4 din fiecare bucata de cer
		for (int i = 0; i < 3; i++) {
			modelMatrix = draw_cube4(modelMatrix, poz_third_cube, pas, i, inaltimeSky[i], zSky[i], translateSky[i]);
			if (rotateSky4[i] == 1)
				modelMatrix = glm::rotate(modelMatrix, rotateTest1, glm::vec3(0, 0, 1));
			RenderMesh_color(meshes["sky"], shaders["ShaderLab5"], modelMatrix, glm::vec3(1, 1, 1));
		}

		////pentru cubul 2 din fiecare bucata de cer
		for (int i = 0; i < 3; i++) {
			modelMatrix = draw_cube2(modelMatrix, poz_third_cube, pas, i, inaltimeSky[i], zSky[i], translateSky[i]);
			if (rotateSky2[i] == 1)
				modelMatrix = glm::rotate(modelMatrix, rotateTest1, glm::vec3(1, 0, 0));
			RenderMesh_color(meshes["sky"], shaders["ShaderLab5"], modelMatrix, glm::vec3(1, 1, 1));
		}

		////pentru cubul 1 din fiecare bucata de cer
		for (int i = 0; i < 3; i++) {
			modelMatrix = draw_cube1(modelMatrix, poz_third_cube, pas, i, inaltimeSky[i], zSky[i], translateSky[i]);
			if (rotateSky1[i] == 1)
				modelMatrix = glm::rotate(modelMatrix, rotateTest1, glm::vec3(0, 0, 1));
			RenderMesh_color(meshes["sky"], shaders["ShaderLab5"], modelMatrix, glm::vec3(1, 1, 1));
		}

		for (int i = 0; i < 3; i++) {
			if (translateSky[i] <= -22 - (pas * i)) {
				translateSky[i] = 12;
				rotateSky1[i] = c.isRotatingSky();
				rotateSky2[i] = c.isRotatingSky();
				rotateSky3[i] = c.isRotatingSky();
				rotateSky4[i] = c.isRotatingSky();
				inaltimeSky[i] = c.getRandom_inaltimeSky();
				zSky[i] = -c.getRandom_zSky();
			}
		}
	}
	////----------------------- desenarea norilor pe ecran ------------------/////



	////------------------------------ desenare vieti Third Person -------------------////
	{
		if (numar_vieti == 3) {
			modelMatrix = draw_sphere1(modelMatrix);
			RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);

			modelMatrix = draw_sphere2(modelMatrix);
			RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);

			modelMatrix = draw_sphere3(modelMatrix);
			RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);
		}

		if (numar_vieti == 2) {
			modelMatrix = draw_sphere1(modelMatrix);
			RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);

			modelMatrix = draw_sphere2(modelMatrix);
			RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);
		}

		if (numar_vieti == 1) {
			modelMatrix = draw_sphere1(modelMatrix);
			RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);
		}

		if (numar_vieti == 0 && scufunda_avion != 2)
			scufunda_avion = 1;
	}
	////------------------------------ desenare vieti Third Person -------------------////



	////------------------------------ desenare vieti First Person -------------------////
	{
		if (isThirdPerson == 1) {
			if (numar_vieti == 3) {
				modelMatrix = draw_sphere1FP(modelMatrix, translateY);
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);

				modelMatrix = draw_sphere2FP(modelMatrix, translateY);
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);

				modelMatrix = draw_sphere3FP(modelMatrix, translateY);
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);
			}

			if (numar_vieti == 2) {
				modelMatrix = draw_sphere1FP(modelMatrix, translateY);
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);

				modelMatrix = draw_sphere2FP(modelMatrix, translateY);
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);
			}

			if (numar_vieti == 1) {
				modelMatrix = draw_sphere1FP(modelMatrix, translateY);
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["pokeball"]);
			}

			if (numar_vieti == 0 && scufunda_avion != 2)
				scufunda_avion = 1;
		}
	}
	////------------------------------ desenare vieti First Person ------------------- ////

	

	////------------------------------ obtacole - se rotesc continuu ------------------- ////
	////aici verific si coliziunea cu avionul////
	{	rotateTest += 10 * deltaTimeSeconds;
		for (int i = 0; i < 3; ++i) {
			if (isCollisionSphere[i] == 0) {
				VECTOR[i] -= 10 * deltaTimeSeconds;
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(10.0f, Sphere_y[i], 0.0f));
				modelMatrix = glm::translate(modelMatrix, glm::vec3(VECTOR[i], 0.0f, 0.0f));
				modelMatrix = glm::rotate(modelMatrix, rotateTest, glm::vec3(1, 0, 0));
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["earth"]);

				if (VECTOR[i] <= -20) {
					VECTOR[i] = 10;
					Sphere_y[i] = c.getRandom_1to4();
					punctaj++;
					cout << "Punctajul este " << punctaj << "\n";
					RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["earth"]);

				}

				calculate_Collision_data(planeBodylength, planeBodylength + planeHeadlength + lengthSupport + lengthElice, planeBodylength / 2,
					planeBodylength / 2, planeBodylength / 2, rotateY, &diff_onX, &diff_onY);
				if ((isCollision(glm::vec3(VECTOR[i] + 10, Sphere_y[i], 0), 0.5, -1 , planeBodylength + planeHeadlength + lengthSupport + lengthElice - 1,
					(float)(3.5 + translateY), (float)(3.5 + planeBodylength + translateY), 0, planeBodylength) == 1) && scufunda_avion != 2 && scufunda_avion != 1) {
					isCollisionSphere[i] = 1;
					numar_vieti--;
				}
			}
			else {
				VECTOR[i] = 20;
				Sphere_y[i] = c.getRandom_1to4();
				RenderMesh_texture(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["earth"]);
				isCollisionSphere[i] = 0;
			}
		}
	}

	////------------------------------ obtacole - se rotesc continuu ------------------- ////


	//// -------------------------------- combustibil ---------------------------------/////
	//// aici o sa maresc micsorare Combustibil la fiecare coliziune cu combustibil... combustibilul o sa dispara
	//// 2 dreptunghiuri suprapuse, cel alb se scaleaza
	if(micsorareCombustibil > 0)
		micsorareCombustibil -= (float)0.0005;
	{
		if (micsorareCombustibil > 0 && isIn_water == 0) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(lengthCombustibil, widthCombustibil, heightCombustibil));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(micsorareCombustibil, 0.40f, 0.0f));
			RenderMesh_color(meshes["combustibil"], shaders["ShaderLab5"], modelMatrix, glm::vec3(1, 1, 1));

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(lengthCombustibil, widthCombustibil, heightCombustibil));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f, 0.40f, 0.0f));
			RenderMesh_color(meshes["combustibil"], shaders["ShaderLab5"], modelMatrix, glm::vec3(0, 0, 0));
		} else {
			scufunda_avion = 1;
			numar_vieti = 0;
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(lengthCombustibil, widthCombustibil, heightCombustibil));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f, 0.40f, 0.0f));
			RenderMesh_color(meshes["combustibil"], shaders["ShaderLab5"], modelMatrix, glm::vec3(0, 0, 0));
		}
	}

	//// bara de combustibil pentru camera FPS
	{
		if (isThirdPerson == 1) {
			if (micsorareCombustibil > 0 && isIn_water == 0) {
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(lengthCombustibil, widthCombustibil + 0.6f + translateY, heightCombustibil - 3.2f));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0f, 0.40f, micsorareCombustibil));
				RenderMesh_color(meshes["combustibil1"], shaders["ShaderLab5"], modelMatrix, glm::vec3(1, 1, 1));

				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(lengthCombustibil, widthCombustibil + 0.6f + translateY, heightCombustibil - 3.2f));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0f, 0.40f, 0.8f));
				RenderMesh_color(meshes["combustibil1"], shaders["ShaderLab5"], modelMatrix, glm::vec3(0, 0, 0));
			}
			else {
				scufunda_avion = 1;
				numar_vieti = 0;
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(lengthCombustibil, widthCombustibil + 0.6f + translateY, heightCombustibil - 3.2f));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0f, 0.40f, 0.8f));
				RenderMesh_color(meshes["combustibil1"], shaders["ShaderLab5"], modelMatrix, glm::vec3(0, 0, 0));
			}
		}
	}
	//// -------------------------------- combustibil ---------------------------------/////


	/////--------------------------------combustibilul-------------------------------//////
	//// se modifica mereu numarul de obiecte de combustibil
	//// au forma arcuita si animatie de rotatie
	//// mereu e aleatorie pozitia pe y
	{
		rotateCOMB -= (float)deltaTimeSeconds * 3;
		for (int j = 0; j <= numarCombustibil; j++) {
			VECTORCOMB[j] -= (float)(deltaTimeSeconds * 9.85);
		}
		
		for (int i = 0; i <= numarCombustibil; i++) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(10, VECTOR_inaltimi_COMB[i], 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(VECTORCOMB[i], 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));
			modelMatrix = glm::rotate(modelMatrix, rotateCOMB, glm::vec3(0, 0, 1));
			if (isCollisionCOMB[i] == 0)
				RenderMesh_color(meshes["teapot"], shaders["ShaderLab5"], modelMatrix, glm::vec3(0, 0.392, 0));


			if ((isCollision(glm::vec3(VECTORCOMB[i] + 10, VECTOR_inaltimi_COMB[i], 0), 0.1f, -1, planeBodylength + planeHeadlength + lengthSupport + lengthElice - 1,
				(float)(3.5 + translateY), (float)(3.5 + planeBodylength + translateY), 0.0f, planeBodylength) == 1) && scufunda_avion != 2 &&
				scufunda_avion != 1) {
				isCollisionCOMB[i] = 1;
				if ((micsorareCombustibil + (float)0.007) > 0.8)
					micsorareCombustibil = 0.8f;
				else
					micsorareCombustibil += (float)0.007;
			}
		}
		if (VECTORCOMB[numarCombustibil] <= -20) {
			for (int i = 0; i <= numarCombustibil; i++) {
				VECTORCOMB[i] = (float)(10 + i * 0.5);
				RenderMesh_color(meshes["teapot"], shaders["ShaderLab5"], modelMatrix, glm::vec3(0, 0.392, 0));
			}

			modif_inaltimeCOMB = (float)(c.getRandom_1to5() * 0.35);
			int yesORno = c.yes_or_no();
			float constant_start = VECTOR_inaltimi_COMB[0];
			float constant_end = VECTOR_inaltimi_COMB[9];
			for (int i = 0; i <= 9; i++) {    //// 9 e numarul maxim de bucati de combustibil posibile

				if(constant_start >= 5)
					VECTOR_inaltimi_COMB[i] -= modif_inaltimeCOMB;
				else if(constant_end <= 3.5)
					VECTOR_inaltimi_COMB[i] += modif_inaltimeCOMB;
				else {
					if (yesORno == 1)
						VECTOR_inaltimi_COMB[i] += modif_inaltimeCOMB;
					else
						VECTOR_inaltimi_COMB[i] -= modif_inaltimeCOMB;
				}
			}

			for (int i = 0; i <= 9; i++)
				isCollisionCOMB[i] = 0;
			numarCombustibil = c.getRandom_1to9();
		}
	}
	/////--------------------------------combustibilul-------------------------------//////


	//// pentru animatia de zbor a avionului
	START++;
	if (START >= 55) {
		time_between += 0.1f;
		if (time_between != 0.0f) {
			if (rotateY > 0)
				rotateY -= 0.001f * 400;
			else
				rotateY += 0.001f * 400;
		}
	}

	//// camera First Person sa urmareasca avionul cand acesta e translatat pe OY de la mouse
	if (translateY_mem != translateY) {
		if (isThirdPerson == 1) {
			camera->Set(glm::vec3(-1.0f, 4.5f + translateY, 0.25f), glm::vec3(0, 4.5 + translateY, 0.25f), glm::vec3(0, 1, 0));
		}
	}
	translateY_mem = translateY;

	// vietile - se ia din teapot`ul rosu
	{
		hearts_x -= 15 * deltaTimeSeconds;
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(hearts_x, hearts_height, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));
		if(help_just_one == 0)
			RenderMesh_color(meshes["teapot"], shaders["ShaderLab5"], modelMatrix, glm::vec3(1, 0, 0));

		if (hearts_x <= -40)
		{
			hearts_x = 100 + c.getRandom_inaltimeCOMB() * 10;
			hearts_height = c.getRandom_inaltimeCOMB() + 4.5;
			help_just_one = 0;
		}	

		if ((isCollision(glm::vec3(hearts_x, hearts_height, 0), 0.1f, -1, planeBodylength + planeHeadlength + lengthSupport + lengthElice - 1,
			(float)(3.5 + translateY), (float)(3.5 + planeBodylength + translateY), 0.0f, planeBodylength) == 1) && numar_vieti < 3 && help_just_one == 0)
		{
			numar_vieti++;
			help_just_one = 1;
		}

	}
}


void Laborator5::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

//// pentru avion si obiecte care sunt formate din mai multe obiecte mai mici de culori diferite
void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

//// pentru obiecte de culori diferite
void Laborator5::RenderMesh_color(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, glm::vec3 &color)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	int loc_color = glGetUniformLocation(shader->program, "color_used");
	glUniform3fv(loc_color, 1, glm::value_ptr(color));

	mesh->Render();
}

void Laborator5::RenderMesh_texture(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->program)
		return;

	//render an object using the specified shader and the specified position
	glUseProgram(shader->program);


	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);
	}

	//draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
	
}


void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// translate the camera down
			camera->TranslateDownward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}
	}
	
}

void Laborator5::OnKeyPress(int key, int mods)
{
	// de pe C trec din FirstPerson in ThirdPerson si invers
	if (key == GLFW_KEY_C)
	{
		isThirdPerson = (isThirdPerson + 1) % 2;
		
		if(isThirdPerson == 1)
			camera->Set(glm::vec3(-1.0f, 4.5f + translateY, 0.25f), glm::vec3(0, 4.5 + translateY, 0.25f), glm::vec3(0, 1, 0));
		else
			camera->Set(glm::vec3(0, 4.0f, 8.7f), glm::vec3(0, 4, 0), glm::vec3(0, 1, 0));
	}
}

void Laborator5::OnKeyRelease(int key, int mods)
{
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	    // de pe click stanga controlez avionul
		// aici ii dau rotatia si translatia 
		if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
			if (START >= 35) {
				float sensivityOY = 0.001f;
				translateY -= deltaY * 15 * sensivityOY;

				rotateY -= sensivityOY * deltaY * 200;
				time_between = 0.0f;
			}
		}

		// modificare camera
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		{
			float sensivityOX = 0.001f;
			float sensivityOY = 0.001f;

			if (window->GetSpecialKeyState() == 0) {
				camera->RotateFirstPerson_OX(-2 * sensivityOX * deltaY);
				camera->RotateFirstPerson_OY(-2 * sensivityOY * deltaX);
			}

			if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
				camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
				camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
			}

		}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height) 
{
}

//functie care afiseaza fundalul din fata
glm::mat4 afisare_fundal_fata(glm::mat4 modelMatrix)
{
	{
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0, -10));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.5f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(600, 500, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, -0.5f, 0));
	}

	return modelMatrix;
}

//functie pentru afisare fundal dreapta
glm::mat4 afisare_fundal_dreapta(glm::mat4 modelMatrix)
{
	{
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(20.0f, 0.0f, 0.0f));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, 0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 500, 600));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -0.5f, -0.5f));
	}

	return modelMatrix;
}

// desenez marea
glm::mat4 draw_cylinder(glm::mat4 modelMatrix)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -20));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1, -4.95));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(25, 35, 10));
	return modelMatrix;
}

// desenez viata cu cele 3 sfere din TP
glm::mat4 draw_sphere1(glm::mat4 modelMatrix)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, 8.3, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	return modelMatrix;
}

glm::mat4 draw_sphere2(glm::mat4 modelMatrix)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-7, 8.3, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	return modelMatrix;
}

glm::mat4 draw_sphere3(glm::mat4 modelMatrix)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 8.3, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	return modelMatrix;
}


// desenez viata cu cele 3 sfere din FP
glm::mat4 draw_sphere1FP(glm::mat4 modelMatrix, float translateY)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(8, 8.3 + translateY, -8));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	return modelMatrix;
}

glm::mat4 draw_sphere2FP(glm::mat4 modelMatrix, float translateY)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(8, 8.3 + translateY, -7));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	return modelMatrix;
}

glm::mat4 draw_sphere3FP(glm::mat4 modelMatrix, float translateY)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(8, 8.3 + translateY, -6));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	return modelMatrix;
}


//helper sky
glm::mat4 draw_cube3(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(poz_third_cube + pas * i, inaltimeSky, zSky));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-10), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(10), glm::vec3(0, 1, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(translateSky, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-10), glm::vec3(0, 1, 0));
	return modelMatrix;
}

glm::mat4 draw_cube4(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 + poz_third_cube + pas * i, inaltimeSky + 0.1, 0.2 + zSky));
	glm::rotate(modelMatrix, RADIANS(-10), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-30), glm::vec3(0, 0, 1));
	glm::rotate(modelMatrix, RADIANS(10), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 2, 2));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(+30), glm::vec3(0, 0, 1));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(translateSky, 0, 0));
	glm::rotate(modelMatrix, RADIANS(-10), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-30), glm::vec3(0, 0, 1));
	return modelMatrix;
}

glm::mat4 draw_cube2(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.4 + poz_third_cube + pas * i, inaltimeSky, 0.3 + zSky));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-45), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-45), glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7, 0.7, 0.7));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1 / 0.7, 1 / 0.7, 1 / 0.7));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 1, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(translateSky, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-45), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-45), glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7, 0.7, 0.7));
	return modelMatrix;
}

glm::mat4 draw_cube1(glm::mat4 modelMatrix, float poz_third_cube, float pas, int i, float inaltimeSky, float zSky, float translateSky)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.7 + poz_third_cube + pas * i, inaltimeSky, zSky));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7, 0.7, 0.7));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-45), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(25), glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-25), glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1 / 0.7, 1 / 0.7, 1 / 0.7));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(translateSky, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7, 0.7, 0.7));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-45), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(25), glm::vec3(0, 0, 1));
	return modelMatrix;

}

//plane fall help
glm::mat4 plane_fall_help(glm::mat4 modelMatrix, float planeYFall)
{
	modelMatrix = glm::rotate(modelMatrix, -0.8f, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, 0.8f, glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, -0.8f, glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, 0.8f, glm::vec3(1, 0, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, planeYFall, 0));
	modelMatrix = glm::rotate(modelMatrix, -0.8f, glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, 0.8f, glm::vec3(1, 0, 0));
	return modelMatrix;
}

//plane draw help
glm::mat4 draw_plane(glm::mat4 modelMatrix, float translateY, float planeBodylength, float rotateY)
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, translateY, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 3.5, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(planeBodylength / 2, planeBodylength / 2, planeBodylength / 2));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(rotateY), glm::vec3(0, 0, 1));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-planeBodylength / 2, -planeBodylength / 2, -planeBodylength / 2));
	return modelMatrix;
}

//functie pentru testarea coliziunii dintre o sfera si un paralelipiped dat prin coordonatele maxime si minime
bool isCollision(glm::vec3 CenterCircle1, float lengthCircle1, float rectangleMinX, float rectangleMaxX, 
	float rectangleMinY, float rectangleMaxY, float rectangleMinZ, float rectangleMaxZ)
{
	float var = getMinim(CenterCircle1.x, rectangleMaxX);
	float x = getMaxim(rectangleMinX, var);

	float var1 = getMinim(CenterCircle1.y, rectangleMaxY);
	float y = getMaxim(rectangleMinY, var1);

	float var2 = getMinim(CenterCircle1.z, rectangleMaxZ);
	float z = getMaxim(rectangleMinZ, var2);

	float distance = sqrt((x - CenterCircle1.x) * (x - CenterCircle1.x) + (y - CenterCircle1.y) * (y - CenterCircle1.y) + (z - CenterCircle1.z) * (z - CenterCircle1.z));

	if (distance < lengthCircle1)
		return true;
	else
		return false;
}


//// functie pentru maximul dintre doua numere reale de tip float
float getMaxim(float number1, float number2)
{
	if (number1 > number2)
		return number1;
	else
		return number2;
}

//// functie pentru minimul dintre doua numere reale de tip float
float getMinim(float number1, float number2)
{
	if (number1 > number2)
		return number2;
	else
		return number1;
}

////functie pentru diferentele de la animatia avionului
void calculate_Collision_data(float length, float width, float pozX_RotationCenter, float pozY_RotationCenter, float pozZ_RotationCenter,
	float angle, float *diff_x, float *diff_y) {
	
	float latura_isoscel = sqrt(pozY_RotationCenter * pozY_RotationCenter + (length - pozX_RotationCenter) * (length - pozX_RotationCenter));
	float latura3_dinIsoscel = sqrt(latura_isoscel * latura_isoscel + latura_isoscel * latura_isoscel - 2 * latura_isoscel * latura_isoscel * 
	cos(angle));
	float unghi_isoscel = (float)(RADIANS(180.0f) - angle) / 2;
	float beta = asin(pozX_RotationCenter / latura_isoscel);
	float fi = (float)(90.0f - unghi_isoscel - beta);
	*diff_x = (sin(fi) * latura_isoscel);
	float help = (cos(fi) * latura_isoscel);
	*diff_y = help - width;
}
#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"
#include "RandomClass.h"

class Laborator5 : public SimpleScene
{
	public:
		Laborator5();
		~Laborator5();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		void RenderMesh_texture(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, Texture2D* texture1);
		void RenderMesh_color(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, glm::vec3 &color);
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		std::unordered_map<std::string, Texture2D*> mapTextures;

		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		glm::vec3 mapCenter = glm::vec3(0, 0, 0);

		//matricea de modelare
		glm::mat4 modelMatrix;

		//rotatia elicei avionului
		float rotateElice = 0;

		//// cu cat se muta avionul pe OY
		float translateY = 0; 

		bool renderCameraTarget;

		//variabila sa stiu ce tip de camera este
		int isThirdPerson = 0;

		//cu cat se roteste avionul de la mouse
		float rotateY = 0; 

		int ok = 0;

		//am nevoie de ele la rotatia din mouse
		float time_between;
		int START = 0;

		//// daca avionul a cazut in apa
		int isIn_water = 0; 

		float diff_onX;
		float diff_onY;

		//am nevoie sa tin camera dupa avion cand trec in First Person
		float translateY_mem = translateY;

		
		float translateTest = 0;
		float rotateSphere = 0;

		//viteza de rotire a cilindrului care reprezinta marea
		float rotateCylinder = 0;

		float rotateTest = 0;

		//variabile care ma ajuta la rotatia diferitelor cuburi din skies
		float rotateTest1 = 0; 
		float pas = 6.0f;

		float lengthCombustibil = 2.1f;
		float widthCombustibil = 5.3f;
		float heightCombustibil = 6.0f;
		float micsorareCombustibil = 0.8f;

		//// pozitiile sferelor /// sunt 3 sfere
		float VECTOR[3];

		////pentru testarea functiilor random
		RandomClass c;

		float Sphere_y[3];
		bool isCollisionSphere[3];
		float translateSphere;

		float planeBodylength = 0.5f;
		float planeHeadlength = 0.25f;
		float lengthSupport = 0.1f;
		float lengthElice = 0.1f;

		float translateCombustibil;
		float VECTORCOMB[10];
		float VECTOR_inaltimi_COMB[10];
		
		int numarCombustibil = 9;
		float modif_inaltimeCOMB;
		
		//daca o anumite bucata de combustibil din sir se roteste sau nu
		float rotateCOMB = 0;

		//daca am coliziune intre combustibil si avion
		int isCollisionCOMB[10];

		float lengthSkyCube;

		//// de aici incep constructia norului
		float poz_third_cube = 5.1f; 
		
		//depozitare date despre cuburile din sky
		float translateSky[3];
		float inaltimeSky[3];
		float zSky[3];
		int rotateSky3[3];
		int rotateSky4[3];
		int rotateSky2[3];
		int rotateSky1[3];

		//numarul de vieti ale playerului
		int numar_vieti = 3;

		//// daca au disparut vietile sau combustibilul, avionul o sa se scufunde
		int scufunda_avion;
		float save_translateY;

		//// rotatia avionului cand cade
		float planeFall; 

		//// caderea pe y a avionului
		float planeYFall;

		float save;

		float keep_Camera = 0;
		float time;
		int ok1 = 1;

		//date despre sferele care dau o viata in plus
		//viata o sa fie data daca 
		float hearts_x;
		float isCollision_heart;
		float hearts_height = 3.0f;
		int help_just_one = 0;

		//variabila in care tin punctajul
		int punctaj = 0.0;
};

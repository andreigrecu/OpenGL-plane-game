#pragma once
#include <string>
#include <math.h>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <iostream>

using namespace std;

class RandomClass {
	public:
		//// un numar real random intre 1 si 4
		float getRandom_1to4() {
			float random = (float)(rand() % 10) + 1;
			while (random >= 8 || random < 2)
				random = (float)(rand() % 10) + 1;

			float random1 = (float)(rand() % 10) + 1;
			while (random1 >= 7 || random1 < 3)
				random1 = (float)(rand() % 10) + 1;

			float random2 = (float)(rand() % 10) + 1;
			while (random2>= 7 || random2 < 3)
				random2 = (float)(rand() % 10) + 1;
			

			float rasp = (float)(random2 + random1 + random) / 3;
			
			return rasp;
		}

		//// un numar intreg random intre 1 si 9
		int getRandom_1to9() {
			int random = (rand() % 10) + 1 - 1;

			return random;
		}

		//// un numar intreg random intre 1 si 5
		int getRandom_1to5() {
			int random = (rand() % 10) + 1;
			while(random > 5 || random == 0)
				random = (rand() % 10) + 1;

			return random;
		}

		int yes_or_no() {
			int random = (rand() % 10) + 1;
			if (random > 5)
				return 1;
			else
				return 0;
		}

		//// inaltimea la care se afla combustibilul
		//// se modifica la fiecare redesenare 
		float getRandom_inaltimeCOMB() {
			float random = (float)(rand() % 10) + 1;
			while (random >= 3 || random < 0)
				random = (float)(rand() % 10) + 1;
			float random1 = (float)(rand() % 10) + 1;
			while (random1 >= 3 || random1 < 0)
				random1 = (float)(rand() % 10) + 1;

			float rez = (float)(random + random1) / 2;
			
			int CAZ = getRandom_1to9();
			if (CAZ == 1 || CAZ == 2 || CAZ == 3 || CAZ == 4 || CAZ == 5)
				return rez;
			else
				return -rez;
		}

		//// random daca un cub dintre cele ale 4 ale norilor se roteste
		//// se face la redesenarea fiecarui nor in dreapta scenei
		int isRotatingSky() {
			int random = (rand() % 10) + 1;

			if (random >= 5)
				return 0;
			else
				return 1;
		}

		//// random pentru pozitia pe y a norilor
		//// intre 6 si 9
		float getRandom_inaltimeSky() {
			float random = (float)(rand() % 10) + 1;
			while (random > 9 || random < 6)
				random = (float)(rand() % 10) + 1;

			float random1 = (float)(rand() % 10) + 1;
			while (random1 > 9 || random1 < 6)
				random1 = (float)(rand() % 10) + 1;

			float random2 = (float)(rand() % 10) + 1;
			while (random2 > 9 || random2 < 6)
				random2 = (float)(rand() % 10) + 1;

			float rez = (float)(random + random1 + random2) / 3;
			return rez;
		}

		//// random pentru pozitia pe z a norilor, intre 1 si 6
		float getRandom_zSky() {
			float random = (float)(rand() % 10) + 1;
			while (random > 6 || random < 1)
				random = (float)(rand() % 10) + 1;

			float random1 = (float)(rand() % 10) + 1;
			while (random1 > 6 || random1 < 1)
				random1 = (float)(rand() % 10) + 1;

			float random2 = (float)(rand() % 10) + 1;
			while (random2 > 6 || random2 < 1)
				random2 = (float)(rand() % 10) + 1;

			float rez = (float)(random + random1 + random2) / 3;
			return rez;
		}
};


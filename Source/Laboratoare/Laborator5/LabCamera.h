#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace Laborator
{
	class Camera
	{
	public:
		Camera()
		{
			position = glm::vec3(0, 2, 5);
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);
			distanceToTarget = 0.3f;
		}

		Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
		{
			Set(position, center, up);
		}

		~Camera()
		{ }

		// Update camera
		void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
		{
			this->position = position;
			forward = glm::normalize(center - position);
			right = glm::cross(forward, up);
			this->up = glm::cross(right, forward);
		}

		void MoveForward(float distance)
		{
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
		}

		void TranslateForward(float distance)
		{
			//  Translate the camera using the "forward" vector
			position += glm::normalize(forward) * distance;
		}

		void TranslateUpword(float distance)
		{
			// Translate the camera using the up vector
			if (position.y <= 6.0f )
				position += distance * glm::normalize(up);
		}

		void TranslateDownward(float distance)
		{
			// Translate the camera using the up vector
			if(position.y >= 4.0f)
				position -= distance * glm::normalize(up);
		}

		void TranslateRight(float distance)
		{
			position += distance * glm::normalize(right);
		}

		void RotateFirstPerson_OX(float angle)
		{
			///rotatie fata de axa right
			forward = glm::normalize(glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 1)); ///asta e vec3
			up = glm::normalize(glm::cross(right, forward));
		}

		void RotateFirstPerson_OY(float angle)
		{
			forward = glm::normalize(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1));
			right = glm::normalize(glm::rotate(glm::mat4(1.f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1));
			up = glm::normalize(glm::cross(right, forward));
		}

		void RotateFirstPerson_OZ(float angle)
		{
			right = glm::normalize(glm::rotate(glm::mat4(1.f), angle, forward) * glm::vec4(right, 0));
			up = glm::normalize(glm::rotate(glm::mat4(1.f), angle, forward) * glm::vec4(up, 0));
			forward = glm::normalize(glm::cross(up, right));
		}

		void RotateThirdPerson_OX(float angle)
		{
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OX(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OY(float angle)
		{
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OY(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OZ(float angle)
		{
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OZ(angle);
			TranslateForward(-distanceToTarget);
		}

		glm::mat4 GetViewMatrix()
		{
			// Returns the View Matrix
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 GetTargetPosition()
		{
			return position + forward * distanceToTarget;
		}

	public:
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
	};
}
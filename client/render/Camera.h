
#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace sh {

	class Camera {
	public:

		inline void updateProjection(size_t width, size_t height) {
			projection = glm::perspective(70.f, ((float) width / height), 1.f, 1000.f);
		}

		inline glm::mat4 getView() const {
			glm::mat4 out = glm::translate(glm::identity<glm::mat4>(), pos);
			return out * glm::mat4(rot) * projection;
		}

	private:

		glm::mat4 projection;

		glm::quat rot = glm::quatLookAt(glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
		glm::vec3 pos;
	};
} // sh 

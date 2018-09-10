//
// Created by Leonard VAN GEND on 2018/09/10.
//

#ifndef LEARNINGOPENGL_TRANSFORMATION_HPP
#define LEARNINGOPENGL_TRANSFORMATION_HPP


#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Transformation {
public:
	Transformation();
	Transformation(const Transformation &obj);
	Transformation& operator =(const Transformation &obj);
	~Transformation();
	glm::mat4 getTransformationMatrix() const;
	static Transformation getInterpolatedTransformation(const Transformation &t1, const Transformation &t2,
														float interpolationValue);

	glm::vec3 m_translation;
	glm::vec3 m_rotation;
	glm::vec3 m_scaling;

	Transformation operator+ (Transformation &rhs) const;


private:
	static glm::vec3 getInterpolatedVec3(glm::vec3 startVector, glm::vec3 endVector, float interpolationValue);
};


#endif //LEARNINGOPENGL_TRANSFORMATION_HPP

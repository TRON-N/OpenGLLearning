//
// Created by Leonard on 2018/09/14.
//

#ifndef LEARNINGOPENGL_CAMERA_HPP
#define LEARNINGOPENGL_CAMERA_HPP


#include "ModelManagement/Models/Transformation.hpp"
#include "Shader.hpp"
#include "ModelManagement/Animation/KeyFrame.hpp"
#include "ModelManagement/Animation/Animation.hpp"

class Camera : public i_Observer {
public:
	Camera(Shader *shader, float cameraViewWidth, float cameraViewHeight);
	~Camera();
	Camera(const Camera &obj);
	Camera &operator=(const Camera &obj);

	void translate(glm::vec3 translationAlongEachAxis);
	void rotate(glm::vec3 rotationAboutEachAxis);

	void animatedMove(float durationInSeconds, glm::vec3 destinationTranslation, glm::vec3 destinationRotation);
	void update();


	const Transformation &getTransformation();
	const glm::vec2 getWidthAndHeight();
	void notify(void *arg) override;

private:
	void sendTransfromationMatrixToShader();

	Transformation m_transformation;
	Shader *m_shaderProgram;
	glm::vec2 m_widthAndHeight;
	Animation m_animation;
	bool m_isAnimationActive;
};


#endif //LEARNINGOPENGL_CAMERA_HPP

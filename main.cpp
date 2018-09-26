#include <SDL.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <TextDisplaySystem.hpp>
#include <glad/glad.h>
#include <openGLFunctionCallErrorManagementWrapper.hpp>
#include "AssimpInterpreter.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "ModelDispenser.hpp"

class testNotification : public i_Observer {
public:
	bool m_isActive;

	testNotification() {
		this->m_isActive = false;
	}

	void notify(void *arg) override {
		this->m_isActive = false;
	}
};

int main(int argc, char *argv[]) {
	if (argc == 0 && argv == nullptr)
		std::cout << "no args" << std::endl;


	{

		Window gameWindow(false, 3);
		Renderer renderer(gameWindow.getWindowPtr());
		gameWindow.registerObserver(&renderer);

		Animation testAnimation;

		Transformation keyFrame1Transformation;
		KeyFrame keyFrame1(0.0f, keyFrame1Transformation);

		Transformation keyFrame2Transformation;
		keyFrame2Transformation.m_translation = glm::vec3(0.1, -0.2, 0);
//	keyFrame2Transformation.m_rotation = glm::vec3(0, 0, -10);
		keyFrame2Transformation.m_scaling = glm::vec3(1.2, 0.6, 1.2);
		KeyFrame keyFrame2(0.10f, keyFrame2Transformation);

		Transformation keyFrame3Transformation;
		keyFrame3Transformation.m_translation = glm::vec3(0.15, 0.7, 0);
//	keyFrame3Transformation.m_rotation = glm::vec3(0, 0, -10);
		keyFrame3Transformation.m_scaling = glm::vec3(0.8, 1.4, 0.8);
		KeyFrame keyFrame3(0.20f, keyFrame3Transformation);

		Transformation keyFrame4Transformation;
		keyFrame4Transformation.m_translation = glm::vec3(0.2, 1.5, 0);
//	keyFrame4Transformation.m_rotation = glm::vec3(0, 0, -20);
		KeyFrame keyFrame4(0.25f, keyFrame4Transformation);

		Transformation keyFrame5Transformation;
		keyFrame5Transformation.m_translation = glm::vec3(0.4, -0.2, 0);
//	keyFrame4Transformation.m_rotation = glm::vec3(0, 0, -20);
		keyFrame5Transformation.m_scaling = glm::vec3(1.2, 0.6, 1.2);
		KeyFrame keyFrame5(0.35f, keyFrame5Transformation);

		Transformation keyFrame6Transformation;
		keyFrame6Transformation.m_translation = glm::vec3(0.4, 0, 0);
		KeyFrame keyFrame6(0.37f, keyFrame6Transformation);


		testAnimation.addKeyFrame(keyFrame1);
		testAnimation.addKeyFrame(keyFrame2);
		testAnimation.addKeyFrame(keyFrame3);
		testAnimation.addKeyFrame(keyFrame4);
		testAnimation.addKeyFrame(keyFrame5);
		testAnimation.addKeyFrame(keyFrame6);

		std::string animationName = "testAnimation";

		ModelDispenser modelDispenser;

		Model *boxModel = modelDispenser.getModel("cubo.obj", "../3dModelsAndTextures");
		boxModel->scale(glm::vec3(20, 1, 12));
		boxModel->translate(glm::vec3(15, -5.0f, 16));

		std::vector<Model *> modelList;
		std::vector<testNotification *> notificationClassList;
		for (unsigned int i = 0; i < 8; i++) {
			notificationClassList.push_back(new testNotification);
			modelList.push_back(modelDispenser.getModel("ballo2.obj", "../3dModelsAndTextures"));
			modelList.back()->addAnimation(testAnimation, animationName);
			modelList.back()->translate(glm::vec3(-5.0f + (float) i, 1.0f, 10.0f + (float) i * 3));
			modelList.back()->registerObserver(notificationClassList.back());
		}

//		Transformation explodeTrans0;
//		explodeTrans0.m_scaling = {0.0001, 0.0001, 0.0001};
		KeyFrame explodeKeyFrame(0.0f, Transformation());
		Transformation explodeTrans;
		explodeTrans.m_scaling = {1, 1, 1};
		KeyFrame explodeKeyFrame2(0.15f, explodeTrans);
		Transformation explodeTrans2;
		explodeTrans2.m_scaling = {0, 0, 0};
		KeyFrame explodeKeyFrame3(0.3f, explodeTrans2);
		Transformation explodeTrans3;

		Animation explodeAnimation;
		explodeAnimation.addKeyFrame(explodeKeyFrame);
		explodeAnimation.addKeyFrame(explodeKeyFrame2);
		explodeAnimation.addKeyFrame(explodeKeyFrame3);

		Model *explodeMod = modelDispenser.getModel("explosion.obj", "../3dModelsAndTextures");
		explodeMod->addAnimation(explodeAnimation, "explode");
		explodeMod->translate(glm::vec3(0.0f, 1.0f, 10.0f));
		testNotification explodeNotifier;
		explodeMod->registerObserver(&explodeNotifier);

		Shader &shaderProgram = renderer.getShaderProgram();
		shaderProgram.bind();

		Camera camera(&shaderProgram, 30, 30);
		glm::vec3 cameraRotation(-45, 5, 0);
		camera.rotate(cameraRotation);

		glm::vec3 cameraTrans = glm::vec3(-5.0f + camera.getWidthAndHeight().x / 2, 0.0f, 10.0f);
		cameraTrans.y -= 13;
		cameraTrans.z += 35;
		camera.setTranslationLimits({cameraTrans.x, cameraTrans.y, cameraTrans.z},
									{cameraTrans.x + (40 - camera.getWidthAndHeight().x),
									 cameraTrans.y, cameraTrans.z});
		camera.translate(cameraTrans);

		TextDisplaySystem textDisplaySystem("../Xcelsion.ttf", 48);

		glm::mat4 projection = glm::ortho(0.0f, (float) gameWindow.getCurrentResolution()[0],
										  (float) gameWindow.getCurrentResolution()[1], 0.0f);
		Shader &textShader = textDisplaySystem.getTextShader();
		textShader.bind();
		textShader.setUniformMatrix4fv("projection", glm::value_ptr(projection));

		TextModel *fontModel = textDisplaySystem.getTextModel("BombiBoi!!");
		fontModel->translate({0, 200, -1.0f});

		// render loop
		// -----------

		bool loop = true;
		while (loop) {

			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
						case SDLK_0:
							gameWindow.setResolution(0);
							break;
						case SDLK_1:
							gameWindow.setResolution(1);
							break;
						case SDLK_2:
							gameWindow.setResolution(2);
							break;
						case SDLK_3:
							gameWindow.setResolution(3);
							break;
						case SDLK_4:
							gameWindow.setResolution(4);
							break;
						case SDLK_5:
							gameWindow.setResolution(5);
							break;
						case SDLK_6:
							gameWindow.setResolution(6);
							break;
						case SDLK_7:
							gameWindow.setResolution(7);
							break;
						case SDLK_8:
							gameWindow.setResolution(8);
							break;
						case SDLK_TAB:
							gameWindow.toggleFullScreen();
							break;
						default:
							loop = false;
					}
				}
				if (event.type == SDL_QUIT) {
					loop = false;
					break;
				}
			}

			shaderProgram.bind();
			boxModel->draw(shaderProgram);
			explodeMod->draw(shaderProgram);
			if (explodeNotifier.m_isActive == false) {
				explodeMod->scale({1, 1, 1});
				explodeMod->startAnimation("explode");
				explodeNotifier.m_isActive = true;
			}
//			testBoxSpecial->draw(shaderProgram);
//			testBoxSpecial2->draw(shaderProgram);
			for (unsigned int i = 0; i < modelList.size(); i++) {
				Model &currentModel = *modelList[i];
				testNotification &notification = *notificationClassList[i];
				currentModel.draw(shaderProgram);
				camera.update();

				if (i == 0) {
					cameraTrans.x = currentModel.getModelTransformation().m_translation.x;
					camera.translate(cameraTrans);
				}

				if (currentModel.getModelTransformation().m_translation.x > 35) {
					currentModel.translate(glm::vec3(-5.0f + (float) i, 0.0f, 10.0f + (float) i * 3));
					if (i == 0)
						camera.animatedMove(0.6f, camera.getMinTranslation(), cameraRotation);
				}

				if (notification.m_isActive == false) {
					currentModel.startAnimation(animationName);
					notification.m_isActive = true;
				}
			}
			GL_ERROR_WRAPPER(glDisable(GL_DEPTH_TEST));
			GL_ERROR_WRAPPER(glEnable(GL_BLEND));
			GL_ERROR_WRAPPER(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			textShader.bind();
			fontModel->draw(textShader, {1, 0, 0});
			GL_ERROR_WRAPPER(glEnable(GL_DEPTH_TEST));
			GL_ERROR_WRAPPER(glDisable(GL_BLEND));
			renderer.update();

		}

	}

	std::cout << "Program Ended" << std::endl;
	return 0;
}
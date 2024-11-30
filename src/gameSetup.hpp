#ifndef DEF_GAMESETUP_HPP
#define DEF_GAMESETUP_HPP
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include"common/objloader.hpp"
#include"common/skybox.h"
#include"common/car.h"
#include"common/decor.h"
#include"common/water.h"
#include"common/carAI.hpp"
#include"common/AllCars.h"
#include"common/shader.hpp"
#include"common/texture.hpp"
#include"common/camera.hpp"
#include"common/hud.hpp"
#include"common/sound.h"
#include"common/text2D.hpp"
#include<GL/glut.h>
#define R 45

using namespace glm;


inline float dist(int x1, int y1, int x2, int y2);

class setup
{
	public:
		
	setup();
	~setup();
	void init();
	void keyboard(unsigned char key, int x, int y);
	void mouseMove(int mx,int my);
	void specialKey(int key, int x, int y);
	void mouseState(int button, int state, int x, int y);
	void update();
	void draw();
	void controlSpecialPassiveKeyboard(int key,int x, int y);
	void passiveKeyboard(unsigned char key, int x, int y);
	void gestionHud(hud* h);

	
	private:
		
	void gestionCam();
	void updateCamera();
	void collisionCarAI();
	void collisionCarAndWall();
	bool linePointDetection(float x1, float y1, float x2, float y2, float px, float py);
	void collisionCar(glm::vec3 pos,glm::vec3 pos2);
	void carMovement(float speed);
	void cameraMovement(float speed);
	void collisionCameraAndWall();
	void resetCar(bool startFreeCamera);
	std::vector<allVehicule*> allCars;
	std::vector<decor *> levels;
	water *ocean;
	water *engrenage;
	skybox* sky;
	int step;
	int step_cam_follow;
	float fog_variation;
	float deltaTime;
	float oldTime;
	double fps;
	sound* audio;
	hud* hud_;
	hud* hud2_;
	camera* cam;
	int sound1;
	bool startFreeCamera,startcameraFollow;
	textHUD* tHUD;
	float time;
	bool finishedGame;
	bool keyV;


	
};

#endif


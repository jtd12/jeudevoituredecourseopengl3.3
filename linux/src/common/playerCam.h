#ifndef DEF_PLAYERCAM_H
#define DEF_PLAYERCAM_H
#define GLEW_STATIC
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<vector>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"objloader.hpp"
#include"camera.hpp"
#include<cmath>
#include<iostream>
#include<GL/freeglut.h>
#include"mathsutils/collisionplane.h"
#include"mathsutils/collision.h"
#define pi 3.14159265359 // on definit un nombre pi

class playerCam
{
public:
	playerCam(const char * n,glm::vec3 location,float sprints,float normals,float looks);
	~playerCam();
	//camera cam;
void showBalle();
void updateBalle();

void update(std::vector<collisionplane>& collplane);
	 		void setPosition(glm::vec3 pos);
	 		void setLocation(glm::vec3  loc);
	 		void setLocation2(glm::vec3 newLoc);
			glm::vec3 getLocation();
			void setJump();
			void setSprint();
			void stopSprint();
			void relacherSpecial(char key,int x, int y);
	    	glm::vec3 dir;
			
private:
		unsigned int w;
		float speed;
		int points;
		std::vector<unsigned int> frames;
		unsigned int a_;
		bool up,down,right,left;
		float curFrame;
		std::string name;
		int mesh;
		std::string file_;
		glm::vec3 force;
		bool isground,iscollision, issprint;
		int headPosition;
		bool headUp;
		glm::vec3 loc;
		float rot;
		float rot2;
		float energy;
		float 	sprintspeed;
		float normalspeed,lookSpeed;
		glm::vec3 rotation;
  		bool balleVisible;
		float bulletDelay;
		int curWep;
		int health;
		//arme *arm;
		bool isWeapon;
	
		glm::vec3 direction;
		unsigned int attackSound;
};
#endif

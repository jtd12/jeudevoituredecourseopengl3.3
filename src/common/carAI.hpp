#ifndef DEF_CAR_AI_HPP
#define DEF_CAR_AI_HPP
#include"car.h"
#include <C:\library\glm\glm\glm.hpp>
#include <C:\library\glm\glm\gtc\matrix_transform.hpp>
#include <C:/library/glm/glm/gtx/transform.hpp>

#include<vector>
#include<math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include<string>
#include"C:\library\freeglut\include\GL\freeglut.h"
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
        

const int num=8; //checkpoints
static int points[num][2] = {1000,1160,
                      5000,1160,
                      5050,1900,
					  -9250,1800,
					  -9250, -20,
					  -2700,-100,
					  -2700,1200,
					  -1500,1250};
   

class vehiculeAI
{
		public:
		vehiculeAI(const char* n,glm::vec3 location, float sprints,float looks,const char * filename,const char *tex);
		~vehiculeAI();
		void ouvrirPorte1();
		void ouvrirPorte2();
		void update();
		void draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix);
		void collisionCarAndGround();
		void setPosition(glm::vec3 pos);
		void setLocation(glm::vec3 vec);
		glm::vec3 getLocation();
			void move();
			void setRotation(glm::vec3 r);
			glm::vec3 getRotation();
			void setLocationIncX(float y);
			void setLocationIncZ(float y);
			void setLocationInc(glm::vec3 l);
			float setSpeed(float num);
		void setSpeed(float s,float speedJoy);
		float getSpeed();
		float getMaxSpeed();
		void findTarget();
		void setActif(bool b);
		bool getActif();
		void fermerPorte1();
		void fermerPorte2();
		int getA();
		void setA(int A);



	
		
	private:
		
		
	std::vector<roue *> wheel;	
	glm::vec3 loc;
	glm::vec3 force;
	std::string name;
	glm::vec3 direction;
	bool isground,iscollision, issprint,actif;
	float sprintspeed;
	float lookspeed;
	glm::vec3 pos;
	float acc, dec,dec2;
	glm::vec3 a;
	
 	float angle;
	float turnSpeed;
	float speed;
	float maxSpeed;	
	float s;
	float rr,rr2;
	int nn;
	int randNumber;
		objloader *obj;
			std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	GLuint uvbuffer;
GLuint vertexbuffer;
GLuint programID ;
GLuint Texture;
GLuint TextureID ;
GLuint	 vertexUVID ;
 GLuint	vertexPosition_modelspaceID;
 GLuint	MatrixID;
};

#endif

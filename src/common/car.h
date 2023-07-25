#ifndef DEF_CAR_H
#define DEF_CAR_H
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include"shader.hpp"
#include"objloader.hpp"
#include <C:\library\glm\glm\glm.hpp>
#include <C:\library\glm\glm\gtc\matrix_transform.hpp>
#include <C:/library/glm/glm/gtx/transform.hpp>
#include<vector>
#include<math.h>
#include<string>
#include"particulesystem.h"
#include"C:\library\freeglut\include\GL\freeglut.h"
#define ni 8
#define SPACEBAR 32

class roue
{
public:
		roue(const char * filename);
		~roue();
		void update();
		void draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix);
		glm::vec3 getRotation();
		void setRotationz(float m);
		void setRotationzegal(float m);
		void setRotationy(float m);
		void setRotationyegal(float m);
		void setLocation(glm::vec3 l);
		
	private:
		objloader *obj;	
		glm::vec3 rot_roue;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals; // Won't be used at the moment.
		GLuint uvbuffer;
		GLuint vertexbuffer;
		GLuint programID ;
		GLuint Texture;
		GLuint TextureID ;
		GLuint	 vertexUVID ;
		 GLuint	vertexPosition_modelspaceID;
		 GLuint	MatrixID;
		 glm::vec3 loc;
};



class vehicule
{
	public:
		vehicule( const char* n, glm::vec3 location,float sprints,float normales,float looks);
		~vehicule();
		void ouvrirPorte1();
		void ouvrirPorte2();
		void update();
		void updateControl();
		void draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix);
		void collisionCarAndGround();
		void setPosition(glm::vec3 pos);
		void setLocation(glm::vec3 vec);
		glm::vec3 getLocation();
		void setLocationIncX(float y);
		void setLocationIncZ(float y);
			void move();
			void setRotation(glm::vec3 r);
			glm::vec3 getRotation();
			int getUP();
			int getDOWN();
			int getRIGHT();
			int getLEFT();
			void setUP(int num);
			void setDOWN(int num);
			void setRIGHT(int num);
			void setLEFT(int num);
			float setSpeed(float num);
		void setSpeed(float s,float speedJoy);
		float getSpeed();
		float getMaxSpeed();
		void keyboard(char key, int x, int y);
		void keyboardUP(char key, int x, int y);
		void inputSpecial(char key,int x, int y);
		void inputSpecialUP(char key,int x, int y);
		void control();
		void setActif(bool b);
		bool getActif();
		void fermerPorte1();
		void fermerPorte2();
		int getA();
		void setA(int A);
	
		std::vector<roue *> wheel;
		objloader *obj;
	

		
	private:

	glm::vec3 force;
	std::string name;
	glm::vec3 direction;
	bool isground,iscollision, issprint,actif;
	float sprintspeed,normalspeed;
	float lookspeed;
	float acc, dec,dec2;
	glm::vec3 a;
	glm::vec3 loc;
	int up,down,left,right,a_touch;
 	float angle;
	float turnSpeed;
	float speed;
	float maxSpeed;	
	float s;
	float rr,rr2;
	std::vector<particule*> part;
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

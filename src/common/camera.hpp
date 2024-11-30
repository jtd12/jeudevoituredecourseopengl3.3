#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include<GL/glut.h>
#include"objloader.hpp"
#include"shader.hpp"
using namespace glm;


class bbBoxCam
{
	
	public:
		bbBoxCam(const char * filename,glm::vec3 l);
		~bbBoxCam();
		void update();
		void draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix);
		glm::vec3 getRotation();
		void setRotationz(float m);
		void setRotationzegal(float m);
		void setRotationy(float m);
		void setRotationyegal(float m);
		void setLocation(glm::vec3 l);
		glm::vec3 getLocation();
		void setInFrontOfCamera(const glm::vec3& cameraPosition, const glm::vec3& cameraOrientation, float distanceFromCamera);
		
	private:
		objloader *obj;	
		glm::vec3 rot;
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


class camera
{

public:	
camera();
camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical);
~camera();
void orienter(int xRel, int yRel);
void collisionCameraAndGround();
void computeMatricesFromInputs(bool startfreecamera);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void setPosition(glm::vec3 loc);
void setTarget(glm::vec3 loc);
void inputSpecial(char key,int x, int y);
void inputSpecialUP(char key,int x, int y);
void deplacer();
void controlMouse(int button, int state, int x, int y);
void tourner(int x, int y);
void setSpeed(float s);
float getSpeed();
glm::vec3 getLocation();
glm::vec3 getRotation();
std::vector<bbBoxCam*> bb;
std::vector<bbBoxCam*> collidersDetection;
		
private:
	
	float m_phi;
    float m_theta;
    glm::vec3 m_orientation;

    glm::vec3 m_axeVertical;
    glm::vec3 m_deplacementLateral;

    bool up,right,left,down;
    glm::vec3 position;
 	glm::vec3 target;
 	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	bool mi;
	int MidX,MidY;
	float speed;
	
    
};


#endif

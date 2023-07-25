#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"C:\library\glm\glm\glm.hpp"
#include <C:/library/glm/glm/gtc/matrix_transform.hpp> 
#include"C:\library\freeglut\include\GL\freeglut.h"

using namespace glm;


class camera
{

public:	
camera();
camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical);
~camera();
void orienter(int xRel, int yRel);
void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void setPosition(glm::vec3 loc);
void setTarget(glm::vec3 loc);
void inputSpecial(char key,int x, int y);
void inputSpecialUP(char key,int x, int y);
void deplacer();
void controlMouse(int button, int state, int x, int y);
void tourner(int x, int y);

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
    
};


#endif

#ifndef DEF_PARTICULESYSTEM_H
#define DEF_PARTICULESYSTEM_H
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include"shader.hpp"
#include <C:\library\glm\glm\glm.hpp>
#include <C:\library\glm\glm\gtc\matrix_transform.hpp>
#include <C:/library/glm/glm/gtx/transform.hpp>
#include<vector>
#include<bits/stdc++.h>
#include<math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include<string>
#include"C:\library\freeglut\include\GL\freeglut.h"
#include <sstream>

static float kelvinR[]={1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,0.907,0.827,0.762,0.711,0.668,0.632,0.602};
static float kelvinG[]={0.007,0.126,0.234,0.349,0.454,0.549,0.635,0.710,0.778,0.837,0.890,0.937,0.888,0.839,0.800,0.766,0.738,0.714,0.693};
static float kelvinB[]={0.000,0.000,0.010,0.067,0.151,0.254,0.370,0.493,0.620,0.746,0.869,0.988,1.000,1.000,1.000,1.000,1.000,1.000,1.000};

static double rand_normal(double mean, double stddev);
static float MAP(float au32_IN, float au32_INmin, float au32_INmax, float au32_OUTmin, float au32_OUTmax);
static double randMToN(double M, double N);



class particule
{
	


	
 int n=50;
 float d=20.0;
 float rot;
 int *x=new int[n];
 int *y=new int[n];
 int *ttl=new int[n];
 int *dx=new int[n];
 int *dy=new int[n];
 GLuint	MatrixID;
GLuint colorbuffer;
GLuint uvbuffer;
GLuint vertexbuffer;
GLuint programID ;
GLuint Texture;
GLuint TextureID ;
GLuint	 vertexUVID ;
GLuint	vertexPosition_modelspaceID;
int g=1;
float th,ra,a;

 
public:
	particule(float tmax);
	~particule();
	void draw(float zpos,float tmax,glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix,glm::vec3 loc);
	int getNumber();
	void setNumber(int numb);
	void setNumberEgal(int numb);
	
};

#endif

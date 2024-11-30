#ifndef OBJLOADER_H
#define OBJLOADER_H
#include<stdio.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include"texture.hpp"
#include <cstdlib>
#include<GL/gl.h>
#include<GL/glu.h>
#include<cmath>
#include <map>
#define MAXLEVEL 4
#define M_PI    3.14159265358979323846

using namespace std;



class objloader
{

public: 

objloader();
~objloader();
int load(const char* path,std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2>& uvs,
	std::vector<glm::vec3> & normales);
int loadAnimation(std::vector<unsigned int>& frames, std::string filename, unsigned int num,
std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2>  & uvs,
	std::vector<glm::vec3>  & normales);

	//void dessineSceneXY();
	//void dessineSceneYZ();
	//void dessineSceneXZ();
void update();
void draw();



textures text;


private:


};

#endif

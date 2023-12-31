#ifndef DEF_WATER_H
#define DEF_WATER_H
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include"C:\library\glm\glm\glm.hpp"
#include <C:/library/glm/glm/gtc/matrix_transform.hpp>
#include<vector>
#include <gl/gl.h>
#include<gl/glu.h>
#include"shader.hpp"
#include"objloader.hpp"
#include<iostream>
#include<string>

class water
{
	public:
		water(const char * c,const char* map,const char* tex);
		~water();
		void update();
		void draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix);
		
	private:
		
				std::string name;
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
			 objloader *obj;
};

#endif

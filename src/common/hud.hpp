#ifndef DEF_HUD_HPP
#define DEF_HUD_HPP
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include <C:\library\glm\glm\glm.hpp>
#include <C:/library/glm/glm/gtc/type_ptr.hpp>
#include <C:\library\glm\glm\gtc\matrix_transform.hpp>
#include <C:/library/glm/glm/gtx/transform.hpp>
#include<vector>
#include<math.h>
#include<string>
#include"C:\library\freeglut\include\GL\freeglut.h"
#include"shader.hpp"
#include"texture.hpp"

using namespace glm;



class hud
{
	public:
		hud();
		~hud();
		void init(const char * name,glm::vec3 pos,glm::vec3 pos2,glm::vec3 pos3,glm::vec3 pos4);
		void draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix,glm::vec3  scale);
		void setPosition(glm::vec3 loc);
		void setRotation(glm::vec3 rot_);
		void tournerAiguille(float s);

		
		
	private:
		GLuint vertexbuffer;
		GLuint VertexArrayID;
		GLuint MatrixID;
		GLuint programID ;
		GLuint uvbuffer;
		GLuint vertexUVID;
		GLuint vertexPosition_modelspaceID;
		GLuint TextureID;
		GLuint Texture;
		textures tex;
		glm::vec3 position;
		glm::vec3 rot;
		float turn;
		
	

};

#endif

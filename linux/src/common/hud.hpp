#ifndef DEF_HUD_HPP
#define DEF_HUD_HPP
#define GLEW_STATIC
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include<vector>
#include<math.h>
#include<string>
#include<GL/glut.h>
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

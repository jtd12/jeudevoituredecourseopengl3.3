#ifndef DEF_DECOR_H
#define DEF_DECOR_H
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"objloader.hpp"
#include"shader.hpp"
#include"texture.hpp"


class decor
{
	public:
		decor(const char* c, 
		const char* map,const char *tex); // Won't be used at the moment.);
		~decor();
		void update();
		void draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix);
std::string& getName();

 	std::vector<glm::vec3>& getSpawnPoints();
 	
	private:
		objloader *obj;
	
	std::vector<glm::vec3> spawnpoints;
	std::string name;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	GLuint uvbuffer;
GLuint vertexbuffer;
GLuint programID ;
GLuint Texture;
GLuint Texture2;
GLuint TextureID ;
GLuint TextureID2 ;
GLuint	 vertexUVID ;
 GLuint	vertexPosition_modelspaceID;
 GLuint	MatrixID;
	
};
#endif

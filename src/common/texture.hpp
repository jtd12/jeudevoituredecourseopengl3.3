#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"C:\library\glm\glm\glm.hpp"
#include <C:/library/glm/glm/gtc/matrix_transform.hpp>
#define GL_BGR 0x80E0


class textures
{
	GLuint texture_;
public:
textures();
// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
//// or do it yourself (just like loadBMP_custom and loadDDS)
//// Load a .TGA file using GLFW's own loader
//GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

};

#endif

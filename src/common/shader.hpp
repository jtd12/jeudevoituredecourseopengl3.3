#ifndef SHADER_HPP
#define SHADER_HPP
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include"C:/library/glew-1.13.0/include/GL/glew.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"C:\library\glm\glm\glm.hpp"
#include <C:/library/glm/glm/gtc/matrix_transform.hpp> 

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif

#ifndef SHADER_HPP
#define SHADER_HPP
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif

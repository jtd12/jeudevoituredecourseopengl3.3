#include"hud.hpp"
/*
static const GLfloat g_vertex_buffer_data[] = {
     	3.5f/4,1.0f/4,1.0f/2,
		2.0f/4,1.0f/4, 1.0f/2,
		3.5f/4, 3.0f/4, 1.0f/2,
		 2.0f/4,3.0f/4,1.0f/2,
		 
	 
		  
};
*/

	static const GLfloat g_uv_buffer_data[] = { 
	      0.0f, 0.0f,    // side 1
          1.0f, 0.0f, 
          0.0f, 1.0f, 
          1.0f, 1.0f, 
      

	};


hud::hud()
{
}
hud::~hud()
{
	
}
void hud::init(const char * name,glm::vec3 pos,glm::vec3 pos2,glm::vec3 pos3,glm::vec3 pos4)
{
	turn=0.0f;
 GLfloat g_vertex_buffer_data[12];

g_vertex_buffer_data[0] = pos.x/4;
g_vertex_buffer_data[1] = 	 pos.y/4;
g_vertex_buffer_data[2] = pos.z/2;
g_vertex_buffer_data[3] = 	pos2.x/4;
g_vertex_buffer_data[4] = pos2.y/4; 
g_vertex_buffer_data[5] = pos2.z/2;
g_vertex_buffer_data[6] = 	pos3.x/4; 
g_vertex_buffer_data[7] = pos3.y/4;
g_vertex_buffer_data[8] = pos3.z/2;
g_vertex_buffer_data[9] =  pos4.x/4;
g_vertex_buffer_data[10] = pos4.y/4;
g_vertex_buffer_data[11] = pos4.z/2;
	
	
	// Initialize the VBO data
programID = LoadShaders( "data/shaders/SimpleVertexShader.vertexshader", "data/shaders/SimpleFragmentShader.fragmentshader" );
	// Get a handle for our "MVP" uniform
MatrixID = glGetUniformLocation(programID, "MVP");

 vertexUVID = glGetAttribLocation(programID, "vertexUV");

 Texture = tex.loadBMP_custom(name);
	
	// Get a handle for our "myTextureSampler" uniform
 TextureID  = glGetUniformLocation(programID, "myTextureSampler");


// Generate 1 buffer, put the resulting identifier in vertexbuffer
glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	
}

void hud::tournerAiguille(float s)
{
		turn=s;
}
void hud::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix,glm::vec3  scale)
{

		glUseProgram(programID);
	
		 glm::mat4  translation2= glm::translate(ModelMatrix, glm::vec3(0, 100,-100));
		 glm::mat4  translation=   glm::translate(ModelMatrix,glm::vec3(position.x, position.y+30, position.z)) ;
		 	glm::vec3 myRotationAxis( 0.0f, 0.5f, 0.0f);
		 	glm::vec3 myRotationAxis2( 0.0f, 0.5f, 0.0f);
		 		glm::vec3 myRotationAxis3( 0.0f, 0.0f, 0.5f);
  glm::mat4 rotMatrix= glm::rotate( rot.y, myRotationAxis );
  glm::mat4 rotMatrix2= glm::rotate( 1.5f, myRotationAxis2 );
    glm::mat4 rotMatrix3= glm::rotate(turn, myRotationAxis3 );
  glm::mat4 scaling = glm::scale(ModelMatrix,glm::vec3( scale.x, scale.y ,scale.z));
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix*translation*rotMatrix2*rotMatrix*rotMatrix3*scaling;


		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
	// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);
		
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
   3,                  // size
   GL_FLOAT,           // type
   GL_FALSE,           // normalized?
   0,                  // stride
   (void*)0            // array buffer offset
);

glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

// Draw the triangle !
glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
glDisableVertexAttribArray(0);

}

void hud::setPosition(glm::vec3 loc)
{
	position=loc;
}

void hud::setRotation(glm::vec3 rot_)
{
	rot.y=rot_.y;
}



#include"skybox.h"


skybox::skybox()
{

	obj=new objloader();
	
    programID = LoadShaders( "data/shaders/TransformVertexShader_skybox.vertexshader", "data/shaders/TextureFragmentShader_skybox.fragmentshader" );
	
	MatrixID = glGetUniformLocation(programID, "MVP");
	
	 vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	 vertexUVID = glGetAttribLocation(programID, "vertexUV");
	
	 Texture = obj->text.loadBMP_custom("data/sky/front.bmp");

	// Get a handle for our "myTextureSampler" uniform
	 TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	
    glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW); 
	glDisable(GL_CULL_FACE);

}
 
skybox::~skybox()
{
      delete obj;
}



void skybox::update()
{
	rot+=2.0f;
}

float skybox::getRot()
{
return rot;	
}

void skybox:: drawSkybox(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
{


		glUseProgram(programID);
		
		glm::mat4  translation= glm::translate(ModelMatrix, glm::vec3(0, 0, 0));
		glm::mat4 scaling = glm::scale(ModelMatrix,glm::vec3( 20000.0f, 20000.0f ,20000.0f));
	
  		
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix*translation*scaling;
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

  
       
}
 

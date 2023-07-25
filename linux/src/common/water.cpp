 #include"water.h"
 

water::water(
		const char * c,const char* map,const char* tex)
{
	obj=new objloader();

	name=c;
	
	programID = LoadShaders( "data/shaders/TransformVertexShader.vertexshader", "data/shaders/TextureFragmentShader.fragmentshader" );
	
	bool res=obj->load(map,vertices,uvs,normals);
	// Get a handle for our "MVP" uniform
	 MatrixID = glGetUniformLocation(programID, "MVP");

	// Get a handle for our buffers
	 vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	 vertexUVID = glGetAttribLocation(programID, "vertexUV");

	// Load the texture
	 Texture = obj->text.loadBMP_custom(tex);

	// Get a handle for our "myTextureSampler" uniform
	 TextureID  = glGetUniformLocation(programID, "myTextureSampler");


		 
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	
	
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	
}

water::~water()
{
	
	delete obj;
	
}

void water::update()
{

}

void water::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
{
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
	
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
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
			0,                  // attribute
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
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		


}

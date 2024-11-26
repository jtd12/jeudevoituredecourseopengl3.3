#include"carAI.hpp"

roueAI::roueAI(const char * filename)
{
		obj=new objloader();	
	//collision::modifyValueCollision(10.0f);
	programID = LoadShaders( "data/shaders/TransformVertexShader.vertexshader", "data/shaders/TextureFragmentShader.fragmentshader" );
	
	bool res=obj->load(filename,vertices,uvs,normals);
	// Get a handle for our "MVP" uniform
	 MatrixID = glGetUniformLocation(programID, "MVP");

	// Get a handle for our buffers
	 vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	 vertexUVID = glGetAttribLocation(programID, "vertexUV");

	// Load the texture
	 //Texture = tex->loadBMP_custom(textureMap);
	// Get a handle for our "myTextureSampler" uniform
	Texture = obj->text.loadBMP_custom("data/vehicule/Car_1_Diffuse_White.bmp");
	 TextureID  = glGetUniformLocation(programID, "myTextureSampler");


		 
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	
	
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	


}

roueAI::~roueAI()
{
	delete obj;
}
void roueAI::update()
{
	
}
void roueAI::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
{
glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
	glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(loc.x, loc.y, loc.z));
	glm::vec3 myRotationAxisZ( 0.0f, 0.0f, 0.5f);
	glm::vec3 myRotationAxisY( 0.0f, 0.5f, 0.0f);
	
	glm::mat4 rotMatrixY= glm::rotate( rot_roue.y, myRotationAxisY );
	glm::mat4 rotMatrixZ= glm::rotate( rot_roue.z, myRotationAxisZ );

	glm::mat4 scaling = glm::scale(glm::mat4(),glm::vec3( 2.0f, 2.0f ,2.0f));

		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix*translation*rotMatrixY*rotMatrixZ*scaling;

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

glm::vec3 roueAI::getRotation()
{
	return rot_roue;
}
		void roueAI::setRotationz(float m)
		{
			rot_roue.z+=m;
			
		}
	
			void roueAI::setRotationzegal(float m)
		{
			rot_roue.z=m;
		}
		
			void roueAI::setRotationy(float m)
		{
			rot_roue.y+=m;
			
		}
	
			void roueAI::setRotationyegal(float m)
		{
			rot_roue.y=m;
		}

void roueAI::setLocation(glm::vec3 l)
{
	loc=l;
}



vehiculeAI::vehiculeAI(const char* n,glm::vec3 location, float sprints,float looks,const char * filename,const char *tex)
{
		obj=new objloader();
		name=n;
		loc=location;
		sprintspeed=sprints;
		force=glm::vec3(0.0,-0.45f,0.0);
		setSpeed(speed);
		isground=iscollision=issprint=false;
		speed=rand() % 55 + 35;
		angle=0;
		maxSpeed=5.0f;
		acc=0.01f;
		dec=0.015f;
		turnSpeed=2.5f;
		s=0;
		a=glm::vec3(0.0,0.0,0);
		dec2=0.1f;
	    rr=0.0f;
	    rr2=0.0f;
		actif=false;
		points_=0;

	
	programID = LoadShaders( "data/shaders/TransformVertexShader.vertexshader", "data/shaders/TextureFragmentShader.fragmentshader" );
	
	bool res=obj->load(filename,vertices,uvs,normals);
	// Get a handle for our "MVP" uniform
	 MatrixID = glGetUniformLocation(programID, "MVP");

	// Get a handle for our buffers
	 vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	 vertexUVID = glGetAttribLocation(programID, "vertexUV");

	// Load the texture
	 //Texture = tex->loadBMP_custom(textureMap);
	// Get a handle for our "myTextureSampler" uniform
	 Texture = obj->text.loadBMP_custom(tex);

	// Get a handle for our "myTextureSampler" uniform
	 TextureID  = glGetUniformLocation(programID, "myTextureSampler");


		 
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	
	
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	
	for(int i=0;i<2;i++)
	 		wheel.push_back(new roueAI("data/vehicule/roue.obj"));
	 		
	for(int i=2;i<4;i++)
	 		wheel.push_back(new roueAI("data/vehicule/roue2.obj"));


}

vehiculeAI::~vehiculeAI()
{


}


void vehiculeAI::placeRoues(bool startCamera)
{
	wheel[0]->setLocation(glm::vec3(loc.x+cos(-a.y)*70,loc.y-20,loc.z+sin(-a.y)*70));
	wheel[1]->setLocation(glm::vec3(loc.x+cos(-a.y)*-55,loc.y-20,loc.z+sin(-a.y)*-55));
	wheel[2]->setLocation(glm::vec3(loc.x+cos(-a.y)*70,loc.y-20,loc.z+sin(-a.y)*70));
	wheel[3]->setLocation(glm::vec3(loc.x+cos(-a.y)*-55,loc.y-20,loc.z+sin(-a.y)*-55));
	
	if(startCamera==false)
	{
	for (int i=0;i<4;i++)
	 wheel[i]->setRotationyegal(a.y);
	 
	for (int i=0;i<4;i++)
	  wheel[i]->setRotationz(.05f);
	  
	  
		for(int i=0;i<wheel.size();i++)
	 wheel[i]->update();
	}
}

void vehiculeAI::resetPoints()
{
	points_=0;

}

void vehiculeAI::setGravity()
{
	loc.y-=0.2f;
	collisionCarAndGround();
}

void vehiculeAI::setRotation(glm::vec3 rot)
{
	a=rot;
}

void vehiculeAI::update()
{


	move();
	findTarget();


}

int vehiculeAI::getPoints()
{
	return points_;
}

void vehiculeAI::setPoints(int p)
{
	points_-=p;
	if(points_<0)
	{
		points_=0;
	}
}

void vehiculeAI::checkPoints(glm::vec3 loc,glm::vec3 loc2)
{
	float dist=sqrt(loc2.x-loc.x)*(loc2.x-loc.x)+(loc2.y-loc.y)*(loc2.y-loc.y)+(loc2.z-loc.z)*(loc2.z-loc.z);
	
	if(dist<5000)
	{
		points_+=5;
	}
}


void vehiculeAI::collisionCarAndGround()
{
	if(loc.x>-2500 && loc.x<9000 && loc.z>1000 && loc.z<1300)
	{
		loc.y=70;
	}
	else
	{
		loc.y=110;
	}
}

		void vehiculeAI::setPosition(glm::vec3 pos)
		{
		
			setLocation(pos);
		}
	
		glm::vec3 vehiculeAI::getLocation()
{
	return loc;
}
glm::vec3 vehiculeAI::getRotation()
{
	return  glm::vec3(a.x,a.y,a.z);
}

void vehiculeAI::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
{

	glUseProgram(programID);
glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(loc.x, loc.y, loc.z));
glm::vec3 myRotationAxis( 0.0f, 0.5f, 0.0f);
glm::mat4 rotMatrix= glm::rotate( a.y, myRotationAxis );
glm::mat4 scaling = glm::scale(glm::mat4(),glm::vec3( 2.0f, 2.0f ,2.0f));
		// Compute the MVP matrix from keyboard and mouse input
	
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix*translation*rotMatrix*scaling;

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
		
		
		
		
		for(int i=0;i<wheel.size();i++)
		{
			wheel[i]->draw(ProjectionMatrix,ViewMatrix,ModelMatrix);
		}
	
}




void vehiculeAI::setLocation(glm::vec3 vec)
{
	loc=glm::vec3(vec);
}
   void vehiculeAI::move()
   {
    loc.x += cos(-a.y) * (speed/20);
    loc.z += sin(-a.y) * (speed/20);
  
   }
   
   void vehiculeAI::setLocationInc(glm::vec3 l)
   {
   	loc+=l;
   }
   
   void vehiculeAI::setLocationIncX(float y)
{
	loc.x+=y;
}

void vehiculeAI::setLocationIncZ(float y)
{
	loc.z+=y;
}

  
 float vehiculeAI::getSpeed()
 {
 	return speed;
 }
void vehiculeAI::setSpeed(float s)
{
	speed=s;
}

float vehiculeAI::getMaxSpeed()
{
	return maxSpeed;
}


		 void vehiculeAI::setActif(bool b)
		 {
		 	actif=b;
		 }
		 	 bool vehiculeAI::getActif()
		 {
		 	return actif;
		 }


void vehiculeAI::findTarget()
  {
    float tx=points[nn][0];
    float ty=points[nn][1];
    float beta = a.y-atan2(-ty+loc.z,tx-loc.x);
    if (sin(beta)<0) a.y+=0.005*speed/20; else a.y-=0.005*speed/20;
    if ((loc.x-tx)*(loc.x-tx)+(loc.z-ty)*(loc.z-ty)<40*40) nn=(nn+1)%num;
   }

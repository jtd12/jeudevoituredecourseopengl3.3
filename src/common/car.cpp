#include"car.h"

bbBox::bbBox(const char * filename,glm::vec3 l)
{
	loc=l;
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
	Texture = obj->text.loadBMP_custom("data/textures/uvtemplate.bmp");
	 TextureID  = glGetUniformLocation(programID, "myTextureSampler");


		 
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	
	
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	
}
bbBox::~bbBox()
{
		delete obj;
}

void bbBox::setParent(glm::vec3 parent,float rotationY,int offset)
{
	loc=glm::vec3(parent.x+cos(-rotationY)*offset,parent.y+2,parent.z+sin(-rotationY)*offset);
	rot.y=rotationY;
}

glm::vec3 bbBox::getLocation()
{
	return loc;
}
void bbBox::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
{
	glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
   glm::mat4  translation= glm::translate(ModelMatrix, glm::vec3(loc.x, loc.y, loc.z));
	glm::vec3 myRotationAxis( 0.0f, 0.5f, 0.0f);
  glm::mat4 rotMatrix= glm::rotate( rot.y, myRotationAxis );
  glm::mat4 scaling = glm::scale(ModelMatrix,glm::vec3( 2.0f, 2.0f ,2.0f));

		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix*translation*rotMatrix*scaling;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//	glUniformMatrix4fv(glGetUniformLocationpshaderCouleur.getProgramID() "projection"), 1, GL_FALSE, value_ptr(projection));
//	glUniformMatrix4fv(glGetUniformLocation(shaderCouleur.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


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

roue::roue(const char * filename)
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

roue::~roue()
{
	delete obj;
}
void roue::update()
{
	
}
void roue::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
{

glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
   glm::mat4  translation= glm::translate(ModelMatrix, glm::vec3(loc.x, loc.y, loc.z));
	glm::vec3 myRotationAxisZ( 0.0f, 0.0f, 0.5f);
	glm::vec3 myRotationAxisY( 0.0f, 0.5f, 0.0f);
	
	glm::mat4 rotMatrixY= glm::rotate( rot_roue.y, myRotationAxisY );
	glm::mat4 rotMatrixZ= glm::rotate( rot_roue.z, myRotationAxisZ );

  glm::mat4 scaling = glm::scale(ModelMatrix,glm::vec3( 2.0f, 2.0f ,2.0f));

		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix*translation*rotMatrixY*rotMatrixZ*scaling;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//	glUniformMatrix4fv(glGetUniformLocationpshaderCouleur.getProgramID() "projection"), 1, GL_FALSE, value_ptr(projection));
//	glUniformMatrix4fv(glGetUniformLocation(shaderCouleur.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


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

glm::vec3 roue::getRotation()
{
	return rot_roue;
}
		void roue::setRotationz(float m)
		{
			rot_roue.z+=m;
			
		}
	
			void roue::setRotationzegal(float m)
		{
			rot_roue.z=m;
		}
		
			void roue::setRotationy(float m)
		{
			rot_roue.y+=m;
			
		}
	
			void roue::setRotationyegal(float m)
		{
			rot_roue.y=m;
		}

void roue::setLocation(glm::vec3 l)
{
	loc=l;
}



vehicule::vehicule(const char* n,glm::vec3 location, float sprints,float normales,float looks)
{
		name=n;
		sprintspeed=sprints;
		normalspeed=normales;
		force=glm::vec3(0.0,-0.45f,0.0);
		loc=location;
		setSpeed(normalspeed);
		isground=iscollision=issprint=false;
		speed=normales;
		angle=0;
		maxSpeed=(rand() % 35 + 55)/10;
		acc=0.02f;
		dec=0.0005f;
		turnSpeed=4.5f/100;
		up=0;
		down=0;
		left=0;
		right=0;
		s=0;
		a=glm::vec3(0.0,0.0,0);
		a_touch=0;
		dec2=0.008f;
	    rr=0.0f;
	    rr2=0.0f;
	    points=0;
	obj=new objloader();	
	
	part.push_back(new particule((int)speed*10));
	part.push_back(new particule((int)speed*10));

	actif=true;
	bb.push_back( new bbBox("data/decor/cube.obj",glm::vec3(0,0,0)));
	bb.push_back( new bbBox("data/decor/cube.obj",glm::vec3(0,0,0)));
	
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-500,50,1000)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(6000,50,1000)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-500,50,1300)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(4500,50,1300)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(4500,50,1300)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(4500,50,1700)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(6000,50,1000)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(6000,50,2000)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(6000,50,2200)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9800,50,2200)));
	
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(4500,50,1700)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9200,50,1700)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9800,50,2200)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9800,50,-100)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9200,50,1700)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9200,50,200)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9800,50,-300)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2500,50,-300)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-9200,50,100)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2900,50,100)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2900,50,100)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2900,50,1600)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2500,50,-300)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2500,50,1100)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2500,50,1100)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-500,50,1100)));
	
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-2900,50,1300)));
	collidersDetection.push_back(new bbBox("data/decor/cube2.obj",glm::vec3(-500,50,1300)));
	//part.push_back(new particule((int)speed));
	//part.push_back(new particule((int)speed));


	programID = LoadShaders( "data/shaders/TransformVertexShader.vertexshader", "data/shaders/TextureFragmentShader.fragmentshader" );
	
	bool res=obj->load("data/vehicule/vehicule0.obj",vertices,uvs,normals);
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




 for(int i=0;i<2;i++)
	 		wheel.push_back(new roue("data/vehicule/roue.obj"));
for(int i=2;i<4;i++)
	 		wheel.push_back(new roue("data/vehicule/roue2.obj"));

}

vehicule::~vehicule()
{
	delete obj;
	for(int i=0;i<collidersDetection.size();i++)
	 collidersDetection[i];
	for(int i=0;i<bb.size();i++)
	  delete bb[i];
for(int i=0;i<part.size();i++)
	delete part[i];
	for(int i=0;i<wheel.size();i++)
	 delete wheel[i];

}


void vehicule::placementRoues()
{
	wheel[0]->setLocation(glm::vec3(loc.x+cos(-a.y)*70,loc.y-20,loc.z+sin(-a.y)*70));
	wheel[1]->setLocation(glm::vec3(loc.x+cos(-a.y)*-55,loc.y-20,loc.z+sin(-a.y)*-55));
	wheel[2]->setLocation(glm::vec3(loc.x+cos(-a.y)*70,loc.y-20,loc.z+sin(-a.y)*70));
	wheel[3]->setLocation(glm::vec3(loc.x+cos(-a.y)*-55,loc.y-20,loc.z+sin(-a.y)*-55));
}

void vehicule::setGravity()
{
	loc.y-=0.2f;
	collisionCarAndGround();
}

void vehicule::update()
{
	
	bb[0]->setParent(getLocation(),getRotation().y,150);
	bb[1]->setParent(getLocation(),getRotation().y,-150);


	 	for (int i=0;i<4;i++)
	 wheel[i]->setRotationyegal(a.y);
	 

	
	for(int i=0;i<wheel.size();i++)
	 wheel[i]->update();


}

void vehicule::checkPoints(glm::vec3 loc,glm::vec3 loc2)
{
	float dist=sqrt(loc2.x-loc.x)*(loc2.x-loc.x)+(loc2.y-loc.y)*(loc2.y-loc.y)+(loc2.z-loc.z)*(loc2.z-loc.z);
	
	if(dist<5000)
	{
		points+=5;
	}
}

void vehicule::updateControl()
 {
 	control();
 }


int vehicule::getPoints()
{
	return points;
}

void vehicule::setPoints(int p)
{
	points-=p;
	if(points<0)
	{
		points=0;
	}
}

void vehicule::resetPoints()
{
	points=0;

}

void vehicule::collisionCarAndGround()
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

	

		void vehicule::setPosition(glm::vec3 pos)
		{
		
			setLocation(pos);
		}
	
		glm::vec3 vehicule::getLocation()
{
	return loc;
}
glm::vec3 vehicule::getRotation()
{
	return  glm::vec3(a.x,a.y,a.z);
}

void vehicule::setRotation(glm::vec3 rot)
{
	a=rot;
	angle=0.0f;
}

void vehicule::setLocationIncX(float y)
{
	loc.x+=y;
}

void vehicule::setLocationIncZ(float y)
{
	loc.z+=y;
}


void vehicule::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
{

	glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
   glm::mat4  translation= glm::translate(ModelMatrix, glm::vec3(loc.x, loc.y, loc.z));
	glm::vec3 myRotationAxis( 0.0f, 0.5f, 0.0f);
  glm::mat4 rotMatrix= glm::rotate( a.y, myRotationAxis );
  glm::mat4 scaling = glm::scale(ModelMatrix,glm::vec3( 2.0f, 2.0f ,2.0f));

		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix*translation*rotMatrix*scaling;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//	glUniformMatrix4fv(glGetUniformLocationpshaderCouleur.getProgramID() "projection"), 1, GL_FALSE, value_ptr(projection));
//	glUniformMatrix4fv(glGetUniformLocation(shaderCouleur.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


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
	


		part[0]->draw(-50,(int)speed*10,ProjectionMatrix,ViewMatrix,ModelMatrix,getLocation()+glm::vec3(-500,0,0));
		part[1]->draw(50,(int)speed*10,ProjectionMatrix,ViewMatrix,ModelMatrix,getLocation()+glm::vec3(-500,0,0));
		
		for(int i=0;i<bb.size();i++)
		 bb[i]->draw(ProjectionMatrix,ViewMatrix,ModelMatrix);
		 
		for(int i=0;i<collidersDetection.size();i++)
	 			collidersDetection[i]->draw(ProjectionMatrix,ViewMatrix,ModelMatrix);
	
	

}

void vehicule::setLocation(glm::vec3 vec)
{
	loc=glm::vec3(vec);
}
   void vehicule::move()
   {
    loc.x += cos(-a.y) * s;
    loc.z += sin(-a.y) * s;
  
   }
   

   void vehicule::inputSpecial(char key,int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		 up=true;
	
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_DOWN:

		 down=true;	
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_RIGHT:
	
		 right=true;
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_LEFT:
		 	
		left=true;
		glutPostRedisplay();
	
	}
}
   void vehicule::inputSpecialUP(char key,int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		 up=false;
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_DOWN:
		 down=false;
		 glutPostRedisplay();	
		 break;
		 case GLUT_KEY_RIGHT:
		 right=false;
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_LEFT:
		left=false;
		glutPostRedisplay();
		break;
	
	}
}
void vehicule::keyboard(char key, int x, int y)
{
	switch(key)
	{
	
		case  SPACEBAR:
		a_touch=true;
		glutPostRedisplay();
		break;
	}
}
void vehicule::keyboardUP(char key, int x, int y)
{
switch(key)
{

	case  SPACEBAR:
		a_touch=false;
		glutPostRedisplay();
		break;
	}
	}
	
void vehicule::control()
{
	/*
	
			if(state[SDLK_m])
			{
					clavierAct++;
				
				}
				*/
				
	
		
		
			if(a_touch==1)
			{
				
			}
			
			
				if(up==1)
				{
						for(int i=0;i<wheel.size();i++)
				{
				
					wheel[i]->setRotationz(1.5f);
				}
			}
					if(down==1)
				{
						for(int i=0;i<wheel.size();i++)
				{
				
					wheel[i]->setRotationz(-1.5f);
				}
			}
			
				if(right==1)
				{
				
					wheel[0]->setRotationy(-0.5f);
					wheel[2]->setRotationy(-0.5f);
					
				
					
				
			}
			
				if(left==1)
				{
			
					wheel[0]->setRotationy(0.5f);
					wheel[2]->setRotationy(0.5f);
					
				
						
				}
				
					if(right==0 && left==0)
				{
				
					wheel[0]->setRotationyegal(a.y);
					wheel[2]->setRotationyegal(a.y);
				
				}
			
					
					
	if(up==1 && speed<maxSpeed)
			{
			
				if(speed<0)
				{
					
					speed+=dec;
			 }
				else
				{
					speed+=acc;
				}
			
	
				
			}
			if(down==1 && speed>-maxSpeed)
			{
				 
				if(speed>0)
				{
				
					speed-=dec;
				}
				else
				{
					speed-=acc;
				}
				
	
			}
			
			if(up==0 && down==0)
			{
				if(speed-dec>0)
				{
					speed-=dec;
				}
				else if(speed+dec<0)
				{
					speed+=dec;
				}
				else
				{
					speed=0;
				}
			}
			
				if(a_touch==1)
			{
				
				
				if(speed-dec2>0)
				{
					speed-=dec2;
				}
				else if(speed+dec2<0)
				{
					speed+=dec2;
				}
				else
				{
					speed=0;
				}
			}

		if(right)
	{
		angle-=turnSpeed*(speed/maxSpeed);
	}
		if(left)
	{
		angle+=turnSpeed*(speed/maxSpeed);
	}
		s=speed;
		a.y=angle;
		
		//angle=turnSpeed;
		

		move();
	
		
	
}

void vehicule::limitSpeed(float s)
{
	speed=s;
	}	
		
int vehicule::getUP()
{
	return up;
	
}
int vehicule::getDOWN()
{
	return down;
	
}
int vehicule::getRIGHT()
{
	return right;
	
}
int vehicule::getLEFT()
{
	return left;
	
}
int vehicule::getA()
{
	return a_touch;
}
void vehicule::setA(int A)
{
	a_touch=A;
}

void vehicule::setUP(int num)
{
	up=num;
}
void vehicule::setDOWN(int num)
{
	down=num;
}
void vehicule::setRIGHT(int num)
{
	right=num;
}
void vehicule::setLEFT(int num)
{
	left=num;
}


 float vehicule::getSpeed()
 {
 	return speed;
 }
void vehicule::setSpeed(float s)
{
	speed=s;
}

float vehicule::getMaxSpeed()
{
	return maxSpeed;
}


		 void vehicule::setActif(bool b)
		 {
		 	actif=b;
		 }
		 	 bool vehicule::getActif()
		 {
		 	return actif;
		 }
		 



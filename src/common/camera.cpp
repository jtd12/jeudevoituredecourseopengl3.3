

#include "camera.hpp"


bbBoxCam::bbBoxCam(const char * filename,glm::vec3 l)
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
bbBoxCam::~bbBoxCam()
{
		delete obj;
}

void bbBoxCam::setInFrontOfCamera(const glm::vec3& cameraPosition, const glm::vec3& cameraOrientation, float distanceFromCamera) {
    // Placer le cube à une distance fixe devant la caméra
    loc = cameraPosition + glm::normalize(cameraOrientation) * distanceFromCamera;
    // Garder la même orientation que la caméra
    rot.y = atan2(cameraOrientation.z, cameraOrientation.x); // Met à jour l'angle Y du cube pour correspondre à la caméra
}


glm::vec3 bbBoxCam::getLocation()
{
	return loc;
}
void bbBoxCam::draw(glm::mat4 ProjectionMatrix,glm::mat4 ViewMatrix,glm::mat4 ModelMatrix)
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

glm::mat4 camera:: getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 camera:: getProjectionMatrix(){
	return ProjectionMatrix;
}

camera::camera() : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(0, 0, 1), m_deplacementLateral(), position(), target()
{

}

// Initial position : on +Z
 


camera::camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical) : m_phi(-35.26), m_theta(-135), m_orientation(), m_axeVertical(axeVertical), 
                                                                                  m_deplacementLateral(), position(position), target(pointCible)
{
 	speed=0.5f;
 	bb.push_back( new bbBoxCam("data/decor/cube.obj",glm::vec3(0,0,0)));

	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-500,50,1000)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(6000,50,1000)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-500,50,1300)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(4500,50,1300)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(4500,50,1300)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(4500,50,1700)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(6000,50,1000)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(6000,50,2000)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(6000,50,2200)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9800,50,2200)));
	
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(4500,50,1700)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9200,50,1700)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9800,50,2200)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9800,50,-100)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9200,50,1700)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9200,50,200)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9800,50,-300)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2500,50,-300)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-9200,50,100)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2900,50,100)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2900,50,100)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2900,50,1600)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2500,50,-300)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2500,50,1100)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2500,50,1100)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-500,50,1100)));
	
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-2900,50,1300)));
	collidersDetection.push_back(new bbBoxCam("data/decor/cube2.obj",glm::vec3(-500,50,1300)));
}

camera::~camera()
{

}

void camera::orienter(int xRel, int yRel)
{
	MidX=480;
	MidY=270;

    // Modification des angles

    m_phi += yRel*0.05f;
    m_theta += xRel*0.05f;
    
      if(m_phi > 89.0)
        m_phi = 89.0;

    else if(m_phi < -89.0)
        m_phi = -89.0;
        
    
    float phiRadian = m_phi * M_PI / 180;
	float thetaRadian = m_theta * M_PI / 180;

	if(m_axeVertical.x == 1.0)
	{
	    // Calcul des coordonnées sphériques
	
	    m_orientation.x = sin(phiRadian);
	    m_orientation.y = cos(phiRadian) * cos(thetaRadian);
	    m_orientation.z = cos(phiRadian) * sin(thetaRadian);
	}
	
	
	// Si c'est l'axe Y
	
	else if(m_axeVertical.y == 1.0)
	{
	    // Calcul des coordonnées sphériques
	
	    m_orientation.x = cos(phiRadian) * sin(thetaRadian);
	    m_orientation.y = sin(phiRadian);
	    m_orientation.z = cos(phiRadian) * cos(thetaRadian);
	}
	
	
	// Sinon c'est l'axe Z
	
	else
	{
	    // Calcul des coordonnées sphériques
	
	    m_orientation.x = cos(phiRadian) * cos(thetaRadian);
	    m_orientation.y = cos(phiRadian) * sin(thetaRadian);
	    m_orientation.z = sin(phiRadian);
	}
	
	m_deplacementLateral = cross(m_axeVertical, m_orientation);
    m_deplacementLateral = normalize(m_deplacementLateral);


    // Calcul du point ciblé pour OpenGL

    target = position + m_orientation;
}

void camera::tourner(int x, int y)
{
		if(mi)
	{
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		orienter(MidX-x, MidY-y);
		glutWarpPointer(MidX,MidY);
	}
	else
	{
	
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
}

void camera::controlMouse(int button, int state, int x, int y)
{

	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
	{
	mi=true;
	}
	else
	{

	mi=false;
	
	}
	
}


void camera::inputSpecial(char key,int x, int y)
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
   void camera::inputSpecialUP(char key,int x, int y)
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

void camera::deplacer()
{
	

	
	if(up)
	{
	  position = position + m_orientation * speed;
	  target = position + m_orientation;
	}
	if(down)
	{
	position = position - m_orientation * speed;
    target = position + m_orientation;
	}
	if(left)
	{
	position = position + m_deplacementLateral * speed;
    target = position + m_orientation;
	}
	if(right)
	 {
    position = position - m_deplacementLateral *speed;
    target = position + m_orientation;
	 }
	 	
}

float camera::getSpeed()
{
	return speed;
}

void camera::setSpeed(float s)
{
	speed=s;
}


void camera::setPosition(glm::vec3 loc)
{
	position=loc;
}
void camera::setTarget(glm::vec3 loc)
{
	target=loc;
}
glm::vec3 camera:: getLocation()
{
	return position;
}
glm::vec3 camera::getRotation()
{
	return target;
}


void camera::collisionCameraAndGround()
{
	if(getLocation().x>-2500 && getLocation().x<9000 && getLocation().z>1000 && getLocation().z<1300 && getLocation().y<70)
	{
		setPosition(glm::vec3(getLocation().x,70,getLocation().z));
	}
	else
	{
	   if(getLocation().y<110)
		setPosition(glm::vec3(getLocation().x,110,getLocation().z));
	}
}


void camera::computeMatricesFromInputs(bool startfreecamera){

bb[0]->setInFrontOfCamera(getLocation(), m_orientation, 100.0f);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;
	// glfwGetTime is called only once, the first time this function is called
//	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	//double currentTime = glfwGetTime();
	//float deltaTime = float(currentTime - lastTime);

	// Get mouse position

	// Up vector


	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45Â° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 250000.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								target, // and looks here : at the same position, plus "direction"
								m_axeVertical                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
						   
		if(startfreecamera)	
		{			   
		for(int i=0;i<bb.size();i++)
	     bb[i]->draw(ProjectionMatrix,ViewMatrix,glm::mat4(1.0));
	    }
		 
	    for(int i=0;i<collidersDetection.size();i++)
	 	 collidersDetection[i]->draw(ProjectionMatrix,ViewMatrix,glm::mat4(1.0));
						   


	// For the next frame, the "last time" will be "now"

}

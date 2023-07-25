

#include "camera.hpp"



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
	  position = position + m_orientation * 0.5f;
	  target = position + m_orientation;
	}
	if(down)
	{
	position = position - m_orientation * 0.5f;
    target = position + m_orientation;
	}
	if(left)
	{
	position = position + m_deplacementLateral * 0.5f;
    target = position + m_orientation;
	}
	if(right)
	 {
    position = position - m_deplacementLateral * 0.5f;
    target = position + m_orientation;
	 }
	 	
}


void camera::setPosition(glm::vec3 loc)
{
	position=loc;
}
void camera::setTarget(glm::vec3 loc)
{
	target=loc;
}


void camera::computeMatricesFromInputs(){


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

	// For the next frame, the "last time" will be "now"

}

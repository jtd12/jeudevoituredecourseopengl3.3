#include"playerCam.h"

playerCam::playerCam(const char * n,glm::vec3 location,float sprints,float normals,float looks)
{
	name=n;
	sprintspeed=sprints;
	normalspeed=normals;
	//force.change(0,-0.05f,0);

	//cam.setSpeed(normalspeed,looks);
	isground=iscollision=issprint=false;
	energy=20;
	bulletDelay=0.1f;
	rot=0.0f;
	rot2=0.0f;
	points=0;
	energy=10;
	health=100;
	curWep=0;
	headPosition=0;
	dir=glm::vec3(0,0,0);
	headUp=false;
	
 
}
playerCam::~playerCam()
{


	
}


void playerCam::setSprint()
{
	if(energy>30.0)
	{
		issprint=true;
		//cam.setSpeed(sprintspeed,cam.getMousevel());
	}
	else
	{
		issprint=false;
	}
}
void playerCam::stopSprint()
{
	issprint=false;
	//cam.setSpeed(normalspeed,cam.getMousevel());
}

void playerCam::update(std::vector<collisionplane>& collplane)
{
	
		if(direction.y>=force.y)
			direction+=force;
		//	glm::vec3 newPos(cam.getLocation());
	 	//	newPos+=direction;
	 		/*	glm::vec3 oldpos(newPos);
	 		for(int i=0;i<collplane.size();i++)
				collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r);
	 					if(oldpos.y<newPos.y)
	 				{
					 isground=true;
				}
				else
				{
					isground=false;
				}
	 		setPosition(newPos);
				 */
}

void playerCam::setPosition(glm::vec3 pos)
{
	
	//cam.setLocation(pos);
}

		glm::vec3 playerCam::getLocation()
{
	return loc;
}
	 	void playerCam::setLocation(glm::vec3 newLoc)
	 	{
	 
	 		//cam.setLocation2(newLoc);
		 }
		 void playerCam::setLocation2(glm::vec3 newLoc)
		 {
		  
		 	//cam.setLocation(newLoc);
		 }
		 
		
		


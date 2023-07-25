#include"gameSetup.hpp"

setup::setup()
{
	
//int randNumber = rand() % 50 + 10;


levels.push_back(new decor("name","data/decor/decor.obj","data/decor/mur.bmp"));
levels.push_back(new decor("name","data/decor/road.obj","data/decor/road07.bmp"));
levels.push_back(new decor("name","data/decor/decor2.obj","data/decor/Grass_01_c.bmp"));
levels.push_back(new decor("name","data/decor/decor3.obj","data/decor/mur.bmp"));


for(int i=0;i<10;i++)
	allCars.push_back(new allVehicule());
	

allCars[0]->car=new vehicule("voiture",glm::vec3(2600,200,1200),0.02,0.0,0.2);
allCars[1]->carAI.push_back(new vehiculeAI("voitureAI",glm::vec3(-450,100,1200),0.02,0.0,"data/vehicule/vehicule0.obj","data/vehicule/Car_1_Diffuse_White.bmp"));
allCars[2]->carAI.push_back(new vehiculeAI("voitureAI2",glm::vec3(-850,100,1200),0.02,0.0,"data/vehicule/vehicule1.obj","data/vehicule/Car_2_Diffuse_White.bmp"));
allCars[3]->carAI.push_back(new vehiculeAI("voitureAI3",glm::vec3(-100,100,1200),0.02,0.0,"data/vehicule/vehicule2.obj","data/vehicule/Car_3_Diffuse_White.bmp"));
allCars[4]->carAI.push_back(new vehiculeAI("voitureAI4",glm::vec3(550,100,1200),0.02,0.0,"data/vehicule/vehicule3.obj","data/vehicule/Car_4_Diffuse_White.bmp"));
allCars[5]->carAI.push_back(new vehiculeAI("voitureAI5",glm::vec3(1200,100,1200),0.02,0.0,"data/vehicule/vehicule4.obj","data/vehicule/Car_6_Diffuse_White.bmp"));
allCars[6]->carAI.push_back(new vehiculeAI("voitureAI6",glm::vec3(1500,100,1200),0.02,0.0,"data/vehicule/vehicule5.obj","data/vehicule/Car_7_Diffuse_White.bmp"));
allCars[7]->carAI.push_back(new vehiculeAI("voitureAI6",glm::vec3(1250,100,1200),0.02,0.0,"data/vehicule/vehicule5.obj","data/vehicule/Car_7_Diffuse_White.bmp"));
allCars[8]->carAI.push_back(new vehiculeAI("voitureAI6",glm::vec3(1400,100,1200),0.02,0.0,"data/vehicule/vehicule4.obj","data/vehicule/Car_6_Diffuse_White.bmp"));
ocean=new water("ocean","data/water/ocean.obj","data/water/water_man.bmp");
engrenage=new water("ocean","data/engrenage/engrenage.obj","data/decor/mur.bmp");
//levels.push_back(new decor("name",map3_2,mapcp4,mapsp));
//ressort=new water(glm::vec3(0.0,0,0.0),0,"ressort","data/engrenage/ressort/ressort_element");
//tuyeau=new water(glm::vec3(0.0,0,0.0),0,"tuyeau","data/engrenage/tuyeau/tuyeau_element");


audio=new sound;
sound1=audio->loadSound("data/audio/vehicule.wav");

PlaySound("data/audio/background.wav", NULL, SND_LOOP |SND_ASYNC);

cam=new camera();
cam=new camera(vec3(5500, 3000, 300), vec3(0, 0, 0), vec3(0, 1, 0));
sky=new skybox();
startFreeCamera=true;
startcameraFollow=false;




}



setup::~setup()
{

for(int i=0;i<levels.size();i++)
 delete levels[i];
 
 for(int i=0;i<allCars.size();i++)
  delete allCars[i];
  
delete ocean;
delete sky;
delete engrenage;
delete audio;
delete cam;
}

void setup::mouseMove(int mx,int my)
{
	if(startFreeCamera)
	  cam->tourner(mx,my);
}

void setup:: mouseState(int button, int state, int x, int y)
{
cam->controlMouse(button,  state,  x, y);
}

void setup::keyboard(unsigned char key, int x, int y)
{
 if(startcameraFollow)
 {
	for(int w=0;w<1;w++)
	   allCars[w]->car->keyboard(key,x,y);
 }

	   
	   switch(key)
	   {
	   	case 'm':
	   		startFreeCamera=true;
	   		startcameraFollow=false;
	   		break;
	   		
	   	case 'v':
	   		startFreeCamera=false;
	   		startcameraFollow=true;
	   		break;
	   		
	   }
}

void setup::passiveKeyboard(unsigned char key, int x, int y)
 {
  if(startcameraFollow)
 {
	for(int w=0;w<1;w++)
	   allCars[w]->car->keyboardUP(key,x,y);
	}

 }
 
void setup::specialKey(int key, int x, int y)
{
	 if(startcameraFollow)
 {
	for(int w=0;w<1;w++)
	   allCars[w]->car->inputSpecial(key,x,y);
}

	   
	if(startFreeCamera)
	 cam->inputSpecial(key,x,y);
	   
}

void setup::controlSpecialPassiveKeyboard(int key,int x, int y)
{
	 if(startcameraFollow)
 {
	
	for(int w=0;w<1;w++)
	   allCars[w]->car->inputSpecialUP(key,x,y);
}

	 if(startFreeCamera)  
	  cam->inputSpecialUP(key,x,y);
	
}

void setup::gestionCam()
{	
for(int w=0;w<1;w++)	
{
  cam->setPosition(glm::vec3(allCars[w]->car->getLocation().x+cos(-allCars[w]->car->getRotation().y)*-500,200,allCars[w]->car->getLocation().z+sin(-allCars[w]->car->getRotation().y)*-500));
  cam->setTarget(glm::vec3(allCars[w]->car->getLocation().x,10,allCars[w]->car->getLocation().z));

}
}


void setup::updateCamera()
{
	cam->deplacer();
}

 

void setup::update()
{
	
	if(startcameraFollow)
	  gestionCam();

	  if(startFreeCamera)
		updateCamera();
		
	audio->setListener(allCars[0]->car->getLocation(),allCars[0]->car->getLocation());
	audio->playSound(sound1,allCars[0]->car->getLocation(),(allCars[0]->car->getSpeed()/allCars[0]->car->getMaxSpeed())+1);

 	if(startcameraFollow)
 	{
 	for(int w=0;w<1;w++)
		   allCars[w]->car->updateControl();	
 	}
	 
 //sky->update();
	 for(int w=0;w<1;w++)
		   allCars[w]->car->update();
	
	 for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
		  allCars[w]->carAI[i]->update();
		  
	  collisionCarAI();
	  for(int z=0;z<1;z++)
	   for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
	   collisionCar(allCars[z]->car->getLocation(),allCars[w]->carAI[i]->getLocation());
	   
	  collisionCarAndWall();

	  
	
 
 //ocean->update();
	
	
//	printf("v1: %.2f\n",allCars[1]->carAI[0]->getSpeed());
//	printf("v2: %.2f\n",allCars[2]->carAI[0]->getSpeed());
	
	/*
	if(player->cam.getActif()==false && car->getActif())
	{
	 player->cam.setLocation(car->getLocation());
	 car->control();
	
	}*/


	
}



void setup::collisionCarAndWall()
{
	
   for(int w=0;w<1;w++)
    if(linePointDetection(-1100,1000,6000,1000,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(15.5f);
	}
	
   for(int w=0;w<1;w++)
    if(linePointDetection(-1100,1300,4500,1300,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(-15.5f);
	}
	
	
	
	for(int w=0;w<1;w++)
    if(linePointDetection(6000,1000,6000,2300,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncX(-15.5f);
	}
	
	for(int w=0;w<1;w++)
    if(linePointDetection(4800,1300,4800,1500,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncX(15.5f);
	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(6000,2100,-9800,2100,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(-15.5f);
	}
	
		for(int w=0;w<1;w++)
    if(linePointDetection(4800,1700,-9200,1700,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(15.5f);
	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(-9800,3000,-9800,-300,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncX(15.5f);
	}
	
		for(int w=0;w<1;w++)
    if(linePointDetection(-9300,1700,-9300,200,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncX(-15.5f);
	}
	
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(-9800,-200,-2500,-200,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(15.5f);
	}
	
		for(int w=0;w<1;w++)
    if(linePointDetection(-9300,0,-2900,0,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(-15.5f);
	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(-2500,-800,-2500,1200,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncX(-15.5f);
	}
	
			for(int w=0;w<1;w++)
    if(linePointDetection(-2800,0,-2800,1600,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncX(15.5f);
	}
	
	
	
			for(int w=0;w<1;w++)
    if(linePointDetection(-2500,1100,-800,1100,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(15.5f);
	}
	
		for(int w=0;w<1;w++)
    if(linePointDetection(-2800,1400,-800,1400,allCars[w]->car->getLocation().x,allCars[w]->car->getLocation().z))
    {
    	allCars[w]->car->setLocationIncZ(-15.5f);
	}
}


void setup::collisionCar(glm::vec3 pos,glm::vec3 pos2)
{
	
	float dist=sqrt((pos.x-pos2.x)*(pos.x-pos2.x) + (pos.z-pos2.z)*(pos.z-pos2.z));
	
		for(int w=0;w<1;w++)
		 {
		 	if(dist<50)
		 	 {
		 	 
		 	 	allCars[w]->car->setLocationIncX(-200.0f);
			  }
		 }
}

void setup::collisionCarAI()
{

	for (int i=1;i<allCars.size();i++)
    for(int j=1;j<allCars.size();j++)
     for(int a=0;a<allCars[i]->carAI.size();a++)
       for(int b=0;b<allCars[j]->carAI.size();b++)
  {
  
        int dx=0, dy=0;
        while (dx*dx+dy*dy<4*R*R)
         {
           allCars[i]->carAI[a]->setLocationInc(glm::vec3(dx/10,0,dy/10));
           allCars[j]->carAI[b]->setLocationInc(glm::vec3(-dx/10,0,-dy/10));
           dx = allCars[i]->carAI[a]->getLocation().x-allCars[j]->carAI[b]->getLocation().x;
           dy = allCars[i]->carAI[a]->getLocation().z-allCars[j]->carAI[b]->getLocation().z;
           if (!dx && !dy) break;
         }
    }

	
}

inline float dist(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

bool setup:: linePointDetection(float x1, float y1, float x2, float y2, float px, float py) {

  // get distance from the point to the two ends of the line
  float distX = px - x1;
  float distY = py - y1;

  float d1 = dist(px,py, x1,y1);
  float d2 = dist(px,py, x2,y2);

  // get the length of the line
  float lineLen = dist(x1,y1, x2,y2);

  // since floats are so minutely accurate, add
  // a little buffer zone that will give collision
  float buffer = 0.1;    // higher # = less accurate

  // if the two distances are equal to the line's
  // length, the point is on the line!
  // note we use the buffer here to give a range,
  // rather than one #
  if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
    return true;
  }
  return false;
}


void setup::draw()
{
	
	cam->computeMatricesFromInputs();
	
	for(int i=0;i<levels.size();i++)
	 levels[i]->draw(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0));
	 
	 for(int w=0;w<1;w++)
	   allCars[w]->car->draw(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0));
	 
	for(int w=1;w<allCars.size();w++)
	 for(int i=0;i<allCars[w]->carAI.size();i++)
	  allCars[w]->carAI[i]->draw(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0));
	  
	ocean->draw(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0));
	
	engrenage->draw(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0));
	
	sky->drawSkybox(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0));
	//ressort->draw(getProjectionMatrix(),getViewMatrix(),glm::mat4(1.0));
}

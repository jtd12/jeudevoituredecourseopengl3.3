#include"gameSetup.hpp"



setup::setup()
{
	
//int randNumber = rand() % 50 + 10;


}


void setup::init()
{

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
allCars[7]->carAI.push_back(new vehiculeAI("voitureAI6",glm::vec3(1950,100,1200),0.02,0.0,"data/vehicule/vehicule5.obj","data/vehicule/Car_7_Diffuse_White.bmp"));
allCars[8]->carAI.push_back(new vehiculeAI("voitureAI6",glm::vec3(1700,100,1200),0.02,0.0,"data/vehicule/vehicule4.obj","data/vehicule/Car_6_Diffuse_White.bmp"));
ocean=new water("ocean","data/water/ocean.obj","data/water/water_man.bmp");
engrenage=new water("ocean","data/engrenage/engrenage.obj","data/decor/mur.bmp");
//levels.push_back(new decor("name",map3_2,mapcp4,mapsp));
//ressort=new water(glm::vec3(0.0,0,0.0),0,"ressort","data/engrenage/ressort/ressort_element");
//tuyeau=new water(glm::vec3(0.0,0,0.0),0,"tuyeau","data/engrenage/tuyeau/tuyeau_element");


audio=new sound;
sound1=audio->loadSound("data/audio/vehicule.wav");


cam=new camera();
cam=new camera(vec3(800, 300, 1300), vec3(0, 0, 0), vec3(0, 1, 0));
sky=new skybox();
startFreeCamera=true;
startcameraFollow=false;
hud_=new hud();
hud_->init("data/textures/tt.bmp",glm::vec3(3.0f,-0.1f,1.0f),glm::vec3(-1.5f,-0.1f,1.0f),glm::vec3(3.0f,1.5f,1.0f),glm::vec3(-1.5f,1.5f,1.0f));

hud2_=new hud();
hud2_->init("data/textures/aiguille.bmp",glm::vec3(3.5f,0.7f,1.2f),glm::vec3(0.5f,0.2f,1.0f),glm::vec3(3.5f,1.5f,1.0f),glm::vec3(0.5f,1.5f,1.0f));

tHUD=new textHUD();
tHUD->initText2D( "data/hud/Holstein.DDS" );
finishedGame=false;
time=50;
keyV = false; 

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
delete hud_;
delete hud2_;

delete tHUD;

tHUD->cleanupText2D();
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

	   		break;
	   	
		case 'V':	
	   	case 'v':
	   		keyV=true;
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
	
	   switch(key)
	   {
	   	case 'm':

	   		break;
	   	
		case 'V':	
	   	case 'v':
	   	
	   		break;
	   		
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
if(allCars[0]->car->getSpeed()>1.0f)
{
  cam->setPosition(glm::vec3(allCars[w]->car->getLocation().x+cos(-allCars[w]->car->getRotation().y)*-500,200,allCars[w]->car->getLocation().z+sin(-allCars[w]->car->getRotation().y)*-500));
  cam->setTarget(glm::vec3(allCars[w]->car->getLocation().x,10,allCars[w]->car->getLocation().z));
}
else if(allCars[0]->car->getSpeed()<-1.0f)
{
  cam->setPosition(glm::vec3(allCars[w]->car->getLocation().x+cos(-allCars[w]->car->getRotation().y)*500,200,allCars[w]->car->getLocation().z+sin(-allCars[w]->car->getRotation().y)*500));
  cam->setTarget(glm::vec3(allCars[w]->car->getLocation().x,10,allCars[w]->car->getLocation().z));
}
else
{
  cam->setPosition(glm::vec3(allCars[w]->car->getLocation().x+cos(-allCars[w]->car->getRotation().y)*-500,150,allCars[w]->car->getLocation().z+sin(-allCars[w]->car->getRotation().y)*-500));
  cam->setTarget(glm::vec3(allCars[w]->car->getLocation().x,10,allCars[w]->car->getLocation().z));
}
}
}

void setup::gestionHud(hud* h)
{	
for(int w=0;w<1;w++)	
{
	if(allCars[0]->car->getSpeed()>1.0f)
	{
  h->setPosition(glm::vec3(allCars[w]->car->getLocation().x+cos(-allCars[w]->car->getRotation().y)*-50,180,allCars[w]->car->getLocation().z+sin(-allCars[w]->car->getRotation().y)*-50));
  h->setRotation(allCars[w]->car->getRotation());
	}
	else if(allCars[0]->car->getSpeed()<-1.0f)
	{
	  h->setPosition(glm::vec3(allCars[w]->car->getLocation().x+cos(-allCars[w]->car->getRotation().y)*20,150,allCars[w]->car->getLocation().z+sin(-allCars[w]->car->getRotation().y)*20));
 	  h->setRotation(glm::vec3(allCars[w]->car->getRotation().x,allCars[w]->car->getRotation().y,allCars[w]->car->getRotation().z));
	}
	else
	{
		  h->setPosition(glm::vec3(allCars[w]->car->getLocation().x+cos(-allCars[w]->car->getRotation().y)*-50,180,allCars[w]->car->getLocation().z+sin(-allCars[w]->car->getRotation().y)*-50));
  		  h->setRotation(allCars[w]->car->getRotation());
	} 
  }
}


void setup::updateCamera()
{
	cam->deplacer();
}

 

void setup::update()
{
	
	resetCar(startFreeCamera);

	if(time<=0 && !finishedGame)
	{
	time=0.0f;
	keyV=false;
	startcameraFollow=true;
	startFreeCamera=false;
	gestionHud(hud_);
	gestionHud(hud2_);
	

    	
	if(startcameraFollow)
	{
		
		for(int w=0;w<1;w++)
		{
		if(allCars[w]->car->getSpeed()>0.0f)
		  hud2_->tournerAiguille(allCars[w]->car->getSpeed());
		}
	
	gestionHud(hud_);
	gestionHud(hud2_);
	gestionCam();
	  

	  	
	 for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
		  allCars[w]->carAI[i]->update();
	}
}
	if(time>0)
	{
			startcameraFollow=false;
			startFreeCamera=true;
	}
	  if(startFreeCamera)
	  {
	  	cam->collisionCameraAndGround();
	  	collisionCameraAndWall();
	  	allCars[0]->car->placementRoues();
	  	allCars[0]->car->setGravity();
	  	
		for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
		 {
		  allCars[w]->carAI[i]->placeRoues(startFreeCamera);
		  allCars[w]->carAI[i]->setGravity();
		}
	
		 updateCamera();
	}
	
	if(time<=0)
	{
	audio->setListener(allCars[0]->car->getLocation(),allCars[0]->car->getLocation());
	audio->playSound(sound1,allCars[0]->car->getLocation(),(allCars[0]->car->getSpeed()/allCars[0]->car->getMaxSpeed())+1);

 	if(startcameraFollow)
 	{
 	for(int w=0;w<1;w++)
 	{
		    allCars[w]->car->updateControl();
	}
	
	allCars[0]->car->placementRoues();
	allCars[0]->car->setGravity();
	   
	   for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
		 {
		  allCars[w]->carAI[i]->placeRoues(startFreeCamera); 
		  allCars[w]->carAI[i]->setGravity(); 
		}
 	}
	 
 //sky->update();
	 for(int w=0;w<1;w++)
		   allCars[w]->car->update();

		  
	  collisionCarAI();
	  for(int z=0;z<1;z++)
	   for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
	   collisionCar(allCars[z]->car->getLocation(),allCars[w]->carAI[i]->getLocation());
	   
	  collisionCarAndWall();

	  allCars[0]->car->checkPoints(glm::vec3(4000,50,1100),allCars[0]->car->getLocation());
	  allCars[0]->car->checkPoints(glm::vec3(-7000,50,1800),allCars[0]->car->getLocation());
	  allCars[0]->car->checkPoints(glm::vec3(-2800,50,-200),allCars[0]->car->getLocation());
	  allCars[0]->car->checkPoints(glm::vec3(-600,50,1200),allCars[0]->car->getLocation());
	  
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
	  allCars[w]->carAI[i]->checkPoints(glm::vec3(4000,50,1100),allCars[w]->carAI[i]->getLocation());
	  allCars[w]->carAI[i]->checkPoints(glm::vec3(-7000,50,1800),allCars[w]->carAI[i]->getLocation());
	  allCars[w]->carAI[i]->checkPoints(glm::vec3(-2800,50,-200),allCars[w]->carAI[i]->getLocation());
	  allCars[w]->carAI[i]->checkPoints(glm::vec3(-600,50,1200),allCars[w]->carAI[i]->getLocation());
	}
}
 	

	
}

void setup::resetCar(bool startFreeCamera)
{
	
	
	if(allCars[0]->car->getPoints()>=15000)
	{
		finishedGame=true;
	}

	
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
	if(allCars[w]->carAI[i]->getPoints()>=15000)
	{
		finishedGame=true;

	}
 }
 

 
 
 if(keyV && time>0 && finishedGame)
 {
 	finishedGame=false;
 }
	
    if( !finishedGame )
		 time-=0.1f;
		
	 else if(finishedGame)
 {

   time=500;
   cam->setPosition(glm::vec3(800, 300, 1300));
   allCars[0]->car->resetPoints();
   allCars[0]->car->setLocation(glm::vec3(2600,200,1200));
   allCars[0]->car->setSpeed(0.0f);
   allCars[0]->car->setRotation(glm::vec3(0,0,0));
   allCars[0]->car->placementRoues();
   allCars[0]->car->setGravity();
   
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
      allCars[w]->carAI[i]->resetPoints();
      allCars[1]->carAI[i]->setLocation(glm::vec3(-450,100,1200));
      allCars[2]->carAI[i]->setLocation(glm::vec3(-850,100,1200));
      allCars[3]->carAI[i]->setLocation(glm::vec3(-100,100,1200));
      allCars[4]->carAI[i]->setLocation(glm::vec3(550,100,1200));
      allCars[5]->carAI[i]->setLocation(glm::vec3(1200,100,1200));
      allCars[6]->carAI[i]->setLocation(glm::vec3(1500,100,1200));
      allCars[7]->carAI[i]->setLocation(glm::vec3(1950,100,1200));
      allCars[8]->carAI[i]->setLocation(glm::vec3(1700,100,1200));
      allCars[w]->carAI[i]->setRotation(glm::vec3(0,0,0));
      allCars[w]->carAI[i]->placeRoues(startFreeCamera);
      allCars[w]->carAI[i]->setGravity();

  	}
	}

}


void setup::carMovement(float speed)
{
	   for(int w=0;w<1;w++)
	   {
	      allCars[w]->car->limitSpeed(speed); 
	      allCars[w]->car->setPoints(1);
	  }
}

void setup::cameraMovement(float speed)
{
	      
		  cam->setSpeed(speed); 
	  
}


void setup::collisionCameraAndWall()
{
  if(linePointDetection(cam->collidersDetection[0]->getLocation().x,
	cam->collidersDetection[0]->getLocation().z,cam->collidersDetection[1]->getLocation().x,
	cam->collidersDetection[1]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}
	
	
	else if(linePointDetection(cam->collidersDetection[2]->getLocation().x,
	cam->collidersDetection[2]->getLocation().z,cam->collidersDetection[3]->getLocation().x,
	cam->collidersDetection[3]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}
	
	
	
	else if(linePointDetection(cam->collidersDetection[4]->getLocation().x,
	cam->collidersDetection[4]->getLocation().z,cam->collidersDetection[5]->getLocation().x,
	cam->collidersDetection[5]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}
	
	
	 else if(linePointDetection(cam->collidersDetection[6]->getLocation().x,
	cam->collidersDetection[6]->getLocation().z,cam->collidersDetection[7]->getLocation().x,
	cam->collidersDetection[7]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	
	else if(linePointDetection(cam->collidersDetection[8]->getLocation().x,
	cam->collidersDetection[8]->getLocation().z,cam->collidersDetection[9]->getLocation().x,
	cam->collidersDetection[9]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	
	else if(linePointDetection(cam->collidersDetection[10]->getLocation().x,
	cam->collidersDetection[10]->getLocation().z,cam->collidersDetection[11]->getLocation().x,
	cam->collidersDetection[11]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	else if(linePointDetection(cam->collidersDetection[12]->getLocation().x,
	cam->collidersDetection[12]->getLocation().z,cam->collidersDetection[13]->getLocation().x,
	cam->collidersDetection[13]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}
	
	
	else if(linePointDetection(cam->collidersDetection[14]->getLocation().x,
	cam->collidersDetection[14]->getLocation().z,cam->collidersDetection[15]->getLocation().x,
	cam->collidersDetection[15]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	
	else if(linePointDetection(cam->collidersDetection[16]->getLocation().x,
	cam->collidersDetection[16]->getLocation().z,cam->collidersDetection[17]->getLocation().x,
	cam->collidersDetection[17]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	
	
	else if(linePointDetection(cam->collidersDetection[18]->getLocation().x,
	cam->collidersDetection[18]->getLocation().z,cam->collidersDetection[19]->getLocation().x,
	cam->collidersDetection[19]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}


	else if(linePointDetection(cam->collidersDetection[20]->getLocation().x,
	cam->collidersDetection[20]->getLocation().z,cam->collidersDetection[21]->getLocation().x,
	cam->collidersDetection[21]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	
	else if(linePointDetection(cam->collidersDetection[22]->getLocation().x,
	cam->collidersDetection[22]->getLocation().z,cam->collidersDetection[23]->getLocation().x,
	cam->collidersDetection[23]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	
	else if(linePointDetection(cam->collidersDetection[24]->getLocation().x,
	cam->collidersDetection[24]->getLocation().z,cam->collidersDetection[25]->getLocation().x,
	cam->collidersDetection[25]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}

	
	else if(linePointDetection(cam->collidersDetection[26]->getLocation().x,
	cam->collidersDetection[26]->getLocation().z,cam->collidersDetection[27]->getLocation().x,
	cam->collidersDetection[27]->getLocation().z,cam->bb[0]->getLocation().x,cam->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-50.8f);

	}
	else
	{
		   cameraMovement(0.5f);
	}
}

void setup::collisionCarAndWall()
{
	
   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[0]->getLocation().x,
	allCars[w]->car->collidersDetection[0]->getLocation().z,allCars[w]->car->collidersDetection[1]->getLocation().x,
	allCars[w]->car->collidersDetection[1]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         carMovement(-1.0f);

	}
	
	  for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[0]->getLocation().x,
	allCars[w]->car->collidersDetection[0]->getLocation().z,allCars[w]->car->collidersDetection[1]->getLocation().x,
	allCars[w]->car->collidersDetection[1]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
      carMovement(1.0f);

	}
	

   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[2]->getLocation().x,
	allCars[w]->car->collidersDetection[2]->getLocation().z,allCars[w]->car->collidersDetection[3]->getLocation().x,
	allCars[w]->car->collidersDetection[3]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
   
    carMovement(-1.0f);
      

	}
	
	
   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[2]->getLocation().x,
	allCars[w]->car->collidersDetection[2]->getLocation().z,allCars[w]->car->collidersDetection[3]->getLocation().x,
	allCars[w]->car->collidersDetection[3]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
   
     carMovement(1.0f);
      

	}

	for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[4]->getLocation().x,
	allCars[w]->car->collidersDetection[4]->getLocation().z,allCars[w]->car->collidersDetection[5]->getLocation().x,
	allCars[w]->car->collidersDetection[5]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
      carMovement(-1.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[4]->getLocation().x,
	allCars[w]->car->collidersDetection[4]->getLocation().z,allCars[w]->car->collidersDetection[5]->getLocation().x,
	allCars[w]->car->collidersDetection[5]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    	
     carMovement(1.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[6]->getLocation().x,
	allCars[w]->car->collidersDetection[6]->getLocation().z,allCars[w]->car->collidersDetection[7]->getLocation().x,
	allCars[w]->car->collidersDetection[7]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
      carMovement(-1.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[6]->getLocation().x,
	allCars[w]->car->collidersDetection[6]->getLocation().z,allCars[w]->car->collidersDetection[7]->getLocation().x,
	allCars[w]->car->collidersDetection[7]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    	
     carMovement(1.0f);
       

	}		


	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[8]->getLocation().x,
	allCars[w]->car->collidersDetection[8]->getLocation().z,allCars[w]->car->collidersDetection[9]->getLocation().x,
	allCars[w]->car->collidersDetection[9]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    carMovement(-1.0f);
       

	}
	
		
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[8]->getLocation().x,
	allCars[w]->car->collidersDetection[8]->getLocation().z,allCars[w]->car->collidersDetection[9]->getLocation().x,
	allCars[w]->car->collidersDetection[9]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(1.0f);
       

	}
	

		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[10]->getLocation().x,
	allCars[w]->car->collidersDetection[10]->getLocation().z,allCars[w]->car->collidersDetection[11]->getLocation().x,
	allCars[w]->car->collidersDetection[11]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {

   carMovement(-1.0f);
       
  
	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[10]->getLocation().x,
	allCars[w]->car->collidersDetection[10]->getLocation().z,allCars[w]->car->collidersDetection[11]->getLocation().x,
	allCars[w]->car->collidersDetection[11]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {

carMovement(1.0f);
       
  
	}

	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[12]->getLocation().x,
	allCars[w]->car->collidersDetection[12]->getLocation().z,allCars[w]->car->collidersDetection[13]->getLocation().x,
	allCars[w]->car->collidersDetection[13]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
      carMovement(-1.0f);
       

	}
	
	

		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[12]->getLocation().x,
	allCars[w]->car->collidersDetection[12]->getLocation().z,allCars[w]->car->collidersDetection[13]->getLocation().x,
	allCars[w]->car->collidersDetection[13]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(1.0f);
       

	}
	
	
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[14]->getLocation().x,
	allCars[w]->car->collidersDetection[14]->getLocation().z,allCars[w]->car->collidersDetection[15]->getLocation().x,
	allCars[w]->car->collidersDetection[15]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
 
      carMovement(-1.0f);
       
      
	}
	
	

	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[14]->getLocation().x,
	allCars[w]->car->collidersDetection[14]->getLocation().z,allCars[w]->car->collidersDetection[15]->getLocation().x,
	allCars[w]->car->collidersDetection[15]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
 
      carMovement(1.0f);
       
      
	}
	
	
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[16]->getLocation().x,
	allCars[w]->car->collidersDetection[16]->getLocation().z,allCars[w]->car->collidersDetection[17]->getLocation().x,
	allCars[w]->car->collidersDetection[17]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {

      carMovement(-1.0f);
    
	}
	
		
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[16]->getLocation().x,
	allCars[w]->car->collidersDetection[16]->getLocation().z,allCars[w]->car->collidersDetection[17]->getLocation().x,
	allCars[w]->car->collidersDetection[17]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {

    carMovement(1.0f);
    
	}
		
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[18]->getLocation().x,
	allCars[w]->car->collidersDetection[18]->getLocation().z,allCars[w]->car->collidersDetection[19]->getLocation().x,
	allCars[w]->car->collidersDetection[19]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {

      carMovement(-1.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[18]->getLocation().x,
	allCars[w]->car->collidersDetection[18]->getLocation().z,allCars[w]->car->collidersDetection[19]->getLocation().x,
	allCars[w]->car->collidersDetection[19]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {

     carMovement(1.0f);
       

	}
		
		
		
		
		
		//////////////////////////////////
		
		
		
	

		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[20]->getLocation().x,
	allCars[w]->car->collidersDetection[20]->getLocation().z,allCars[w]->car->collidersDetection[21]->getLocation().x,
	allCars[w]->car->collidersDetection[21]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
  carMovement(-1.0f);
       
 
	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[20]->getLocation().x,
	allCars[w]->car->collidersDetection[20]->getLocation().z,allCars[w]->car->collidersDetection[21]->getLocation().x,
	allCars[w]->car->collidersDetection[21]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(1.0f);
       
 
	}

	
	
			for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[22]->getLocation().x,
	allCars[w]->car->collidersDetection[22]->getLocation().z,allCars[w]->car->collidersDetection[23]->getLocation().x,
	allCars[w]->car->collidersDetection[23]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    carMovement(-1.0f);

	}
	
	
			for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[22]->getLocation().x,
	allCars[w]->car->collidersDetection[22]->getLocation().z,allCars[w]->car->collidersDetection[23]->getLocation().x,
	allCars[w]->car->collidersDetection[23]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(1.0f);

	}
	
	
	
	//////////////////////////////////
	
	
	
	
	   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[24]->getLocation().x,
	allCars[w]->car->collidersDetection[24]->getLocation().z,allCars[w]->car->collidersDetection[25]->getLocation().x,
	allCars[w]->car->collidersDetection[25]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         carMovement(-1.0f);

	}
	
	  for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[24]->getLocation().x,
	allCars[w]->car->collidersDetection[24]->getLocation().z,allCars[w]->car->collidersDetection[25]->getLocation().x,
	allCars[w]->car->collidersDetection[25]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
      carMovement(1.0f);

	}
	
	
	   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[26]->getLocation().x,
	allCars[w]->car->collidersDetection[26]->getLocation().z,allCars[w]->car->collidersDetection[27]->getLocation().x,
	allCars[w]->car->collidersDetection[27]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         carMovement(-1.0f);

	}
	
	  for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[26]->getLocation().x,
	allCars[w]->car->collidersDetection[26]->getLocation().z,allCars[w]->car->collidersDetection[27]->getLocation().x,
	allCars[w]->car->collidersDetection[27]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
      carMovement(1.0f);

	}

	
	
}


void setup::collisionCar(glm::vec3 pos,glm::vec3 pos2)
{
	
	float dist=sqrt((pos.x-pos2.x)*(pos.x-pos2.x) + (pos.z-pos2.z)*(pos.z-pos2.z));
	
		 	  if(dist<80)
		 	  {
		 	 carMovement(-1.0f);
		 	 allCars[0]->car->setPoints(1);
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

	cam->computeMatricesFromInputs(startFreeCamera);
	
	
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
	   	
	if(startcameraFollow && allCars[0]->car->getSpeed()>=0.0f)
	{
	hud_->draw(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0),glm::vec3(170,120,150));
	hud2_->draw(cam->getProjectionMatrix(),cam->getViewMatrix(),glm::mat4(1.0),glm::vec3(20,15,50));
	}
	
		char text[256];
		char text2[256];
		char text3[256];
		
		tHUD->printText2D("PLAYER: ", 10, 560, 17);
		
		if(allCars[0]->car->getSpeed()>0)
		  sprintf(text,"SPEED:%.f",allCars[0]->car->getSpeed()*80);
		else
		  sprintf(text,"SPEED:%.f",allCars[0]->car->getSpeed()*-80);
		  
		tHUD->printText2D(text, 10, 540, 17);
		sprintf(text,"POINTS:%d",allCars[0]->car->getPoints());
		
		tHUD->printText2D(text, 10, 500, 17);
		
		tHUD->printText2D("PLAYERAI: ", 10, 410, 17);
		
		for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
		 {
			sprintf(text2,"CAR-N\B0:%d POINTS:%d\n                        SPEED:%.f\n",w,allCars[w]->carAI[i]->getPoints(),allCars[w]->carAI[i]->getSpeed());
			tHUD->printText2D(text2, 10, 400-(w*30), 14);
		 }
		 
	if(time>0)
	{
		sprintf(text3,"START GAME IN:%.f",time);
		tHUD->printText2D(text3, 250, 400, 27);
	}
	
	for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
		 {
	if( allCars[0]->car->getPoints()>=15000 && allCars[w]->carAI[i]->getPoints()<15000)
	{
		tHUD->printText2D("You win!!!", 65, 300, 17);
	}
	else
	{
	  if( allCars[0]->car->getPoints()<15000 && allCars[w]->carAI[i]->getPoints()>=15000)
		tHUD->printText2D("You lose!!!", 65, 300, 17);
	}
  }
	//ressort->draw(getProjectionMatrix(),getViewMatrix(),glm::mat4(1.0));
}

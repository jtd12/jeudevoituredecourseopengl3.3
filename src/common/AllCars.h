#ifndef DEF_ALLCARS_H
#define DEF_ALLCARS_H
#include"carAI.hpp"
#include"car.h"
#include"C:\library\glm\glm\glm.hpp"
#include <C:/library/glm/glm/gtc/matrix_transform.hpp>

class allVehicule
{
public:
	allVehicule();
	~allVehicule();
	std::vector<vehiculeAI*> carAI;
	vehicule* car;
};

#endif

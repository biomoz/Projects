#include "ParcServices.h"
#include <iostream>
#include <string>
using namespace std;

ParcServices::ParcServices()
{
	this->subtropicSwimmingPool = false;
	this->sportslnfrastructure = false;
	this->bowlingAlley = false;
	this->bicycleRent = false;
	this->childrensParadise = false;
	this->waterBikes = false;
}

ParcServices::ParcServices(bool subtropicSwimmingPool, bool sportslnfrastructure, bool bowlingAlley, bool bicycleRent, bool childrensParadise, bool waterBikes)
{
	this->subtropicSwimmingPool = subtropicSwimmingPool;
	this->sportslnfrastructure = sportslnfrastructure;
	this->bowlingAlley = bowlingAlley;
	this->bicycleRent = bicycleRent;
	this->childrensParadise = childrensParadise;
	this->waterBikes = waterBikes;
}

ParcServices::~ParcServices()
{
}

void ParcServices::setSubtropicSwimmingPool(bool subtropicSwimmingPool)
{
	this->subtropicSwimmingPool = subtropicSwimmingPool;
}

void ParcServices::setSportslnfrastructure(bool sportslnfrastructure)
{
	this->sportslnfrastructure = sportslnfrastructure;
}

void ParcServices::setBowlingAlley(bool bowlingAlley)
{
	this->bowlingAlley = bowlingAlley;
}

void ParcServices::setBicycleRent(bool bicycleRent)
{
	this->bicycleRent = bicycleRent;
}

void ParcServices::setChildrensParadise(bool childrensParadise)
{
	this->childrensParadise = childrensParadise;
}

void ParcServices::setWaterBikes(bool waterBikes)
{
	this->waterBikes = waterBikes;
}

bool ParcServices::getSubtropicSwimmingPool()
{
	return this->subtropicSwimmingPool;
}

bool ParcServices::getSportslnfrastructure()
{
	return this->sportslnfrastructure;
}

bool ParcServices::getBowlingAlley()
{
	return this->bowlingAlley;
}

bool ParcServices::getBicycleRent()
{
	return this->bicycleRent;
}

bool ParcServices::getChildrensParadise()
{
	return this->childrensParadise;
}

bool ParcServices::getWaterBikes()
{
	return this->waterBikes;
}

void ParcServices::print()
{
	cout << "Subtropic Swimming Pool: " << this->subtropicSwimmingPool << endl;
	cout << "Sports Infrastructure: " << this->sportslnfrastructure << endl;
	cout << "Bowling Alley: " << this->bowlingAlley << endl;
	cout << "Bicycle Rent: " << this->bicycleRent << endl;
	cout << "Children's Paradise: " << this->childrensParadise << endl;
	cout << "Water Bikes: " << this->waterBikes << endl;
}
#include "Accommodations.h"

Accommodations::Accommodations()
{
	this->ID = 0;
	this->nrPeople = 0;
	this->size = 0;
	this->bathroomWithBath = false;
	this->luxuryLevel = LuxuryLevel();
}

Accommodations::Accommodations(int ID, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel)
{
	this->ID = ID;
	this->nrPeople = nrPeople;
	this->size = size;
	this->bathroomWithBath = bathroomWithBath;
	this->luxuryLevel = luxuryLevel;
}

Accommodations::~Accommodations()
{
}

void Accommodations::setID(int ID)
{
	this->ID = ID;
}

void Accommodations::setNrPeople(int nrPeople)
{
	this->nrPeople = nrPeople;
}

void Accommodations::setSize(int size)
{
	this->size = size;
}

void Accommodations::setBathroomWithBath(bool bathroomWithBath)
{
	this->bathroomWithBath = bathroomWithBath;
}

void Accommodations::setLuxuryLevel(LuxuryLevel luxuryLevel)
{
	this->luxuryLevel = luxuryLevel;
}

int Accommodations::getID()
{
	return this->ID;
}

int Accommodations::getNrPeople()
{
	return this->nrPeople;
}

int Accommodations::getSize()
{
	return this->size;
}

bool Accommodations::getBathroomWithBath()
{
	return this->bathroomWithBath;
}

LuxuryLevel Accommodations::getLuxuryLevel()
{
	return this->luxuryLevel;
}

void Accommodations::print()
{
	cout << "Accommodation: " << endl;
	cout << "ID: " << this->ID << endl;
	cout << "Nr people: " << this->nrPeople << endl;
	cout << "Size: " << this->size << endl;
	cout << "Bathroom with bath: " << this->bathroomWithBath << endl;
	this->luxuryLevel.print();
}

void Accommodations::setBedrooms(int bedrooms)
{
}

int Accommodations::getBedrooms()
{
	return 0;
}

void Accommodations::setFloor(int floor)
{
}

void Accommodations::setLocation(string location)
{
}

void Accommodations::setNrBeds(int nrBeds)
{
}

void Accommodations::setChildrenBed(bool childrenBed)
{
}

int Accommodations::getFloor()
{
	return 0;
}

string Accommodations::getLocation()
{
	return "";
}

int Accommodations::getNrBeds()
{
	return 0;
}

bool Accommodations::getChildrenBed()
{
	return false;
}

void Accommodations::setLLBBQ(bool BBQ)
{
	this->luxuryLevel.setBBQ(BBQ);
}

void Accommodations::setLLSurroundSystem(bool surroundSystem)
{
	this->luxuryLevel.setSurroundSystem(surroundSystem);
}

void Accommodations::setLLBreakfastService(bool breakfastService)
{
	this->luxuryLevel.setBreakfastService(breakfastService);
}

void Accommodations::setLLCleaningService(bool cleaningService)
{
	this->luxuryLevel.setCleaningService(cleaningService);
}

void Accommodations::setLLAccommodationKind(string accommodationKind)
{
	this->luxuryLevel.setAccommodationKind(accommodationKind);
}

bool Accommodations::getLLBBQ()
{
	return this->luxuryLevel.getBBQ();
}

bool Accommodations::getLLSurroundSystem()
{
	return this->luxuryLevel.getSurroundSystem();
}

bool Accommodations::getLLBreakfastService()
{
	return this->luxuryLevel.getBreakfastService();
}

bool Accommodations::getLLCleaningService()
{
	return this->luxuryLevel.getCleaningService();
}

string Accommodations::getLLAccommodationKind()
{
	return this->luxuryLevel.getAccommodationKind();
}
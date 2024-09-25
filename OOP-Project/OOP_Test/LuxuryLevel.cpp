#include "LuxuryLevel.h"

LuxuryLevel::LuxuryLevel()
{
	this->BBQ = false;
	this->surroundSystem = false;
	this->breakfastService = false;
	this->cleaningService = false;
	this->accommodationKind = "None";
}

LuxuryLevel::LuxuryLevel(bool BBQ, bool surroundSystem, bool breakfastService, bool cleaningService, string accommodationKind)
{
	this->BBQ = BBQ;
	this->surroundSystem = surroundSystem;
	this->breakfastService = breakfastService;
	this->cleaningService = cleaningService;
	this->accommodationKind = accommodationKind;
}

LuxuryLevel::~LuxuryLevel()
{
}

void LuxuryLevel::setBBQ(bool BBQ)
{
	this->BBQ = BBQ;
}

void LuxuryLevel::setSurroundSystem(bool surroundSystem)
{
	this->surroundSystem = surroundSystem;
}

void LuxuryLevel::setBreakfastService(bool breakfastService)
{
	this->breakfastService = breakfastService;
}

void LuxuryLevel::setCleaningService(bool cleaningService)
{
	this->cleaningService = cleaningService;
}

void LuxuryLevel::setAccommodationKind(string accommodationKind)
{
	this->accommodationKind = accommodationKind;
}

bool LuxuryLevel::getBBQ()
{
	return this->BBQ;
}

bool LuxuryLevel::getSurroundSystem()
{
	return this->surroundSystem;
}

bool LuxuryLevel::getBreakfastService()
{
	return this->breakfastService;
}

bool LuxuryLevel::getCleaningService()
{
	return this->cleaningService;
}

string LuxuryLevel::getAccommodationKind()
{
	return this->accommodationKind;
}

void LuxuryLevel::print()
{
	cout << "Luxury Level: " << endl;
	cout << "BBQ: " << this->BBQ << endl;
	cout << "Surround system: " << this->surroundSystem << endl;
	cout << "Breakfast service: " << this->breakfastService << endl;
	cout << "Cleaning service: " << this->cleaningService << endl;
	cout << "Accommodation kind: " << this->accommodationKind << endl;
}
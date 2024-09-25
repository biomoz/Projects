#include "HotelRoom.h"

HotelRoom::HotelRoom()
{
	this->floor = 0;
	this->location = "";
	this->nrBeds = 0;
	this->childrenBed = false;
}

HotelRoom::HotelRoom(int ID, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel, int floor, string location, int nrBeds, bool childrenBed)
	:Accommodations(ID, nrPeople, size, bathroomWithBath, luxuryLevel)
{
	this->floor = floor;
	this->location = location;
	this->nrBeds = nrBeds;
	this->childrenBed = childrenBed;
}

HotelRoom::~HotelRoom()
{
}

void HotelRoom::setFloor(int floor)
{
	this->floor = floor;
}

void HotelRoom::setLocation(string location)
{
	this->location = location;
}

void HotelRoom::setNrBeds(int nrBeds)
{
	this->nrBeds = nrBeds;
}

void HotelRoom::setChildrenBed(bool childrenBed)
{
	this->childrenBed = childrenBed;
}

int HotelRoom::getFloor()
{
	return this->floor;
}

string HotelRoom::getLocation()
{
	return this->location;
}

int HotelRoom::getNrBeds()
{
	return this->nrBeds;
}

bool HotelRoom::getChildrenBed()
{
	return this->childrenBed;
}

void HotelRoom::print()
{
	cout << "HotelRoom: " << endl;
	Accommodations::print();
	cout << "Floor: " << this->floor << endl;
	cout << "Location: " << this->location << endl;
	cout << "Number of beds: " << this->nrBeds << endl;
	cout << "Children bed: " << this->childrenBed << endl;
}
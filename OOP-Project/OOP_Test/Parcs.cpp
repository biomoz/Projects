#include "Parcs.h"

#include "Parcs.h"

Parcs::Parcs()
{
	name = "";
	address = "";
	services = ParcServices();
	accommodations = vector<Accommodations*>();
}

Parcs::Parcs(string name, string address, ParcServices services, vector<Accommodations*> accommodations)
{
	this->name = name;
	this->address = address;
	this->services = services;
	this->accommodations = accommodations;
}

Parcs::~Parcs()
{
}

void Parcs::setName(string name)
{
	this->name = name;
}

void Parcs::setAddress(string address)
{
	this->address = address;
}

void Parcs::setServices(ParcServices services)
{
	this->services = services;
}

void Parcs::setAccommodations(vector<Accommodations*> accommodations)
{
	this->accommodations = accommodations;
}

string Parcs::getName()
{
	return this->name;
}

string Parcs::getAddress()
{
	return this->address;
}

ParcServices Parcs::getServices()
{
	return this->services;
}

vector<Accommodations*> Parcs::getAccommodations()
{
	return this->accommodations;
}

void Parcs::addAccommodation(Accommodations* accommodation)
{
	this->accommodations.push_back(accommodation);
}

void Parcs::deleteAccommodation(int index)
{
	this->accommodations.erase(this->accommodations.begin() + index);
}

void Parcs::print()
{
	cout << "Parc: " << endl;
	cout << "Name: " << this->name << endl;
	cout << "Address: " << this->address << endl;
	cout << "Services: " << endl;
	this->services.print();
	cout << "Accommodations: " << endl;
	for (int i = 0; i < this->accommodations.size(); i++)
	{
		this->accommodations[i]->print();
	}
}

void Parcs::setPSSubtropicSwimmingPool(bool subtropicSwimmingPool)
{
	this->services.setSubtropicSwimmingPool(subtropicSwimmingPool);
}

void Parcs::setPSSportslnfrastructure(bool sportslnfrastructure)
{
	this->services.setSportslnfrastructure(sportslnfrastructure);
}

void Parcs::setPSBowlingAlley(bool bowlingAlley)
{
	this->services.setBowlingAlley(bowlingAlley);
}

void Parcs::setPSBicycleRent(bool bicycleRent)
{
	this->services.setBicycleRent(bicycleRent);
}

void Parcs::setPSChildrensParadise(bool childrensParadise)
{
	this->services.setChildrensParadise(childrensParadise);
}

void Parcs::setPSWaterBikes(bool waterBikes)
{
	this->services.setWaterBikes(waterBikes);
}

bool Parcs::getPSSubtropicSwimmingPool()
{
	return this->services.getSubtropicSwimmingPool();
}

bool Parcs::getPSSportslnfrastructure()
{
	return this->services.getSportslnfrastructure();
}

bool Parcs::getPSBowlingAlley()
{
	return this->services.getBowlingAlley();
}

bool Parcs::getPSBicycleRent()
{
	return this->services.getBicycleRent();
}

bool Parcs::getPSChildrensParadise()
{
	return this->services.getChildrensParadise();
}

bool Parcs::getPSWaterBikes()
{
	return this->services.getWaterBikes();
}
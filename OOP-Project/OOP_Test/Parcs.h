#ifndef PARC_H
#define PARC_H

#include <string>
#include "ParcServices.h"
#include "Accommodations.h"
#include <iostream>
#include <vector>
using namespace std;

class Parcs
{
private:
	string name;
	string address;
	ParcServices services;
	vector<Accommodations*> accommodations;
public:
	Parcs();
	Parcs(string name, string address, ParcServices services, vector<Accommodations*> accommodations);
	~Parcs();
	void setName(string name);
	void setAddress(string address);
	void setServices(ParcServices services);
	void setAccommodations(vector<Accommodations*> accommodations);
	void addAccommodation(Accommodations* accommodation);
	void deleteAccommodation(int index);
	string getName();
	string getAddress();
	ParcServices getServices();
	vector<Accommodations*> getAccommodations();
	void print();
	void setPSSubtropicSwimmingPool(bool subtropicSwimmingPool);
	void setPSSportslnfrastructure(bool sportslnfrastructure);
	void setPSBowlingAlley(bool bowlingAlley);
	void setPSBicycleRent(bool bicycleRent);
	void setPSChildrensParadise(bool childrensParadise);
	void setPSWaterBikes(bool waterBikes);
	bool getPSSubtropicSwimmingPool();
	bool getPSSportslnfrastructure();
	bool getPSBowlingAlley();
	bool getPSBicycleRent();
	bool getPSChildrensParadise();
	bool getPSWaterBikes();
};

#endif // !PARC_H
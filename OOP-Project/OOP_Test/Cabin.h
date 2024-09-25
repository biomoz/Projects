#ifndef CABIN_H
#define CABIN_H

#include "Accommodations.h"
#include <string>
#include <iostream>
using namespace std;

class Cabin : public Accommodations
{
private:
	int bedrooms;
public:
	Cabin();
	Cabin(int ID, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel, int bedrooms);
	~Cabin();
	void setBedrooms(int bedrooms);
	int getBedrooms();
	void print();
};

#endif // !CABIN_H
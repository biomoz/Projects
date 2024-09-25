
#include "Cabin.h"

Cabin::Cabin()
{
	this->bedrooms = 0;
}

Cabin::Cabin(int ID, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel, int bedrooms)
	:Accommodations(ID, nrPeople, size, bathroomWithBath, luxuryLevel)
{
	this->bedrooms = bedrooms;
}

Cabin::~Cabin()
{
}

void Cabin::setBedrooms(int bedrooms)
{
	this->bedrooms = bedrooms;
}

int Cabin::getBedrooms()
{
	return this->bedrooms;
}

void Cabin::print()
{
	cout << "Cabin: " << endl;
	Accommodations::print();
	cout << "Bedrooms: " << this->bedrooms << endl;

}


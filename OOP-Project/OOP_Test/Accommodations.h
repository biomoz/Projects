#ifndef ACCOMMODATIONS_H
#define ACCOMMODATIONS_H
#include "LuxuryLevel.h"
#include <iostream>
#include <string>
using namespace std;

class Accommodations
{
private:
	int ID;
	int nrPeople;
	int size;
	bool bathroomWithBath;
	LuxuryLevel luxuryLevel;
public:
	Accommodations();
	Accommodations(int ID, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel);
	~Accommodations();
	void setID(int ID);
	void setNrPeople(int nrPeople);
	void setSize(int size);
	void setBathroomWithBath(bool bathroomWithBath);
	void setLuxuryLevel(LuxuryLevel luxuryLevel);
	int getID();
	int getNrPeople();
	int getSize();
	bool getBathroomWithBath();
	LuxuryLevel getLuxuryLevel();
	virtual void print();
	virtual void setBedrooms(int bedrooms);
	virtual int getBedrooms();
	virtual void setFloor(int floor);
	virtual void setLocation(string location);
	virtual void setNrBeds(int nrBeds);
	virtual void setChildrenBed(bool childrenBed);
	virtual int getFloor();
	virtual string getLocation();
	virtual int getNrBeds();
	virtual bool getChildrenBed();
	void setLLBBQ(bool BBQ);
	void setLLSurroundSystem(bool surroundSystem);
	void setLLBreakfastService(bool breakfastService);
	void setLLCleaningService(bool cleaningService);
	void setLLAccommodationKind(string accommodationKind);
	bool getLLBBQ();
	bool getLLSurroundSystem();
	bool getLLBreakfastService();
	bool getLLCleaningService();
	string getLLAccommodationKind();
};

#endif // !ACCOMMODATIONS_H
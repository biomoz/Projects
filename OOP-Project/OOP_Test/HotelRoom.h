#ifndef HOTELROOM_H
#define HOTELROOM_H

#include "Accommodations.h"
#include <iostream>
#include <string>
using namespace std;

class HotelRoom : public Accommodations
{
private:
	int floor;
	string location;
	int nrBeds;
	bool childrenBed;
public:
	HotelRoom();
	HotelRoom(int ID, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel, int floor, string location, int nrBeds, bool childrenBed);
	~HotelRoom();
	void setFloor(int floor);
	void setLocation(string location);
	void setNrBeds(int nrBeds);
	void setChildrenBed(bool childrenBed);
	int getFloor();
	string getLocation();
	int getNrBeds();
	bool getChildrenBed();
	void print();
};

#endif // !HOTELROOM_H
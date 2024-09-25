#ifndef BOOKING_H
#define BOOKING_H

#include "Customer.h"
#include "Accommodations.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Booking
{
private:
	int ID;
	Customer customer;
	vector<Accommodations*> accommodations;
	bool activityPass;
	bool sportsPass;
	bool bicycleRent;
	bool swimmingPass;

public:
	Booking();
	Booking(int ID, Customer customer, vector<Accommodations*> accommodations, bool activityPass, bool sportsPass, bool bicycleRent, bool swimmingPass);
	~Booking();
	void setID(int ID);
	void setCustomer(Customer customer);
	void setAccommodations(vector<Accommodations*> accommodations);
	void setActivityPass(bool activityPass);
	void setSportsPass(bool sportsPass);
	void setBicycleRent(bool bicycleRent);
	void setSwimmingPass(bool swimmingPass);
	int getID();
	Customer getCustomer();
	vector<Accommodations*> getAccommodations();
	void addAccommodation(Accommodations* accommodation);
	void deleteAccommodation(int index);
	bool getActivityPass();
	bool getSportsPass();
	bool getBicycleRent();
	bool getSwimmingPass();
	void print();
	void setCustName(string name);
	void setCustAddress(string address);
	void setCustMail(string email);
	string getCustName();
	string getCustAddress();
	string getCustMail();
};

#endif // !BOOKING_H
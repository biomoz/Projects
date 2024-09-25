#include "Booking.h"


Booking::Booking()
{
	ID = 0;
	customer = Customer();
	accommodations = vector<Accommodations*>();
	activityPass = false;
	sportsPass = false;
	bicycleRent = false;
	swimmingPass = false;
}

Booking::Booking(int ID, Customer customer, vector<Accommodations*> accommodations, bool activityPass, bool sportsPass, bool bicycleRent, bool swimmingPass)
{
	this->ID = ID;
	this->customer = customer;
	this->accommodations = accommodations;
	this->activityPass = activityPass;
	this->sportsPass = sportsPass;
	this->bicycleRent = bicycleRent;
	this->swimmingPass = swimmingPass;
}

Booking::~Booking()
{
}

void Booking::setID(int ID)
{
	this->ID = ID;
}

void Booking::setCustomer(Customer customer)
{
	this->customer = customer;
}

void Booking::setAccommodations(vector<Accommodations*> accommodations)
{
	this->accommodations = accommodations;
}

void Booking::setActivityPass(bool activityPass)
{
	this->activityPass = activityPass;
}

void Booking::setSportsPass(bool sportsPass)
{
	this->sportsPass = sportsPass;
}

void Booking::setBicycleRent(bool bicycleRent)
{
	this->bicycleRent = bicycleRent;
}

void Booking::setSwimmingPass(bool swimmingPass)
{
	this->swimmingPass = swimmingPass;
}

int Booking::getID()
{
	return this->ID;
}

Customer Booking::getCustomer()
{
	return this->customer;
}

vector<Accommodations*> Booking::getAccommodations()
{
	return this->accommodations;
}

bool Booking::getActivityPass()
{
	return this->activityPass;
}

bool Booking::getSportsPass()
{
	return this->sportsPass;
}

bool Booking::getBicycleRent()
{
	return this->bicycleRent;
}

bool Booking::getSwimmingPass()
{
	return this->swimmingPass;
}

void Booking::addAccommodation(Accommodations* accommodation)
{
	this->accommodations.push_back(accommodation);
}

void Booking::deleteAccommodation (int index)
{
	this->accommodations.erase(this->accommodations.begin() + index);
}

void Booking::print()
{
	cout << "Booking: " << endl;
	cout << "Booking ID: " << this->ID << endl;
	this->customer.print();
	cout << "Accommodations: " << endl;
	for (int i = 0; i < this->accommodations.size(); i++)
	{
		this->accommodations[i]->print();
	}
	cout << "Activity Pass: " << this->activityPass << endl;
	cout << "Sports Pass: " << this->sportsPass << endl;
	cout << "Bicycle Rent: " << this->bicycleRent << endl;
	cout << "Swimming Pass: " << this->swimmingPass << endl;
}

void Booking::setCustName(string name)
{
	this->customer.setName(name);
}

void Booking::setCustAddress(string address)
{
	this->customer.setAddress(address);
}

void Booking::setCustMail(string mail)
{
	this->customer.setMail(mail);
}

string Booking::getCustName()
{
	return this->customer.getName();
}

string Booking::getCustAddress()
{
	return this->customer.getAddress();
}

string Booking::getCustMail()
{
	return this->customer.getMail();
}


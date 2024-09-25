#include "Customer.h"

Customer::Customer()
{
}

Customer::Customer(string name, string address, string mail)
{
	this->name = name;
	this->address = address;
	this->mail = mail;
}

Customer::~Customer()
{
}

void Customer::setName(string name)
{
	this->name = name;
}

void Customer::setAddress(string address)
{
	this->address = address;
}

void Customer::setMail(string mail)
{
	this->mail = mail;
}

string Customer::getName()
{
	return this->name;
}

string Customer::getAddress()
{
	return this->address;
}

string Customer::getMail()
{
	return this->mail;
}

void Customer::print()
{
	cout << "Customer: " << endl;
	cout << "Name: " << this->name << endl;
	cout << "Address: " << this->address << endl;
	cout << "Mail: " << this->mail << endl;
}



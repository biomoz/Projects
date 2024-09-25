#include "VacationParcs.h"

VacationParcs::VacationParcs()
{
}

VacationParcs::VacationParcs(string name, string address, string VAT, vector<Parcs> parcs, vector<Customer> customers)
{
	this->name = name;
	this->address = address;
	this->VAT = VAT;
	this->parcs = parcs;
	this->customers = customers;
}

VacationParcs::~VacationParcs()
{
}

void VacationParcs::setName(string name)
{
	this->name = name;
}

void VacationParcs::setAddress(string address)
{
	this->address = address;
}

void VacationParcs::setVAT(string VAT)
{
	this->VAT = VAT;
}

void VacationParcs::setParcs(vector<Parcs> parcs)
{
	this->parcs = parcs;
}

void VacationParcs::setCustomers(vector<Customer> customers)
{
	this->customers = customers;
}

string VacationParcs::getName()
{
	return this->name;
}

string VacationParcs::getAddress()
{
	return this->address;
}

string VacationParcs::getVAT()
{
	return this->VAT;
}

vector<Parcs> VacationParcs::getParcs()
{
	return this->parcs;
}

vector<Customer> VacationParcs::getCustomers()
{
	return this->customers;
}

void VacationParcs::print()
{
	cout << "Name: " << this->name << endl;
	cout << "Address: " << this->address << endl;
	cout << "VAT: " << this->VAT << endl;
	cout << "Parcs: " << endl;
	for (int i = 0; i < this->parcs.size(); i++)
	{
		cout << this->parcs[i].getName() << endl;
	}
	cout << "Customers: " << endl;
	for (int i = 0; i < this->customers.size(); i++)
	{
		cout << this->customers[i].getName() << endl;
	}
}

void VacationParcs::addParc(Parcs parc)
{
	this->parcs.push_back(parc);
}

void VacationParcs::addCustomer(Customer customer)
{
	this->customers.push_back(customer);
}

void VacationParcs::removeParc(Parcs parc)
{
	for (int i = 0; i < this->parcs.size(); i++)
	{
		if (this->parcs[i].getName() == parc.getName())
		{
			this->parcs.erase(this->parcs.begin() + i);
		}
	}
}

void VacationParcs::removeCustomer(Customer customer)
{
	for (int i = 0; i < this->customers.size(); i++)
	{
		if (this->customers[i].getName() == customer.getName())
		{
			this->customers.erase(this->customers.begin() + i);
		}
	}
}

void VacationParcs::printParcs()
{
	for (int i = 0; i < this->parcs.size(); i++)
	{
		cout << this->parcs[i].getName() << endl;
	}
}

void VacationParcs::printCustomers()
{
	for (int i = 0; i < this->customers.size(); i++)
	{
		cout << this->customers[i].getName() << endl;
	}
}


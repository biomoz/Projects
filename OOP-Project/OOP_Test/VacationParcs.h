#ifndef VACATION_PARKS_H
#define VACATION_PARKS_H

#include "Parcs.h"
#include "Customer.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class VacationParcs
{
private:
	string name;
	string address;
	string VAT;
	vector<Parcs> parcs;
	vector<Customer> customers;

public:
	VacationParcs();
	VacationParcs(string name, string address, string VAT, vector<Parcs> parcs, vector<Customer> customers);
	~VacationParcs();
	void setName(string name);
	void setAddress(string address);
	void setVAT(string VAT);
	void setParcs(vector<Parcs> parcs);
	void setCustomers(vector<Customer> customers);
	string getName();
	string getAddress();
	string getVAT();
	vector<Parcs> getParcs();
	vector<Customer> getCustomers();
	void print();

	void addParc(Parcs parc);
	void addCustomer(Customer customer);
	void removeParc(Parcs parc);
	void removeCustomer(Customer customer);
	void printParcs();
	void printCustomers();
};

#endif // !VACATION_PARKS_H
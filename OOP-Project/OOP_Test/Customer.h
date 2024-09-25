#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <iostream>
using namespace std;

class Customer
{
private:
	string name;
	string address;
	string mail;
public:
	Customer();
	Customer(string name, string address, string mail);
	~Customer();
	void setName(string name);
	void setAddress(string address);
	void setMail(string mail);
	string getName();
	string getAddress();
	string getMail();
	void print();
};

#endif // !CUSTOMER_H
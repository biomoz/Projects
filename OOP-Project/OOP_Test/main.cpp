#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Customer.h"
#include "ParcServices.h"
#include "LuxuryLevel.h"
#include "Accommodations.h"
#include "HotelRoom.h"
#include "Cabin.h"
#include "Booking.h"
#include "Parcs.h"
#include "VacationParcs.h"
using namespace std;

int randomID();

void createCustomer(vector<Customer>* customers);
void changeCustomer(vector<Customer>* customers, string* mail, vector<Booking>* bookings);
void deleteCustomer(vector<Customer>* customers, vector <Booking>* bookings);
void listCustomers(vector<Customer>* customers);
void searchCustomer(vector<Customer>* customers);

void createBooking(vector<Booking>* bookings, vector<Customer>* customers, vector<Accommodations*>* accommodations, string mail);
void changeBooking(vector<Booking>* bookings, vector<Customer>* customers, vector<Accommodations*>* accommodations, string mail);
void deleteBooking(vector<Booking>* bookings, vector<Customer>* customers);
void listBooking(vector<Booking>* bookings, string mail);
void listAllBookings(vector<Booking>* bookings);
void searchBooking(vector<Booking>* bookings);

void createAccommodation(vector<Accommodations*>* accommodations);
void changeAccommodation(vector<Accommodations*>* accommodations, vector<Booking>* bookings);
void deleteAccommodation(vector<Accommodations*>* accommodations, vector<Parcs>* parcs, vector<Booking>* bookings);
void searchAccommodation(vector<Accommodations*>* accommodations);
void listAccommodations(vector<Accommodations*>* accommodations);

void createParc(vector<Parcs>* parcs, vector<Accommodations*>* accommodations);
void changeParc(vector<Parcs>* parcs, vector<Accommodations*>* accommodations, vector<Booking>* bookings);
void deleteParc(vector<Parcs>* parcs, vector<Accommodations*>* accommodations, vector<Booking>* bookings);
void listParcs(vector<Parcs>* parcs);


int main()
{
	vector <Customer> custos;
	vector <Accommodations*> accos;
	vector <Parcs> parcs;
	vector <Booking> bookings;
	
	string login;
	string vpname1 = "VP1", vatname1 = "VAT1", location1= "Belgium";
	
	ifstream customerFile("../data/customers.txt");
	if (customerFile.is_open())
	{
		string c1name, c1address, c1mail;
		getline(customerFile, c1name);
		getline(customerFile, c1address);
		customerFile >> c1mail;
		while (!customerFile.eof())
		{
			Customer cu1(c1name, c1address, c1mail);
			custos.push_back(cu1);
			customerFile.ignore();
			getline(customerFile, c1name);
			getline(customerFile, c1address);
			customerFile >> c1mail;
		}
		customerFile.close();
	}
	else
	{
		cout << "Unable to open file\n";
	}


	ifstream accomodationFile("../data/accommodations.txt");
	if (accomodationFile.is_open())
	{
		int ID2;
		int nrPeople2;
		int size2;
		bool bathroomWithBath2;
		bool BBQ2;
		bool surroundSystem2;
		bool breakfastService2;
		bool cleaningService2;
		string accommodationKind2;
		int bedrooms2;
		int floor2;
		string location2;
		int nrBeds2;
		bool childrenBed2;
		
		accomodationFile >> ID2 >> nrPeople2 >> size2 >> bathroomWithBath2 >> BBQ2 >> surroundSystem2 >> breakfastService2 >> cleaningService2 >> accommodationKind2;
		if (accommodationKind2 == "bungalow")
		{
			accomodationFile >> bedrooms2;
		}
		else if (accommodationKind2 == "hotel")
		{
			accomodationFile >> floor2;
			accomodationFile.ignore();
			getline(accomodationFile, location2);
			accomodationFile >> nrBeds2 >> childrenBed2;
		}
		while (!accomodationFile.eof())
		{
			if (accommodationKind2 == "bungalow")
			{
				LuxuryLevel ll2(BBQ2, surroundSystem2, breakfastService2, cleaningService2, accommodationKind2);
				Cabin* ca2 = new Cabin(ID2, nrPeople2, size2, bathroomWithBath2, ll2, bedrooms2);
				accos.push_back(ca2);
			}
			else if (accommodationKind2 == "hotel")
			{
				LuxuryLevel ll2(BBQ2, surroundSystem2, breakfastService2, cleaningService2, accommodationKind2);
				HotelRoom* hr2 = new HotelRoom(ID2, nrPeople2, size2, bathroomWithBath2, ll2, floor2, location2, nrBeds2, childrenBed2);
				accos.push_back(hr2);
			}
			accommodationKind2 = "";
			accomodationFile >> ID2 >> nrPeople2 >> size2 >> bathroomWithBath2 >> BBQ2 >> surroundSystem2 >> breakfastService2 >> cleaningService2 >> accommodationKind2;
			if (accommodationKind2 == "bungalow")
			{
				accomodationFile >> bedrooms2;
			}
			else if (accommodationKind2 == "hotel")
			{
			accomodationFile >> floor2;
			accomodationFile.ignore();
			getline(accomodationFile, location2);
			accomodationFile >> nrBeds2 >> childrenBed2;
			}
		}
		accomodationFile.close();
	}
	else
	{
		cout << "Unable to open file\n";
	}
	
	ifstream bookFile("../data/bookings.txt");
	if (bookFile.is_open())
	{
		vector<Accommodations*> accop3;
		int ID3;
		string name3, address3, mail3;
		int accsize3;
		int ID4;
		int nrPeople3;
		int size3;
		bool bathroomWithBath3;
		bool BBQ3;
		bool surroundSystem3;
		bool breakfastService3;
		bool cleaningService3;
		string accommodationKind3;
		int bedrooms3;
		int floor3;
		string location3;
		int nrBeds3;
		bool childrenBed3;
		bool activityPass3;
		bool sportsPass3;
		bool bicycleRent3;
		bool swimmingPass3;
		vector <Accommodations*> accop4;

		bookFile >> ID3;
		bookFile.ignore();
		getline(bookFile, name3);
		getline(bookFile, address3);
		bookFile >> mail3 >> accsize3;
		for (int i = 0; i < accsize3; i++)
		{
			bookFile >> ID4 >> nrPeople3 >> size3 >> bathroomWithBath3 >> BBQ3 >> surroundSystem3 >> breakfastService3 >> cleaningService3 >> accommodationKind3;
			if (accommodationKind3 == "bungalow")
			{
				bookFile >> bedrooms3;
				LuxuryLevel llt(BBQ3, surroundSystem3, breakfastService3, cleaningService3, accommodationKind3);
				Cabin* cat = new Cabin(ID4, nrPeople3, size3, bathroomWithBath3, llt, bedrooms3);
				accop4.push_back(cat);
			}
			else if (accommodationKind3 == "hotel")
			{
				bookFile >> floor3;
				bookFile.ignore();
				getline(bookFile, location3);
				bookFile >> nrBeds3 >> childrenBed3;
				LuxuryLevel llt(BBQ3, surroundSystem3, breakfastService3, cleaningService3, accommodationKind3);
				HotelRoom* hrt = new HotelRoom(ID4, nrPeople3, size3, bathroomWithBath3, llt, floor3, location3, nrBeds3, childrenBed3);
				accop4.push_back(hrt);
			}
			accommodationKind3 = "";
		}
		if (accsize3 != 0)
		{
			bookFile >> activityPass3 >> sportsPass3 >> bicycleRent3 >> swimmingPass3;
		}
		while (!bookFile.eof())
		{
			for (int i = 0; i < accsize3; i++)
			{
				if (accop4[i]->getLuxuryLevel().getAccommodationKind() == "bungalow")
				{
					Cabin* ca3 = dynamic_cast<Cabin*>(accop4[i]);
					accop3.push_back(ca3);
				}
				else if (accop4[i]->getLuxuryLevel().getAccommodationKind() == "hotel")
				{
					HotelRoom* hr3 = dynamic_cast<HotelRoom*>(accop4[i]);
					accop3.push_back(hr3);
				}
			}
			Customer c3(name3, address3, mail3);
			Booking b3(ID3, c3, accop3, activityPass3, sportsPass3, bicycleRent3, swimmingPass3);
			bookings.push_back(b3);
			accop4.clear();
			accop3.clear();
			accsize3 = 0;
			accommodationKind3 = "";
			bookFile >> ID3;
			bookFile.ignore();
			getline(bookFile, name3);
			getline(bookFile, address3);
			bookFile >> mail3 >> accsize3;
			for (int i = 0; i < accsize3; i++)
			{
				bookFile >> ID4 >> nrPeople3 >> size3 >> bathroomWithBath3 >> BBQ3 >> surroundSystem3 >> breakfastService3 >> cleaningService3 >> accommodationKind3;
				if (accommodationKind3 == "bungalow")
				{
					bookFile >> bedrooms3;
					LuxuryLevel llt(BBQ3, surroundSystem3, breakfastService3, cleaningService3, accommodationKind3);
					Cabin* cat = new Cabin(ID4, nrPeople3, size3, bathroomWithBath3, llt, bedrooms3);
					accop4.push_back(cat);
				}
				else if (accommodationKind3 == "hotel")
				{
					bookFile >> floor3;
					bookFile.ignore();
					getline(bookFile, location3);
					bookFile >> nrBeds3 >> childrenBed3;
					LuxuryLevel llt(BBQ3, surroundSystem3, breakfastService3, cleaningService3, accommodationKind3);
					HotelRoom* hrt = new HotelRoom(ID4, nrPeople3, size3, bathroomWithBath3, llt, floor3, location3, nrBeds3, childrenBed3);
					accop4.push_back(hrt);
				}
				accommodationKind3 = "";
			}
			if (accsize3 != 0)
			{
				bookFile >> activityPass3 >> sportsPass3 >> bicycleRent3 >> swimmingPass3;
			}
		}
		bookFile.close();
	}
	else
	{
		cout << "Unable to open file\n";
	}
	
	ifstream parcsFile("../data/parcs.txt");
	if (parcsFile.is_open())
	{
		string name5;
		string address5;
		ParcServices services5;
		bool subtropicSwimmingPool5;
		bool sportslnfrastructure5;
		bool bowlingAlley5;
		bool bicycleRent5;
		bool childrensParadise5;
		bool waterBikes5;
		int accsize5;
		vector<Accommodations*> accop5;
		int ID6;
		int nrPeople6;
		int size6;
		bool bathroomWithBath6;
		bool BBQ6;
		bool surroundSystem6;
		bool breakfastService6;
		bool cleaningService6;
		string accommodationKind6;
		int bedrooms6;
		int floor6;
		string location6;
		int nrBeds6;
		bool childrenBed6;
		bool activityPass6;
		bool sportsPass6;
		bool swimmingPass6;
		vector <Accommodations*> accop6;
		
		getline(parcsFile, name5);
		getline(parcsFile, address5);
		parcsFile >> subtropicSwimmingPool5 >> sportslnfrastructure5 >> bowlingAlley5 >> bicycleRent5 >> childrensParadise5 >> waterBikes5 >> accsize5;		
		for (int i = 0; i < accsize5; i++)
		{
			parcsFile >> ID6 >> nrPeople6 >> size6 >> bathroomWithBath6 >> BBQ6 >> surroundSystem6 >> breakfastService6 >> cleaningService6 >> accommodationKind6;
			if (accommodationKind6 == "bungalow")
			{
				parcsFile >> bedrooms6;
				LuxuryLevel llt(BBQ6, surroundSystem6, breakfastService6, cleaningService6, accommodationKind6);
				Cabin* cat = new Cabin(ID6, nrPeople6, size6, bathroomWithBath6, llt, bedrooms6);
				accop6.push_back(cat);
			}
			else if (accommodationKind6 == "hotel")
			{
				parcsFile >> floor6;
				parcsFile.ignore();
				getline(parcsFile, location6);
				parcsFile >> nrBeds6 >> childrenBed6;
				LuxuryLevel llt(BBQ6, surroundSystem6, breakfastService6, cleaningService6, accommodationKind6);
				HotelRoom* hrt = new HotelRoom(ID6, nrPeople6, size6, bathroomWithBath6, llt, floor6, location6, nrBeds6, childrenBed6);
				accop6.push_back(hrt);
			}
			accommodationKind6 = "";
		}
		while (!parcsFile.eof())
		{
			for (int i = 0; i < accsize5; i++)
			{
				if (accop6[i]->getLuxuryLevel().getAccommodationKind() == "bungalow")
				{
					Cabin* ca4 = dynamic_cast<Cabin*>(accop6[i]);
					accop5.push_back(ca4);
				}
				else if (accop6[i]->getLuxuryLevel().getAccommodationKind() == "hotel")
				{
					HotelRoom* hr4 = dynamic_cast<HotelRoom*>(accop6[i]);
					accop5.push_back(hr4);
				}
			}
			services5 = ParcServices(subtropicSwimmingPool5, sportslnfrastructure5, bowlingAlley5, bicycleRent5, childrensParadise5, waterBikes5);
			Parcs p5(name5, address5, services5, accop5);
			parcs.push_back(p5);
			accop6.clear();
			accop5.clear();
			accsize5 = 0;
			accommodationKind6 = "";
			
			parcsFile.ignore();
			getline(parcsFile, name5);
			getline(parcsFile, address5);
			parcsFile >> subtropicSwimmingPool5 >> sportslnfrastructure5 >> bowlingAlley5 >> bicycleRent5 >> childrensParadise5 >> waterBikes5 >> accsize5;
			for (int i = 0; i < accsize5; i++)
			{
				parcsFile >> ID6 >> nrPeople6 >> size6 >> bathroomWithBath6 >> BBQ6 >> surroundSystem6 >> breakfastService6 >> cleaningService6 >> accommodationKind6;
				if (accommodationKind6 == "bungalow")
				{
					parcsFile >> bedrooms6;
					LuxuryLevel llt(BBQ6, surroundSystem6, breakfastService6, cleaningService6, accommodationKind6);
					Cabin* cat = new Cabin(ID6, nrPeople6, size6, bathroomWithBath6, llt, bedrooms6);
					accop6.push_back(cat);
				}
				else if (accommodationKind6 == "hotel")
				{
					parcsFile >> floor6;
					parcsFile.ignore();
					getline(parcsFile, location6);
					parcsFile >> nrBeds6 >> childrenBed6;
					LuxuryLevel llt(BBQ6, surroundSystem6, breakfastService6, cleaningService6, accommodationKind6);
					HotelRoom* hrt = new HotelRoom(ID6, nrPeople6, size6, bathroomWithBath6, llt, floor6, location6, nrBeds6, childrenBed6);
					accop6.push_back(hrt);
				}
				accommodationKind6 = "";
			}
		}
		parcsFile.close();
	}
	else
	{
		cout << "Unable to open file\n";
	}
	
	VacationParcs vp(vpname1, location1, vatname1, parcs, custos);
	
	string mail;

	cout << "Login or Register: " << endl;
	cout << "1. Customer" << endl;
	cout << "2. Employee" << endl;
	cout << "3. Owner" << endl;
	cout << "4. Register" << endl;
	cout << "5. Exit" << endl;
	cin >> login;

	while (login != "5")
	{
		if (login == "1")
		{
			cout << "Welcome Customer" << endl;
			cout << "Please enter your mail: " << endl;
			cin >> mail;
			int found = 0;

			for (int i = 0; i < custos.size(); i++)
			{
				if (mail == custos[i].getMail())
				{
					found = 1;
					int choice;
					cout << "1. Create Booking" << endl;
					cout << "2. Change Booking" << endl;
					cout << "3. Search Accommodation" << endl;
					cout << "4. Change Customer" << endl;
					cout << "5. Exit" << endl;
					cin >> choice;

					while (choice != 5)
					{
						if (choice == 1)
						{
							createBooking(&bookings, &custos, &accos, mail);
						}
						else if (choice == 2)
						{
							changeBooking(&bookings, &custos, &accos, mail);
						}
						else if (choice == 3)
						{
							searchAccommodation(&accos);
						}
						else if (choice == 4)
						{
							changeCustomer(&custos, &mail, &bookings);
							
						}
						cout << "1. Create Booking" << endl;
						cout << "2. Change Booking" << endl;
						cout << "3. Search Accommodation" << endl;
						cout << "4. Change Customer Info" << endl;
						cout << "5. Exit" << endl;
						cin >> choice;
					}
					if (choice == 5)
					{
						cout << "Customer logged off" << endl;
					}
				}
			}
			if (found == 0)
			{
				cout << "Customer not found" << endl;
			}
		}
		else if (login == "2")
		{
			int choice;
			cout << "Welcome Employee" << endl;
			cout << "1. Delete Booking" << endl;
			cout << "2. Search Booking" << endl;
			cout << "3. Change Accommodation" << endl;
			cout << "4. Search Accommodation" << endl;
			cout << "5. Delete Customer" << endl;
			cout << "6. Search Customer" << endl;
			cout << "7. Exit" << endl;
			cin >> choice;

			while (choice != 7)
			{
				if (choice == 1)
				{
					deleteBooking(&bookings, &custos);
				}
				else if (choice == 2)
				{
					searchBooking(&bookings);
				}
				else if (choice == 3)
				{
					changeAccommodation(&accos, &bookings);
				}
				else if (choice == 4)
				{
					searchAccommodation(&accos);
				}
				else if (choice == 5)
				{
					deleteCustomer(&custos, &bookings);
				}
				else if (choice == 6)
				{
					searchCustomer(&custos);
				}
				cout << "Welcome Employee" << endl;
				cout << "1. Delete Booking" << endl;
				cout << "2. Search Booking" << endl;
				cout << "3. Change Accommodation" << endl;
				cout << "4. Search Accommodation" << endl;
				cout << "5. Delete Customer" << endl;
				cout << "6. Search Customer" << endl;
				cout << "7. Exit" << endl;
				cin >> choice;
			}
			if (choice == 7)
			{
				cout << "Employee logged off" << endl;
			}
		}
		else if (login == "3")
		{
			int choice;
			cout << "Welcome Owner" << endl;
			cout << "1. Create a Parc" << endl;
			cout << "2. Change Parc" << endl;
			cout << "3. Delete Parc" << endl;
			cout << "4. Create Accommodation" << endl;
			cout << "5. Change Accommodation" << endl;
			cout << "6. Delete Accommodation" << endl;
			cout << "7. Exit" << endl;

			cin >> choice;

			while (choice != 7)
			{
				if (choice == 1)
				{
					createParc(&parcs, &accos);
				}
				else if (choice == 2)
				{
					changeParc(&parcs, &accos, &bookings);
				}
				else if (choice == 3)
				{
					deleteParc(&parcs, &accos, &bookings);
				}
				else if (choice == 4)
				{
					createAccommodation(&accos);
				}
				else if (choice == 5)
				{
					changeAccommodation(&accos, &bookings);
				}
				else if (choice == 6)
				{
					deleteAccommodation(&accos, &parcs, &bookings);
				}
				cout << "Welcome Owner" << endl;
				cout << "1. Create a Parc" << endl;
				cout << "2. Change Parc" << endl;
				cout << "3. Delete Parc" << endl;
				cout << "4. Create Accommodation" << endl;
				cout << "5. Change Accommodation" << endl;
				cout << "6. Delete Accommodation" << endl;
				cout << "7. Exit" << endl;
				cin >> choice;
			}
			if (choice == 7)
			{
				cout << "Owner logged off" << endl;
			}
		}
		else if (login == "4")
		{
			cout << "Welcome to Registeration" << endl;
			createCustomer(&custos);
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		cout << "Login or Register: " << endl;
		cout << "1. Customer" << endl;
		cout << "2. Employee" << endl;
		cout << "3. Owner" << endl;
		cout << "4. Register" << endl;
		cout << "5. Exit" << endl;
		cin >> login;
	}
	if (login == "5")
	{
		cout << "Goodbye" << endl;
	}

	ofstream custoFile;
	custoFile.open("../data/customers.txt");
	for (int i = 0; i < custos.size(); i++)
	{
		custoFile << custos[i].getName() << endl;
		custoFile << custos[i].getAddress() << endl;
		custoFile << custos[i].getMail() << endl;
	}
	custoFile.close();

	ofstream bookingFile;
	bookingFile.open("../data/bookings.txt");
	for (int i = 0; i < bookings.size(); i++)
	{
		bookingFile << bookings[i].getID() << endl;
		bookingFile << bookings[i].getCustomer().getName() << endl;
		bookingFile << bookings[i].getCustomer().getAddress() << endl;
		bookingFile << bookings[i].getCustomer().getMail() << endl;
		bookingFile << bookings[i].getAccommodations().size() << endl;
		for (int j = 0; j < bookings[i].getAccommodations().size(); j++)
		{
			if (bookings[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() == "bungalow")
			{
				bookingFile << bookings[i].getAccommodations().at(j)->getID() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getNrPeople() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getSize() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getBathroomWithBath() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getBBQ() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getSurroundSystem() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getBreakfastService() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getCleaningService() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getBedrooms() << endl;
			}
			else if (bookings[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() == "hotel")
			{
				bookingFile << bookings[i].getAccommodations().at(j)->getID() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getNrPeople() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getSize() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getBathroomWithBath() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getBBQ() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getSurroundSystem() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getBreakfastService() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getCleaningService() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getFloor() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getLocation() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getNrBeds() << endl;
				bookingFile << bookings[i].getAccommodations().at(j)->getChildrenBed() << endl;
			}
		}
		bookingFile << bookings[i].getActivityPass() << endl;
		bookingFile << bookings[i].getSportsPass() << endl;
		bookingFile << bookings[i].getBicycleRent() << endl;
		bookingFile << bookings[i].getSwimmingPass() << endl;
	}
	bookingFile.close();


	ofstream accomFile;
	accomFile.open("../data/accommodations.txt");
	for (int i = 0; i < accos.size(); i++)
	{
		if (accos[i]->getLuxuryLevel().getAccommodationKind() == "bungalow")
		{
			accomFile << accos[i]->getID() << endl;
			accomFile << accos[i]->getNrPeople() << endl;
			accomFile << accos[i]->getSize() << endl;
			accomFile << accos[i]->getBathroomWithBath() << endl;
			accomFile << accos[i]->getLuxuryLevel().getBBQ() << endl;
			accomFile << accos[i]->getLuxuryLevel().getSurroundSystem() << endl;
			accomFile << accos[i]->getLuxuryLevel().getBreakfastService() << endl;
			accomFile << accos[i]->getLuxuryLevel().getCleaningService() << endl;
			accomFile << accos[i]->getLuxuryLevel().getAccommodationKind() << endl;
			accomFile << accos[i]->getBedrooms() << endl;
		}
		else if (accos[i]->getLuxuryLevel().getAccommodationKind() == "hotel")
		{
			accomFile << accos[i]->getID() << endl;
			accomFile << accos[i]->getNrPeople() << endl;
			accomFile << accos[i]->getSize() << endl;
			accomFile << accos[i]->getBathroomWithBath() << endl;
			accomFile << accos[i]->getLuxuryLevel().getBBQ() << endl;
			accomFile << accos[i]->getLuxuryLevel().getSurroundSystem() << endl;
			accomFile << accos[i]->getLuxuryLevel().getBreakfastService() << endl;
			accomFile << accos[i]->getLuxuryLevel().getCleaningService() << endl;
			accomFile << accos[i]->getLuxuryLevel().getAccommodationKind() << endl;
			accomFile << accos[i]->getFloor() << endl;
			accomFile << accos[i]->getLocation() << endl;
			accomFile << accos[i]->getNrBeds() << endl;
			accomFile << accos[i]->getChildrenBed() << endl;
		}
	}
	accomFile.close();


	ofstream parcFile;
	parcFile.open("../data/parcs.txt");
	for (int i = 0; i < parcs.size(); i++)
	{
		parcFile << parcs[i].getName() << endl;
		parcFile << parcs[i].getAddress() << endl;
		parcFile << parcs[i].getServices().getSubtropicSwimmingPool() << endl;
		parcFile << parcs[i].getServices().getSportslnfrastructure() << endl;
		parcFile << parcs[i].getServices().getBowlingAlley() << endl;
		parcFile << parcs[i].getServices().getBicycleRent() << endl;
		parcFile << parcs[i].getServices().getChildrensParadise() << endl;
		parcFile << parcs[i].getServices().getWaterBikes() << endl;
		parcFile << parcs[i].getAccommodations().size() << endl;
		for (int j = 0; j < parcs[i].getAccommodations().size(); j++)
		{
			if (parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() == "bungalow")
			{
				parcFile << parcs[i].getAccommodations().at(j)->getID() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getNrPeople() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getSize() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getBathroomWithBath() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBBQ() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getSurroundSystem() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBreakfastService() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getCleaningService() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getBedrooms() << endl;
			}
			else if (parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() == "hotel")
			{
				parcFile << parcs[i].getAccommodations().at(j)->getID() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getNrPeople() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getSize() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getBathroomWithBath() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBBQ() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getSurroundSystem() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBreakfastService() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getCleaningService() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getFloor() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getLocation() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getNrBeds() << endl;
				parcFile << parcs[i].getAccommodations().at(j)->getChildrenBed() << endl;
			}
		}
	}
	parcFile.close();

	ofstream vpFile;
	vpFile.open("../data/vp.txt");
	vpFile << vp.getName() << endl;
	vpFile << vp.getAddress() << endl;
	vpFile << vp.getVAT() << endl;
	vpFile << vp.getParcs().size() << endl;
	for (int i = 0; i < parcs.size(); i++)
	{
		vpFile << parcs[i].getName() << endl;
		vpFile << parcs[i].getAddress() << endl;
		vpFile << parcs[i].getServices().getSubtropicSwimmingPool() << endl;
		vpFile << parcs[i].getServices().getSportslnfrastructure() << endl;
		vpFile << parcs[i].getServices().getBowlingAlley() << endl;
		vpFile << parcs[i].getServices().getBicycleRent() << endl;
		vpFile << parcs[i].getServices().getChildrensParadise() << endl;
		vpFile << parcs[i].getServices().getWaterBikes() << endl;
		vpFile << parcs[i].getAccommodations().size() << endl;
		for (int j = 0; j < parcs[i].getAccommodations().size(); j++)
		{
			if (parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() == "bungalow")
			{
				vpFile << parcs[i].getAccommodations().at(j)->getID() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getNrPeople() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getSize() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getBathroomWithBath() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBBQ() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getSurroundSystem() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBreakfastService() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getCleaningService() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getBedrooms() << endl;
			}
			else if (parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() == "hotel")
			{
				vpFile << parcs[i].getAccommodations().at(j)->getID() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getNrPeople() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getSize() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getBathroomWithBath() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBBQ() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getSurroundSystem() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getBreakfastService() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getCleaningService() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLuxuryLevel().getAccommodationKind() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getFloor() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getLocation() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getNrBeds() << endl;
				vpFile << parcs[i].getAccommodations().at(j)->getChildrenBed() << endl;
			}
		}
	}
	vpFile << vp.getCustomers().size() << endl;
	for (int k = 0; k < custos.size(); k++)
	{
		vpFile << custos[k].getName() << endl;
		vpFile << custos[k].getAddress() << endl;
		vpFile << custos[k].getMail() << endl;
	}		
	vpFile.close();
	
	return 0;
}

int randomID()
{
	srand(time(NULL));
	int id = rand() % 1000 + 1;
	return id;
}
	
void createCustomer(vector<Customer>* customers)
{
	string name, address, mail;
	cout << "Please enter your name: " << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Please enter your address: " << endl;
	getline(cin, address);
	cout << "Please enter your mail: " << endl;
	cin >> mail;
	if (customers->size() == 0)
	{
		Customer cu(name, address, mail);
		customers->push_back(cu);
		cout << "Customer created" << endl;
	}
	else
	{
		int found = 0;
		for (int i = 0; i < customers->size(); i++)
		{
			if (customers->at(i).getMail() == mail)
			{
				found = 1;
				cout << "You are already registered!" << endl;
				break;
			}
		}
		if (found == 0)
		{
			Customer cu(name, address, mail);
			customers->push_back(cu);
			cout << "Customer created" << endl;
		}
	}
}
	
void changeCustomer(vector<Customer>* customers, string* mail, vector<Booking>* bookings)
{
	for (int i = 0; i < customers->size(); i++)
	{
		if (*mail == customers->at(i).getMail())
		{
			int choice;
			cout << "What do you want to change?" << endl;
			cout << "1. Change Name" << endl;
			cout << "2. Change Address" << endl;
			cout << "3. Change Mail" << endl;
			cout << "4. Exit" << endl;
			cin >> choice;

			while (choice != 4) 
			{
				if (choice == 1)
				{
					string name;
					cout << "Please enter your new name: " << endl;
					cin.ignore();
					getline(cin, name);
					for (int j = 0; j < bookings->size(); j++)
					{
						if (bookings->at(j).getCustomer().getMail() == *mail)
						{
							bookings->at(j).setCustName(name);
						}
					}
					customers->at(i).setName(name);
					cout << "Your new name is: " << customers->at(i).getName() << endl;
				}
				else if (choice == 2)
				{
					string address;
					cout << "Please enter your new address: " << endl;
					cin.ignore();
					getline(cin, address);
					for (int j = 0; j < bookings->size(); j++)
					{
						if (bookings->at(j).getCustomer().getMail() == *mail)
						{
							bookings->at(j).setCustAddress(address);
						}
					}
					customers->at(i).setAddress(address);
					cout << "Your new address is: " << customers->at(i).getAddress() << endl;
				}
				else if (choice == 3)
				{
					string cmail;
					int found =0;
					cout << "Please enter your new mail: " << endl;
					cin >> cmail;
					for (int i = 0; i < customers->size(); i++)
					{
						if (cmail == customers->at(i).getMail())
						{
							found = 1;
							cout << "This mail is already registered!" << endl;
							break;
						}
					}
					if (found == 0)
					{
						for (int j = 0; j < bookings->size(); j++)
						{
							if (bookings->at(j).getCustomer().getMail() == *mail)
							{
								bookings->at(j).setCustMail(cmail);
							}
						}
						customers->at(i).setMail(cmail);
						*mail = customers->at(i).getMail();
						cout << "Your new mail is: " << customers->at(i).getMail() << endl;
					}
				}
				else
				{
					cout << "Invalid input" << endl;
				}
				cout << "What do you want to change?" << endl;
				cout << "1. Change Name" << endl;
				cout << "2. Change Address" << endl;
				cout << "3. Change Mail" << endl;
				cout << "4. Exit" << endl;
				cin >> choice;
			}
			if (choice == 4)
			{
				cout << "Exiting..." << endl;
				customers->at(i).print();
			}
		}
	}
	
}

void deleteCustomer(vector<Customer>* customers, vector <Booking>* bookings)
{
	string mail;
	cout << "Please enter customer's mail: " << endl;
	cin >> mail;
	int found = 0;
	for (int i = 0; i < customers->size(); i++)
	{
		if (mail == customers->at(i).getMail())
		{
			found = 1;
			cout << "Customer found" << endl;
			for (int j = 0; j < bookings->size(); j++)
			{
				if (mail == bookings->at(j).getCustomer().getMail())
				{
					cout << "Booking " << bookings->at(j).getID() << " deleted" << endl;
					bookings->erase(bookings->begin() + j);
					j--;
				}
			}
			customers->erase(customers->begin() + i);
			cout << "Customer deleted" << endl;	
		}
	}
	if (found == 0)
	{
		cout << "Customer not found" << endl;
	}
}

void listCustomers(vector<Customer>* customers)
{
	for (int i = 0; i < customers->size(); i++)
	{
		customers->at(i).print();
		cout << endl;
	}
}

void searchCustomer(vector<Customer>* customers)
{
	int choice;
	cout << "1. Search by mail" << endl;
	cout << "2. List Customers" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;

	while (choice != 3)
	{
		if (choice == 1)
		{
			string mail;
			cout << "Please enter customer's mail: " << endl;
			cin >> mail;
			int found = 0;
			for (int i = 0; i < customers->size(); i++)
			{
				if (mail == customers->at(i).getMail())
				{
					found = 1;
					cout << "Customer found" << endl;
					customers->at(i).print();
					cout << endl;
				}
			}
			if (found == 0)
			{
				cout << "Customer not found" << endl;
			}
		}
		else if (choice == 2)
		{
			listCustomers(customers);
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		cout << "1. Search by mail" << endl;
		cout << "2. List Customers" << endl;
		cout << "3. Exit" << endl;
		cin >> choice;
	}
	if (choice == 3)
	{
		cout << "Search Customer exited" << endl;
	}
}

void createBooking(vector<Booking>* bookings, vector<Customer>* customers, vector<Accommodations*>* accos, string mail)
{
	Customer custo;
	vector <Accommodations*> acco;
	int afound = 0;
	int cfound = 0;
	for (int i = 0; i < customers->size(); i++)
	{
		if (mail == customers->at(i).getMail())
		{
			cfound = 1;
			custo = customers->at(i);
			int id;
			int amount;
			cout << "How many accommodations do you want to book?" << endl;
			cin >> amount;
			if (amount > 3 || amount < 1)
			{
				cout << "Invalid input" << endl;
			}
			else
			{
				for (int j = 0; j < amount; j++)
				{
					afound = 0;
					cout << "Please enter the id of the accommodation you want to book: " << endl;
					cin >> id;
					for (int k = 0; k < accos->size(); k++)
					{
						if (id == accos->at(k)->getID())
						{
							afound = 1;
							acco.push_back(accos->at(k));
						}
					}
					if (afound == 0)
					{
						cout << "Accommodation not found" << endl;
						j--;
					}
					if (afound == 1)
					{
						bool bike, apass, sopass, swpass;
						cout << "Do you want activity pass (1 for yes, 0 for no): " << endl;
						cin >> apass;
						cout << "Do you want sports pass (1 for yes, 0 for no): " << endl;
						cin >> sopass;
						cout << "Do you want to rent bicycle (1 for yes, 0 for no): " << endl;
						cin >> bike;
						cout << "Do you want swimming pass (1 for yes, 0 for no): " << endl;
						cin >> swpass;

						int bid = randomID();
						for (int i = 0; i < bookings->size(); i++)
						{
							if (bid == bookings->at(i).getID())
							{
								bid = randomID();
							}
						}
						Booking book(bid, custo, acco, apass, sopass, bike, swpass);
						bookings->push_back(book);
					}
				}
				cout << "Booking created" << endl;
				bookings->at(bookings->size() - 1).print();
			}

		}
	}
	if (cfound == 0)
	{
		cout << "Customer not found" << endl;
	}
}

void deleteBooking(vector<Booking>* bookings, vector<Customer>* customers)
{
	int id;
	string mail;
	cout << "Please enter customer's mail: " << endl;
	cin >> mail;
	cout << "Please enter booking's ID: " << endl;
	cin >> id;
	int found = 0;
	for (int i = 0; i < bookings->size(); i++)
	{
		if (mail == bookings->at(i).getCustomer().getMail())
		{
			if (id == bookings->at(i).getID())
			{
				found = 1;
				cout << "Booking found" << endl;
				bookings->erase(bookings->begin() + i);
				cout << "Booking deleted" << endl;
			}
		}
	}
	if (found == 0)
	{
		cout << "Booking not found" << endl;
	}
}


void changeBooking(vector<Booking>* bookings, vector<Customer>* customers, vector<Accommodations*>* accos, string mail)
{
	int choice;
	cout << "1. Select by ID" << endl;
	cout << "2. List Booking" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;
	while (choice != 3)
	{
		if (choice == 1)
		{
			int aid;
			int afound = 0;
			int rid;
			int rfound = 0;
			int id, index;
			cout << "Please enter booking's ID: " << endl;
			cin >> id;
			int found = 0;
			for (int i = 0; i < bookings->size(); i++)
			{
				if (id == bookings->at(i).getID())
				{
					if (mail == bookings->at(i).getCustomer().getMail())
					{
						found = 1;
						index = i;
						cout << "Booking found" << endl;
						int choice;
						cout << "1. Add Accommodation" << endl;
						cout << "2. Remove Accommodation" << endl;
						cout << "3. Change Activity Pass" << endl;
						cout << "4. Change Sports Pass" << endl;
						cout << "5. Change Bicycle" << endl;
						cout << "6. Change Swimming Pass" << endl;
						cout << "7. Exit" << endl;
						cin >> choice;
						while (choice != 7)
						{
							if (choice == 1)
							{
								if (bookings->at(i).getAccommodations().size() < 3)
								{
									cout << "Please enter accommodation's ID: " << endl;
									cin >> aid;
									for (int l = 0; l < bookings->at(i).getAccommodations().size(); l++)
									{
										afound = 0;
										if (aid == bookings->at(i).getAccommodations().at(l)->getID())
										{
											afound = 1;
											cout << "Accommodation already added" << endl;
											break;
										}
									}
									if (afound == 0)
									{
										for (int j = 0; j < accos->size(); j++)
										{
											if (aid == accos->at(j)->getID())
											{
												afound = 1;
												bookings->at(i).addAccommodation(accos->at(j));
												cout << "Accommodation added" << endl;
												break;
											}
										}
									}
									if (afound == 0)
									{
										cout << "Accommodation not found" << endl;
									}
								}
								else
								{
									cout << "You can't add more than 3 accommodations" << endl;
								}
							}
							else if (choice == 2)
							{
								
								cout << "Please enter the id of the accommodation you want to remove: " << endl;
								cin >> rid;
								for (int k = 0; k < accos->size(); k++)
								{
									if (rid == accos->at(k)->getID())
									{
										rfound = 1;
										for (int l = 0; l < bookings->at(i).getAccommodations().size(); l++)
										{
											if (rid == bookings->at(i).getAccommodations().at(l)->getID())
											{
												bookings->at(i).deleteAccommodation(l);
												cout << "Accommodation removed" << endl;
												break;
											}
											else if (l == bookings->at(i).getAccommodations().size() - 1)
											{
												cout << "Accommodation not found" << endl;
											}
										}
									}		
								}
								if (rfound == 0)
								{
									cout << "Accommodation not found" << endl;
								}
							}
							else if (choice == 3)
							{
								bool apass;
								cout << "Do you want activity pass (1 for yes, 0 for no): " << endl;
								cin >> apass;
								bookings->at(i).setActivityPass(apass);
								cout << "Activity pass changed" << endl;
							}
							else if (choice == 4)
							{
								bool sopass;
								cout << "Do you want sports pass (1 for yes, 0 for no): " << endl;
								cin >> sopass;
								bookings->at(i).setSportsPass(sopass);
								cout << "Sports pass changed" << endl;
							}
							else if (choice == 5)
							{
								bool bike;
								cout << "Do you want to rent bicycle (1 for yes, 0 for no): " << endl;
								cin >> bike;
								bookings->at(i).setBicycleRent(bike);
								cout << "Bicycle rent changed" << endl;
							}
							else if (choice == 6)
							{
								bool swpass;
								cout << "Do you want swimming pass (1 for yes, 0 for no): " << endl;
								cin >> swpass;
								bookings->at(i).setSwimmingPass(swpass);
								cout << "Swimming pass changed" << endl;
							}
							else
							{
								cout << "Invalid input" << endl;
							}
							cout << "1. Add Accommodation" << endl;
							cout << "2. Remove Accommodation" << endl;
							cout << "3. Change Activity Pass" << endl;
							cout << "4. Change Sports Pass" << endl;
							cout << "5. Change Bicycle" << endl;
							cout << "6. Change Swimming Pass" << endl;
							cout << "7. Exit" << endl;
							cin >> choice;
						}
						if (choice == 7)
						{
							cout << "Exiting..." << endl;
						}
					}

				}
			}
			if (found == 0)
			{
				cout << "Booking not found" << endl;
			}
			if (found == 1)
			{
				cout << "Booking changed" << endl;
				bookings->at(index).print();
			}
		}
		else if (choice == 2)
		{
			listBooking(bookings, mail);
		}
		cout << "1. Select by ID" << endl;
		cout << "2. List Booking" << endl;
		cout << "3. Exit" << endl;
		cin >> choice;
	}
	if (choice == 3)
	{
		cout << "Changing Booking exited" << endl;
	}
}

void listBooking(vector<Booking>* bookings, string mail)
{
	for (int i = 0; i < bookings->size(); i++)
	{
		if (bookings->at(i).getCustomer().getMail() == mail)
		{
			bookings->at(i).print();
			cout << endl;
		}
	}
}

void listAllBookings(vector<Booking>* bookings)
{
	for (int i = 0; i < bookings->size(); i++)
	{
		bookings->at(i).print();
		cout << endl;
	}
}

void searchBooking(vector<Booking>* bookings)
{
	int choice;
	cout << "1. Search by ID" << endl;
	cout << "2. List All Bookings" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;

	while (choice != 3)
	{
		if (choice == 1)
		{
			int id;
			cout << "Please enter Booking's ID: " << endl;
			cin >> id;
			int found = 0;
			for (int i = 0; i < bookings->size(); i++)
			{
				if (id == bookings->at(i).getID())
				{
					found = 1;
					cout << "Accommodation found" << endl;
					bookings->at(i).print();
				}
			}
			if (found == 0)
			{
				cout << "Accommodation not found" << endl;
			}
		}
		else if (choice == 2)
		{
			listAllBookings(bookings);
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		cout << "1. Search by ID" << endl;
		cout << "2. List All Bookings" << endl;
		cout << "3. Exit" << endl;
		cin >> choice;
	}
	if (choice == 3)
	{
		cout << "Search Booking exited" << endl;
	}
}

void createAccommodation(vector<Accommodations*>* accos)
{
	int choice;
	cout << "Please enter your choice: " << endl;
	cout << "1. Create bungalow" << endl;
	cout << "2. Create hotel" << endl;
	cin >> choice;
	if (choice == 1)
	{
		int beds;
		int people;
		int size;
		bool bath;
		bool bbq;
		bool surround;
		bool breakfast;
		bool cleaning;
		string kind;
		cout << "Please enter number of beds: " << endl;
		cin >> beds;
		cout << "Please enter number of people: " << endl;
		cin >> people;
		cout << "Please enter size: " << endl;
		cin >> size;
		cout << "Please enter bathroom with bath option (1/0): " << endl;
		cin >> bath;
		cout << "Please enter BBQ option (1/0): " << endl;
		cin >> bbq;
		cout << "Please enter surround system option (1/0): " << endl;
		cin >> surround;
		cout << "Please enter breakfast service option (1/0): " << endl;
		cin >> breakfast;
		cout << "Please enter cleaning service option (1/0): " << endl;
		cin >> cleaning;
		kind = "bungalow";
		int id = randomID();
		for (int i = 0; i < accos->size(); i++)
		{
			if (accos->at(i)->getID() == id)
			{
				id = randomID();
			}
		}
		LuxuryLevel ll(bbq, surround, breakfast, cleaning, kind);
		Cabin* bungalow = new Cabin(id, people, size, bath, ll, beds);
		bungalow->setID(randomID());
		accos->push_back(bungalow);
		cout << "Bungalow created" << endl;
		bungalow->print();
	}
	else if (choice == 2)
	{
		int floor;
		string location;
		int beds;
		bool children;
		int people;
		int size;
		bool bath;
		bool bbq;
		bool surround;
		bool breakfast;
		bool cleaning;
		string kind;
		cout << "Please enter floor: " << endl;
		cin >> floor;
		cout << "Please enter location: " << endl;
		cin.ignore();
		getline(cin, location);
		cout << "Please enter number of beds: " << endl;
		cin >> beds;
		cout << "Please enter children bed option (1/0): " << endl;
		cin >> children;
		cout << "Please enter number of people: " << endl;
		cin >> people;
		cout << "Please enter size: " << endl;
		cin >> size;
		cout << "Please enter bathroom with bath option (1/0): " << endl;
		cin >> bath;
		cout << "Please enter BBQ option (1/0): " << endl;
		cin >> bbq;
		cout << "Please enter surround system option (1/0): " << endl;
		cin >> surround;
		cout << "Please enter breakfast service option (1/0): " << endl;
		cin >> breakfast;
		cout << "Please enter cleaning service option (1/0): " << endl;
		cin >> cleaning;
		kind = "hotel";
		int id = randomID();
		for (int i = 0; i < accos->size(); i++)
		{
			if (accos->at(i)->getID() == id)
			{
				id = randomID();
			}
		}
		LuxuryLevel ll(bbq, surround, breakfast, cleaning, kind);
		HotelRoom* hotel = new HotelRoom(id, people, size, bath, ll, floor, location, beds, children);
		hotel->setID(randomID());
		accos->push_back(hotel);
		cout << "Hotel created" << endl;
		hotel->print();
	}
	else
	{
		cout << "Wrong choice" << endl;
	}
}


void deleteAccommodation(vector<Accommodations*>* accos, vector<Parcs>* parcs, vector<Booking>* bookings)
{
	int id;
	cout << "Please enter accommodation's ID: " << endl;
	cin >> id;
	int found = 0;
	for (int i = 0; i < accos->size(); i++)
	{
		if (id == accos->at(i)->getID())
		{
			found = 1;
			cout << "Accommodation found" << endl;
			for (int j = 0; j < parcs->size(); j++)
			{
				for (int k = 0; k < parcs->at(j).getAccommodations().size(); k++)
				{
					if (id == parcs->at(j).getAccommodations().at(k)->getID())
					{
						parcs->at(j).deleteAccommodation(k);
					}
				}
			}
			for (int j = 0; j < bookings->size(); j++)
			{
				for (int k = 0; k < bookings->at(j).getAccommodations().size(); k++)
				{
					if (id == bookings->at(j).getAccommodations().at(k)->getID())
					{
						bookings->at(j).deleteAccommodation(k);
					}
				}
			}
			delete accos->at(i);
			accos->erase(accos->begin() + i);
			cout << "Accommodation deleted" << endl;
		}
	}
	if (found == 0)
	{
		cout << "Accommodation not found" << endl;
	}
}

void changeAccommodation(vector<Accommodations*>* accos, vector<Booking>* bookings) 
{
	int choice; 
	cout << "1. Select by ID" << endl;
	cout << "2. List Accommodations" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;
	while (choice != 3)
	{
		if (choice == 1)
		{
			int index;
			int id;
			cout << "Please enter accommodation's ID: " << endl;
			cin >> id;
			int found = 0;
			for (int i = 0; i < accos->size(); i++)
			{
				if (id == accos->at(i)->getID())
				{
					if (accos->at(i)->getLuxuryLevel().getAccommodationKind() == "bungalow")
					{
						found = 1;
						index = i;
						cout << "Accommodation found" << endl;
						accos->at(i)->print();
						int choice;
						cout << "1. Change number of beds" << endl;
						cout << "2. Change number of people" << endl;
						cout << "3. Change size" << endl;
						cout << "4. Change bathroom with bath option (1/0)" << endl;
						cout << "5. Change BBQ option (1/0)" << endl;
						cout << "6. Change surround system option (1/0)" << endl;
						cout << "7. Change breakfast service option (1/0)" << endl;
						cout << "8. Change cleaning service option (1/0)" << endl;
						cout << "9. Exit" << endl;
						cin >> choice;

						while (choice != 9)
						{
							if (choice == 1)
							{
								int beds;
								cout << "Please enter new number of beds: " << endl;
								cin >> beds;
								accos->at(i)->setBedrooms(beds);
								cout << "Number of beds changed" << endl;
							}
							else if (choice == 2)
							{
								int people;
								cout << "Please enter new number of people: " << endl;
								cin >> people;
								accos->at(i)->setNrPeople(people);
								cout << "Number of people changed" << endl;
							}
							else if (choice == 3)
							{
								int size;
								cout << "Please enter new size: " << endl;
								cin >> size;
								accos->at(i)->setSize(size);
								cout << "Size changed" << endl;
							}
							else if (choice == 4)
							{
								bool bath;
								cout << "Please enter new bathroom with bath option (1/0): " << endl;
								cin >> bath;
								accos->at(i)->setBathroomWithBath(bath);
								cout << "Bathroom with bath option changed" << endl;
							}
							else if (choice == 5)
							{
								bool bbq;
								cout << "Please enter new BBQ option (1/0): " << endl;
								cin >> bbq;
								accos->at(i)->setLLBBQ(bbq);
								cout << "BBQ option changed" << endl;
							}
							else if (choice == 6)
							{
								bool surround;
								cout << "Please enter new surround system option (1/0): " << endl;
								cin >> surround;
								accos->at(i)->setLLSurroundSystem(surround);
								cout << "Surround system option changed" << endl;
							}
							else if (choice == 7)
							{
								bool breakfast;
								cout << "Please enter new breakfast service option (1/0): " << endl;
								cin >> breakfast;
								accos->at(i)->setLLBreakfastService(breakfast);
								cout << "Breakfast service option changed" << endl;
							}
							else if (choice == 8)
							{
								bool cleaning;
								cout << "Please enter new cleaning service option (1/0): " << endl;
								cin >> cleaning;
								accos->at(i)->setLLCleaningService(cleaning);
								cout << "Cleaning service option changed" << endl;
							}
							
							else
							{
								cout << "Wrong choice" << endl;
							}

							cout << "1. Change number of beds" << endl;
							cout << "2. Change number of people" << endl;
							cout << "3. Change size" << endl;
							cout << "4. Change bathroom with bath option (1/0)" << endl;
							cout << "5. Change BBQ option (1/0)" << endl;
							cout << "6. Change surround system option (1/0)" << endl;
							cout << "7. Change breakfast service option (1/0)" << endl;
							cout << "8. Change cleaning service option (1/0)" << endl;
							cout << "9. Exit" << endl;
							cin >> choice;
						}
						if (choice == 9)
						{
							cout << "Exiting..." << endl;
							for (int k = 0; k < bookings->size(); k++)
							{
								for (int j = 0; j < bookings->at(k).getAccommodations().size(); j++)
								{
									if (bookings->at(k).getAccommodations().at(j)->getID() == accos->at(i)->getID())
									{
										bookings->at(k).deleteAccommodation(j);
										bookings->at(k).addAccommodation(accos->at(i));
									}
								}
							}
						}
					}
					else if (accos->at(i)->getLuxuryLevel().getAccommodationKind() == "hotel")
					{
						found = 1;
						index = i;
						cout << "Accommodation found" << endl;
						accos->at(i)->print();
						int choice;
						cout << "1. Change number of the floor" << endl;
						cout << "2. Change location" << endl;
						cout << "3. Change number of beds" << endl;
						cout << "4. Change children bed option (1/0)" << endl;
						cout << "5. Change number of people" << endl;
						cout << "6. Change size" << endl;
						cout << "7. Change bathroom with bath option (1/0)" << endl;
						cout << "8. Change BBQ option (1/0)" << endl;
						cout << "9. Change surround system option (1/0)" << endl;
						cout << "10. Change breakfast service option (1/0)" << endl;
						cout << "11. Change cleaning service option (1/0)" << endl;
						cout << "12. Exit" << endl;
						cin >> choice;
						while (choice != 12)
						{
							if (choice == 1)
							{
								int floor;
								cout << "Please enter new number of the floor: " << endl;
								cin >> floor;
								accos->at(i)->setFloor(floor);
								cout << "Number of the floor changed" << endl;
							}
							else if (choice == 2)
							{
								string location;
								cout << "Please enter new location: " << endl;
								cin.ignore();
								getline(cin, location);
								accos->at(i)->setLocation(location);
								cout << "Location changed" << endl;
							}
							else if (choice == 3)
							{
								int beds;
								cout << "Please enter new number of beds: " << endl;
								cin >> beds;
								accos->at(i)->setNrBeds(beds);
								cout << "Number of beds changed" << endl;
							}
							else if (choice == 4)
							{
								bool children;
								cout << "Please enter new children bed option (1/0): " << endl;
								cin >> children;
								accos->at(i)->setChildrenBed(children);
								cout << "Number of children beds changed" << endl;
							}
							else if (choice == 5)
							{
								int people;
								cout << "Please enter new number of people: " << endl;
								cin >> people;
								accos->at(i)->setNrPeople(people);
								cout << "Number of people changed" << endl;
							}
							else if (choice == 6)
							{
								int size;
								cout << "Please enter new size: " << endl;
								cin >> size;
								accos->at(i)->setSize(size);
								cout << "Size changed" << endl;
							}
							else if (choice == 7)
							{
								bool bath;
								cout << "Please enter new bathroom with bath option (1/0): " << endl;
								cin >> bath;
								accos->at(i)->setBathroomWithBath(bath);
								cout << "Bathroom with bath option changed" << endl;
							}
							else if (choice == 8)
							{
								bool bbq;
								cout << "Please enter new BBQ option (1/0): " << endl;
								cin >> bbq;
								accos->at(i)->setLLBBQ(bbq);
								cout << "BBQ option changed" << endl;
							}
							else if (choice == 9)
							{
								bool surround;
								cout << "Please enter new surround system option (1/0): " << endl;
								cin >> surround;
								accos->at(i)->setLLSurroundSystem(surround);
								cout << "Surround system option changed" << endl;
							}
							else if (choice == 10)
							{
								bool breakfast;
								cout << "Please enter new breakfast service option (1/0): " << endl;
								cin >> breakfast;
								accos->at(i)->setLLBreakfastService(breakfast);
								cout << "Breakfast service option changed" << endl;
							}
							else if (choice == 11)
							{
								bool cleaning;
								cout << "Please enter new cleaning service option (1/0): " << endl;
								cin >> cleaning;
								accos->at(i)->setLLCleaningService(cleaning);
								cout << "Cleaning service option changed" << endl;
							}
							else
							{
								cout << "Wrong choice" << endl;
							}
							cout << "Please enter your choice: " << endl;
							cout << "1. Change floor" << endl;
							cout << "2. Change location" << endl;
							cout << "3. Change number of beds" << endl;
							cout << "4. Change children bed option" << endl;
							cout << "5. Change number of people" << endl;
							cout << "6. Change size" << endl;
							cout << "7. Change bathroom with bath option" << endl;
							cout << "8. Change BBQ option" << endl;
							cout << "9. Change surround system option" << endl;
							cout << "10. Change breakfast service option" << endl;
							cout << "11. Change cleaning service option" << endl;
							cout << "12. Exit" << endl;
							cin >> choice;
						}
						if (choice == 12)
						{
							cout << "Exiting..." << endl;
							for (int k = 0; k < bookings->size(); k++)
							{
								for (int j = 0; j < bookings->at(k).getAccommodations().size(); j++)
								{
									if (bookings->at(k).getAccommodations().at(j)->getID() == accos->at(i)->getID())
									{
										bookings->at(k).deleteAccommodation(j);
										bookings->at(k).addAccommodation(accos->at(i));
									}
								}
							}
						}
					}
				}
			}
			if (found == 0)
			{
				cout << "Accommodation not found" << endl;
			}
			if (found == 1)
			{
				cout << "Accommodation changed" << endl;
				accos->at(index)->print();
			}
			
		}
		else if (choice == 2)
		{
			listAccommodations(accos);
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		cout << "1. Select by ID" << endl;
		cout << "2. List Accommmodations" << endl;
		cout << "3. Exit" << endl;
		cin >> choice;
	}
	if (choice == 3)
	{
		cout << "Change Accommodation exited" << endl;
	}

	
	
}

void searchAccommodation(vector<Accommodations*>* accos)
{
	int choice;
	cout << "1. Search by ID" << endl;
	cout << "2. List Accommmodations" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;

	while (choice != 3)
	{
		if (choice == 1)
		{
			int id;
			cout << "Please enter accommodation's ID: " << endl;
			cin >> id;
			int found = 0;
			for (int i = 0; i < accos->size(); i++)
			{
				if (id == accos->at(i)->getID())
				{
					found = 1;
					cout << "Accommodation found" << endl;
					accos->at(i)->print();
				}
			}
			if (found == 0)
			{
				cout << "Accommodation not found" << endl;
			}
		}
		else if (choice == 2)
		{
			listAccommodations(accos);
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		cout << "1. Search by ID" << endl;
		cout << "2. List Accommmodations" << endl;
		cout << "3. Exit" << endl;
		cin >> choice;
	}
	if (choice == 3)
	{
		cout << "Search Accommodation exited" << endl;
	}
}

void listAccommodations(vector<Accommodations*>* accos)
{
	for (int i = 0; i < accos->size(); i++)
	{
		accos->at(i)->print();
		cout << endl;
	}
}

void createParc(vector<Parcs>* parcs, vector<Accommodations*>* accos)
{
	string name;
	string address;
	bool subtropicSwimmingPool;
	bool sportslnfrastructure;
	bool bowlingAlley;
	bool bicycleRent;
	bool childrensParadise;
	bool waterBikes;
	ParcServices services;
	vector<Accommodations*> accommodations;
	cout << "Please enter name: " << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Please enter address: " << endl;
	getline(cin, address);
	cout << "Please enter subtropic swimming pool option (1/0): " << endl;
	cin >> subtropicSwimmingPool;
	cout << "Please enter sports infrastructure option (1/0): " << endl;
	cin >> sportslnfrastructure;
	cout << "Please enter bowling alley option (1/0): " << endl;
	cin >> bowlingAlley;
	cout << "Please enter bicycle rent option (1/0): " << endl;
	cin >> bicycleRent;
	cout << "Please enter children's paradise option (1/0): " << endl;
	cin >> childrensParadise;
	cout << "Please enter water bikes option (1/0): " << endl;
	cin >> waterBikes;
	services = ParcServices(subtropicSwimmingPool, sportslnfrastructure, bowlingAlley, bicycleRent, childrensParadise, waterBikes);
	cout << "Please enter number of accommodations: " << endl;
	int accoNum;
	cin >> accoNum;
	for (int i = 0; i < accoNum; i++)
	{
		cout << "Please enter accommodation ID: " << endl;
		int id;
		cin >> id;
		for (int j = 0; j < accos->size(); j++)
		{
			if (accos->at(j)->getID() == id)
			{
				accommodations.push_back(accos->at(j));
			}
		}
	}
	Parcs parc(name, address, services, accommodations);
	parcs->push_back(parc);
	cout << "Parc created" << endl;	
	parc.print();
}

void changeParc(vector<Parcs>* parcs, vector<Accommodations*>* accos, vector<Booking>* bookings)
{
	int choice;
	cout << "1. Select by Name" << endl;
	cout << "2. List Parcs" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;

	while (choice != 3)
	{
		if (choice == 1)
		{
			int found = 0;
			int index;
			string name;
			string address;
			bool subtropicSwimmingPool;
			bool sportslnfrastructure;
			bool bowlingAlley;
			bool bicycleRent;
			bool childrensParadise;
			bool waterBikes;
			ParcServices services;
			vector<Accommodations*> accommodations;
			cout << "Please enter name of parc: " << endl;
			cin.ignore();
			getline(cin, name);
			for (int i = 0; i < parcs->size(); i++)
			{
				if (parcs->at(i).getName() == name)
				{
					found = 1;
					int rfound = 0;
					int rid;
					int afound = 0;
					int aid;
					int choice;
					index = i;
					cout << "Please enter number of option you want to change: " << endl;
					cout << "1. Name" << endl;
					cout << "2. Address" << endl;
					cout << "3. Subtropic swimming pool" << endl;
					cout << "4. Sports infrastructure" << endl;
					cout << "5. Bowling alley" << endl;
					cout << "6. Bicycle rent" << endl;
					cout << "7. Children's paradise" << endl;
					cout << "8. Water bikes" << endl;
					cout << "9. Add Accommodations" << endl;
					cout << "10. Remove Accommodations" << endl;
					cout << "11. Exit" << endl;
					cin >> choice;
					while (choice != 11)
					{
						if (choice == 1)
						{
							cout << "Please enter new name: " << endl;
							cin.ignore();
							getline(cin, name);
							parcs->at(i).setName(name);
							cout << "Name changed" << endl;
						}
						else if (choice == 2)
						{
							cout << "Please enter new address: " << endl;
							cin.ignore();
							getline(cin, address);
							parcs->at(i).setAddress(address);
							cout << "Address changed" << endl;
						}
						else if (choice == 3)
						{
							cout << "Please enter new subtropic swimming pool option (1/0): " << endl;
							cin >> subtropicSwimmingPool;
							parcs->at(i).setPSSubtropicSwimmingPool(subtropicSwimmingPool);
							cout << "Subtropic swimming pool changed" << endl;
						}
						else if (choice == 4)
						{
							cout << "Please enter new sports infrastructure option (1/0): " << endl;
							cin >> sportslnfrastructure;
							parcs->at(i).setPSSportslnfrastructure(sportslnfrastructure);
							cout << "Sports infrastructure changed" << endl;
						}
						else if (choice == 5)
						{
							cout << "Please enter new bowling alley option (1/0): " << endl;
							cin >> bowlingAlley;
							parcs->at(i).setPSBowlingAlley(bowlingAlley);
							cout << "Bowling alley changed" << endl;
						}
						else if (choice == 6)
						{
							cout << "Please enter new bicycle rent option (1/0): " << endl;
							cin >> bicycleRent;
							parcs->at(i).setPSBicycleRent(bicycleRent);
							cout << "Bicycle rent changed" << endl;
						}
						else if (choice == 7)
						{
							cout << "Please enter new children's paradise option (1/0): " << endl;
							cin >> childrensParadise;
							parcs->at(i).setPSChildrensParadise(childrensParadise);
							cout << "Children's paradise changed" << endl;
						}
						else if (choice == 8)
						{
							cout << "Please enter new water bikes option (1/0): " << endl;
							cin >> waterBikes;
							parcs->at(i).setPSWaterBikes(waterBikes);
							cout << "Water bikes changed" << endl;
						}
						else if (choice == 9)
						{
							if (parcs->at(i).getAccommodations().size() < 3)
								{
								cout << "Please enter accommodation ID you want to add: " << endl;
								cin >> aid;
								for (int l = 0; l < parcs->at(i).getAccommodations().size(); l++)
								{
									afound = 0;
									if (aid == parcs->at(i).getAccommodations().at(l)->getID())
									{
										afound = 1;
										cout << "Accommodation already added" << endl;
										break;
									}
								}
								if (afound == 0)
								{
									for (int j = 0; j < accos->size(); j++)
									{
										if (aid == accos->at(j)->getID())
										{
											afound = 1;
											parcs->at(i).addAccommodation(accos->at(j));
											cout << "Accommodation added" << endl;
											break;
										}
									}
								}
								if (afound == 0)
								{
									cout << "Accommodation not found" << endl;
								}
							}
							else
							{
								cout << "You can't add more than 3 accommodations" << endl;
							}
						}
						else if (choice == 10)
						{
							cout << "Please enter the id of the accommodation ID you want to remove: " << endl;
							cin >> rid;
							for (int k = 0; k < accos->size(); k++)
							{
								if (rid == accos->at(k)->getID())
								{
									rfound = 1;
									for (int l = 0; l < parcs->at(i).getAccommodations().size(); l++)
									{
										if (rid == parcs->at(i).getAccommodations().at(l)->getID())
										{
											parcs->at(i).deleteAccommodation(l);
											delete accos->at(k);
											accos->erase(accos->begin() + k);
											cout << "Accommodation removed" << endl;
											for (int m = 0; m < bookings->size(); m++)
											{	
												for (int n = 0; n < bookings->at(m).getAccommodations().size(); n++)
												{
													if (bookings->at(m).getAccommodations().at(n)->getID() == rid)
													{
														bookings->at(m).deleteAccommodation(n);
													}
												}
											}
											break;
										}
									}
									
								}
							}
							if (rfound == 0)
							{
								cout << "Accommodation with ID " << rid << " not found!" << endl;
							}
						}
						else
						{
							cout << "Invalid choice" << endl;
						}

						cout << "Please enter number of option you want to change: " << endl;
						cout << "1. Name" << endl;
						cout << "2. Address" << endl;
						cout << "3. Subtropic swimming pool" << endl;
						cout << "4. Sports infrastructure" << endl;
						cout << "5. Bowling alley" << endl;
						cout << "6. Bicycle rent" << endl;
						cout << "7. Children's paradise" << endl;
						cout << "8. Water bikes" << endl;
						cout << "9. Add Accommodations" << endl;
						cout << "10. Remove Accommodations" << endl;
						cout << "11. Exit" << endl;
						cin >> choice;
					}
				}
				
			}
			if (found == 0)
			{
				cout << "Park not found!" << endl;
			}
			if (found == 1)
			{
				cout << "Park updated!" << endl;
				parcs->at(index).print();
				
			}
		}
		else if (choice == 2)
		{
			listParcs(parcs);
		}
		cout << "1. Select by Name" << endl;
		cout << "2. List Parcs" << endl;
		cout << "3. Exit" << endl;
		cin >> choice;
	}
	if (choice == 3)
	{
		cout << "Change Parcs exited" << endl;  
	}
}

void deleteParc(vector<Parcs>* parcs, vector<Accommodations*>* accos, vector<Booking>* bookings)
{
	string name;
	cout << "Please enter name of parc: " << endl;
	cin.ignore();
	getline(cin, name);
	int found = 0;
	for (int i = 0; i < parcs->size(); i++)
	{
		if (parcs->at(i).getName() == name)
		{
			found = 1;
			for (int j = 0; j < parcs->at(i).getAccommodations().size(); j++)
			{
				for (int k = 0; k < accos->size(); k++)
				{
					if (parcs->at(i).getAccommodations().at(j)->getID() == accos->at(k)->getID())
					{
						delete accos->at(k);
						accos->erase(accos->begin() + k);
					}
				}
				for (int l = 0; l < bookings->size(); l++)
				{
					for (int m = 0; m < bookings->at(l).getAccommodations().size(); m++)
					{
						if (parcs->at(i).getAccommodations().at(j)->getID() == bookings->at(l).getAccommodations().at(m)->getID())
						{
							bookings->at(l).deleteAccommodation(m);
						}
					}
				}
				
			}
			parcs->erase(parcs->begin() + i);
			cout << "Parc deleted" << endl;
		}
	}
	if (found == 0)
	{
		cout << "Parc not found" << endl;
	}
	
}

void listParcs(vector<Parcs>* parcs)
{
	for (int i = 0; i < parcs->size(); i++)
	{
		parcs->at(i).print();
		cout << endl;
	}
}

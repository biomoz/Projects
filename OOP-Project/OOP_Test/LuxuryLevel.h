#ifndef LUXURYLEVEL_H
#define LUXURYLEVEL_H
#include <string>
#include <iostream>
using namespace std;

class LuxuryLevel
{
private:
	bool BBQ;
	bool surroundSystem;
	bool breakfastService;
	bool cleaningService;
	string accommodationKind;
public:
	LuxuryLevel();
	LuxuryLevel(bool BBQ, bool surroundSystem, bool breakfastService, bool cleaningService, string accommadationKind);
	~LuxuryLevel();
	void setBBQ(bool BBQ);
	void setSurroundSystem(bool surroundSystem);
	void setBreakfastService(bool breakfastService);
	void setCleaningService(bool cleaningService);
	void setAccommodationKind(string accommodationKind);
	bool getBBQ();
	bool getSurroundSystem();
	bool getBreakfastService();
	bool getCleaningService();
	string getAccommodationKind();
	void print();
};

#endif // !LUXURYLEVEL_H
#ifndef PARCSERVICES_H
#define PARCSERVICES_H

#include <string>

class ParcServices
{
private:
	bool subtropicSwimmingPool;
	bool sportslnfrastructure;
	bool bowlingAlley;
	bool bicycleRent;
	bool childrensParadise;
	bool waterBikes;
public:
	ParcServices();
	ParcServices(bool subtropicSwimmingPool, bool sportslnfrastructure, bool bowlingAlley, bool bicycleRent, bool childrensParadise, bool waterBikes);
	~ParcServices();
	void setSubtropicSwimmingPool(bool subtropicSwimmingPool);
	void setSportslnfrastructure(bool sportslnfrastructure);
	void setBowlingAlley(bool bowlingAlley);
	void setBicycleRent(bool bicycleRent);
	void setChildrensParadise(bool childrensParadise);
	void setWaterBikes(bool waterBikes);
	bool getSubtropicSwimmingPool();
	bool getSportslnfrastructure();
	bool getBowlingAlley();
	bool getBicycleRent();
	bool getChildrensParadise();
	bool getWaterBikes();
	void print();
};

#endif // !PARCSERVICES_H
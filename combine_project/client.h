#pragma once
#include <iostream>
#include <string>

enum data_type { id, name, gender, birthday, phone_number, visit, mileage, service_history };

class Client
{
private:
	int id;
	std::string name;
	std::string gender;
	std::string birthday;
	std::string phone_number;
	int visit;
	int mileage;
	std::string service_history;
protected:
	int type;	// ¸â¹ö½Ê Á¾·ù
public:
	Client();
	Client(int id, std::string name, int gender, int birthday, std::string phone_number, int visit, int mileage, std::string service_history);
	~Client();

	void SaveMileage(int cost);
	int PayMileage(int cost);
	// void record_history(int t, int length);

	void PutIntData(int data_type, int data);
	void PutStringData(int data_type, std::string data);
	void PrintInfo() const;
	int GetIntData(int data_type);
	std::string GetStringData(int data_type);
	std::string toCSV();
};
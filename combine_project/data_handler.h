#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "client.h"

class DataHandler
{
private:
	Client* clients;
	int next_pointer;
public:
	DataHandler(int size);
	~DataHandler();

	void ReadCSV(std::string filename);
	void WriteCSV(std::string filename);
	void AddClient();
	void ModifyClientMileage(int id, int cost, int type);
	void ModifyClientHistory(int id, std::string data);
	int FindClient(std::string birthday);
	std::string GetData(int index);
};
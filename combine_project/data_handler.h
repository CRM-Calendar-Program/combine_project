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
	void FindClient(std::string birthday);
	void AddClient();
	std::string GetData(int index);
};
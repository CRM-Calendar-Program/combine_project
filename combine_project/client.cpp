#include "client.h"

using namespace std;

Client::Client()
{

}

Client::Client(int id, std::string name, int gender, int birthday, std::string phone_number, int visit, int mileage, std::string service_history)
{
	this->id = id; this->name = name; this->gender = gender; this->birthday = birthday;
	this->phone_number = phone_number; this->visit = visit; this->mileage = mileage;
	this->service_history = service_history;
}

Client::~Client() {}

void Client::SaveMileage(int cost)
{
	int temp = cost * 0.1;
	mileage += temp;
}

int Client::PayMileage(int cost)
{
	if (mileage < 100)
	{
		cout << "마일리지가 충분하지 않습니다" << endl;
		return cost;
	}
	else
	{
		int temp = mileage - cost;
		if (temp < 0)
		{
			mileage = 0;
			return cost - mileage;
		}
		else
		{
			mileage -= cost;
			return 0;
		}
	}
}

void Client::PutIntData(int data_type, int data)
{
	if (data_type == 0) id = data;
	else if (data_type == 5) visit = data;
	else if (data_type == 6) mileage = data;
	else std::cout << "Type entered does not exit" << std::endl;
}

void Client::PutStringData(int data_type, std::string data)
{
	if (data_type == 1) name = data;
	else if (data_type == 2) gender = data;
	else if (data_type == 3) birthday = data;
	else if (data_type == 4) phone_number = data;
	else if (data_type == 7) service_history = data;
	else std::cout << "Type entered does not exit" << std::endl;
}

void Client::PrintInfo() const
{
	std::cout << "이름 : " << name << std::endl;
	std::cout << "성별 : " << gender << std::endl;
	std::cout << "생일 : " << birthday << std::endl;
	std::cout << "전화번호 : " << phone_number << std::endl;
	std::cout << "방문횟수 : " << visit << std::endl;
	std::cout << "마일리지 : " << mileage << std::endl;
	std::cout << "이전 서비스 : " << service_history << std::endl;
}

int Client::GetIntData(int data_type)
{
	if (data_type == 0) return id;
	else if (data_type == 5) return visit;
	else if (data_type == 6) return mileage;
	else
	{
		std::cout << "Type entered does not exit" << std::endl;
		return NULL;
	}
}

std::string Client::GetStringData(int data_type)
{
	if (data_type == 1) return name;
	else if (data_type == 2) return gender;
	else if (data_type == 3) return birthday;
	else if (data_type == 4) return phone_number;
	else if (data_type == 7) return service_history;
	else
	{
		std::cout << "Type entered does not exit" << std::endl;
		return NULL;
	}
}

std::string Client::toCSV()
{
	string line;
	for (int i = 0; i < 8; i++)
	{
		if ((i == 0) || (i == 5) || (i == 6))
		{
			line += std::to_string(GetIntData(i));
			line += ",";
		}
		else if (i == 7) line += GetStringData(i);
		else
		{
			line += GetStringData(i);
			line += ",";
		}
	}
	return line;
}
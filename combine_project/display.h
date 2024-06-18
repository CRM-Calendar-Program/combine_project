#pragma once
#ifndef SYSTEM_MENU_H
#define SYSTEM_MENU_H
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "data_handler.h"
#include "client.h"
#include <fstream>

class Display
{
private:
	int box_x = 30;
	int box_y = 10;
	DataHandler& DB;
public:
	Display(DataHandler& DB) : DB(DB) {}
	void SetCursorPosition(int x, int y);
	void CleanDisplay() { system("cls"); }
	void ShowMenu();
	void ShowClientMenu();
	void ShowMileageMenu();
	void ShowHistoryMenu();
	void DailyMenu();
	void Register();
};

#endif
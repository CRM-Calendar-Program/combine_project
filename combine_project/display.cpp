#include "display.h"

void Display::SetCursorPosition(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Display::ShowMenu()
{
	CleanDisplay();
	SetCursorPosition(0, 0);
	std::cout << "------------Menu-------------" << std::endl;
	std::cout << "1. 고객관리" << std::endl;
	std::cout << "2. 마일리지 관리" << std::endl;
	std::cout << "3. 서비스 히스토리" << std::endl;
	// std::cout << "4. 일정관리" << std::endl;

	SetCursorPosition(0, 5);
	std::cout << "---------일정 요약----------" << std::endl;

	SetCursorPosition(0, 6);
	DailyMenu();
	//Register();

	char selection = 0;
	while (true)
	{
		while (!_kbhit()) {}
		selection = _getch();

		switch (selection)
		{
		case '1':
			ShowClientMenu();
			break;
		case '2':
			ShowMileageMenu();
			break;
		case '3':
			ShowHistoryMenu();
			break;
		case '4':
			DailyMenu();
			break;
		default:
			std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
			Sleep(1000);
		}
	}
}

void Display::ShowClientMenu()
{
	CleanDisplay();
	std::cout << "------------고객관리-------------" << std::endl;
	std::cout << "1. 고객찾기" << std::endl;
	std::cout << "2. 고객추가" << std::endl;
	std::cout << std::endl;

	int repeat = -1;
	char selection = 0;
	while (repeat == -1)
	{
		while (!_kbhit()) {}
		selection = _getch();

		std::string birthday;
		switch (selection)
		{
		case '1':
			std::cout << "---------------------------------" << std::endl;
			std::cout << "찾으려는 고객의 생년월일을 입력해주세요!!" << std::endl;
			std::cout << "-> 메인으로 돌아가려면 \'m\'를 입력하세요" << std::endl;
			while (repeat == -1)
			{
				std::cout << "\n";
				std::cout << ">> ";
				std::cin >> birthday;
				if (birthday == "m")
				{
					repeat = 0;
					continue;
				}
				std::cout << std::endl;
				repeat = DB.FindClient(birthday);
				if (repeat != -1)
				{
					std::cout << "\n";
					std::cout << "메인으로 돌아가려면 \'m\'를 입력하세요>> ";
					std::cin >> birthday;
					if (birthday == "m") ShowMenu();
					else repeat = -1;
				}
			}
			break;
		case '2':
			std::cout << "---------------------------------" << std::endl;
			std::cout << "추가하려는 고객의 정보를 입력해주세요!!" << std::endl;
			DB.AddClient();
			break;
		default:
			std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
			Sleep(1000);
		}
	}
	ShowMenu();
}

void Display::ShowMileageMenu()
{
	CleanDisplay();
	std::cout << "----------마일리지 관리-----------" << std::endl;
	std::cout << "1. 마일리지 추가" << std::endl;
	std::cout << "2. 마일리지 사용" << std::endl;
	std::cout << std::endl;

	int repeat = -1;
	char selection = 0;
	while (repeat == -1)
	{
		while (!_kbhit()) {}
		selection = _getch();

		std::string birthday;
		switch (selection)
		{
		case '1':
			std::cout << "---------------------------------" << std::endl;
			std::cout << "찾으려는 고객의 생년월일을 입력해주세요!!" << std::endl;
			std::cout << "-> 메인으로 돌아가려면 \'m\'를 입력하세요" << std::endl;
			while (repeat == -1)
			{
				std::cout << "\n";
				std::cout << ">> ";
				std::cin >> birthday;
				if (birthday == "m")
				{
					repeat = 0;
					continue;
				}
				std::cout << std::endl;
				repeat = DB.FindClient(birthday);
				std::cout << std::endl;
				std::cout << "---------------------------------" << std::endl;
				int cost = 0;
				std::cout << "비용을 입력해주세요 >> ";
				std::cin >> cost;
				DB.ModifyClientMileage(repeat, cost, 0);
			}
			break;
		case '2':
			std::cout << "---------------------------------" << std::endl;
			std::cout << "찾으려는 고객의 생년월일을 입력해주세요!!" << std::endl;
			std::cout << "-> 메인으로 돌아가려면 \'m\'를 입력하세요" << std::endl;
			while (repeat == -1)
			{
				std::cout << "\n";
				std::cout << ">> ";
				std::cin >> birthday;
				if (birthday == "m")
				{
					repeat = 0;
					continue;
				}
				std::cout << std::endl;
				repeat = DB.FindClient(birthday);
				std::cout << std::endl;
				std::cout << "---------------------------------" << std::endl;
				int cost = 0;
				std::cout << "비용을 입력해주세요 >> ";
				std::cin >> cost;
				DB.ModifyClientMileage(repeat, cost, 1);
			}
			break;
		default:
			std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
			Sleep(1000);
		}
	}
	ShowMenu();
}

void Display::ShowHistoryMenu()
{
	int repeat = -1;
	std::string birthday;

	CleanDisplay();
	std::cout << "----------히스토리 관리-----------" << std::endl;
	std::cout << "찾으려는 고객의 생년월일을 입력해주세요!!" << std::endl;
	std::cout << "-> 메인으로 돌아가려면 \'m\'를 입력하세요" << std::endl;
	while (repeat == -1)
	{
		std::cout << "\n";
		std::cout << ">> ";
		std::cin >> birthday;
		if (birthday == "m")
		{
			repeat = 0;
			continue;
		}
		std::cout << std::endl;
		repeat = DB.FindClient(birthday);
		std::cout << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::string history;
		std::cout << "비용을 입력해주세요 >> ";
		std::cin >> history;
		DB.ModifyClientHistory(repeat, history);
	}
}

void Display::DailyMenu()
{
	std::string line;
	std::ifstream file("summary.txt"); // summary 열기
	if (file.is_open()) {
		while (getline(file, line)) {
			std::cout << line << std::endl;
		}
		file.close(); // 파일 닫기
	}
	else {
		std::cout << "Unable to open file";
	}
	
}

void Display::Register()
{
	SetCursorPosition(0, 5);
	std::cout << "---------오늘의 일정----------" << std::endl;
	std::cout << "┌";
	for (int i = 0; i < box_x; i++)
		std::cout << "─";
	std::cout << "┐";

	for (int i = 7; i < box_y + 10; i++)
	{
		SetCursorPosition(0, i);
		std::cout << "│";
		SetCursorPosition(box_x + 1, i);
		std::cout << "│";
	}

	SetCursorPosition(0, box_y + 9);
	std::cout << "└";
	for (int i = 0; i < box_x; i++)
		std::cout << "─";
	std::cout << "┘";
}
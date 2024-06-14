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
	std::cout << "---------오늘의 일정----------" << std::endl;

	SetCursorPosition(0, 6);
	// 오늘의 일정부분 출력

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

	// 입력 받고 그에 해당하는 기능 추가
}

void Display::ShowMileageMenu()
{
	std::string birthday;

	CleanDisplay();
	std::cout << "----------마일리지 관리-----------" << std::endl;
	std::cout << "고객 생년월일 : ";
	std::cin >> birthday;


}

void Display::ShowHistoryMenu()
{

}

void Display::DailyMenu()
{
	// 추가할 부분
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
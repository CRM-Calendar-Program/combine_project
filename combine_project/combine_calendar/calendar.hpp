#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

// 월과 연도를 입력받아 해당 월의 일 수를 반환하는 함수
int getNumberOfDays(int month, int year);

// 달력을 그리는 함수
void drawCalendar(sf::RenderWindow& window, const vector<string>& weekDays, const string& currentMonthStr, int firstWeekDayOfMonth, int numberOfDays, const unordered_map<string, string>& reminders, int today, const string& currentYearMonth);

// 알림을 파일에 저장하는 함수
void saveReminders(const unordered_map<string, string>& reminders, const string& filename);

// 파일에서 알림을 불러오는 함수
void loadReminders(unordered_map<string, string>& reminders, const string& filename);

// 오늘의 알림을 별도의 창에 표시하는 함수
void showTodayReminder(const string& reminder, const string& todayDate);

#endif // CALENDAR_HPP

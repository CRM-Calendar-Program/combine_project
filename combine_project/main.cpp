#include <iostream>
#include <cstdlib>
#include "data_handler.h"
#include "calendar.hpp"

using namespace std;

int GetSize(string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return 0;
    }

    int size = 0;
    string line;
    while (getline(file, line))
    {
        size++;
    }

    file.close();
    return size + 10;
}

int main()
{
    string filename = "people.csv";
    int size;

    size = GetSize(filename);
    DataHandler DB(size);
    DB.ReadCSV(filename);
    DB.WriteCSV(filename);

//================================

    int currentDay, currentMonth, currentYear, firstWeekDayOfMonth, numberOfDays;
    vector<string> months = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    vector<string> weekDays = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    // 현재 날짜 초기화
    time_t currentTime = time(0);
    struct tm now;
    localtime_s(&now, &currentTime);
    currentDay = now.tm_mday;
    currentYear = now.tm_year + 1900;
    currentMonth = now.tm_mon;
    numberOfDays = getNumberOfDays(currentMonth + 1, currentYear);

    struct tm tFirst = { 0, 0, 0, 1, currentMonth, currentYear - 1900 };
    time_t time_temp = mktime(&tFirst);
    struct tm firstTime;
    localtime_s(&firstTime, &time_temp);

    firstWeekDayOfMonth = firstTime.tm_wday;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Calendar");
    
    // 리마인더를 파일에서 불러옴
    unordered_map<string, string> reminders;
    loadReminders(reminders, "reminders.txt");

    string currentYearMonth = to_string(currentYear) + "-" + (currentMonth + 1 < 10 ? "0" : "") + to_string(currentMonth + 1);

    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cerr << "Failed to open font" << endl;
        return 1;
    }

    // 오늘의 리마인더 표시
    string todayKey = currentYearMonth + "-" + (currentDay < 10 ? "0" : "") + to_string(currentDay);
    if (reminders.count(todayKey))
    {
        string todayDate = to_string(currentYear) + "-" + (currentMonth + 1 < 10 ? "0" : "") + to_string(currentMonth + 1) + "-" + (currentDay < 10 ? "0" : "") + to_string(currentDay);
        showTodayReminder(reminders[todayKey], todayDate);
    }

    string inputText;
    bool inputActive = false;
    bool deleteActive = false;
    bool displayActive = false;
    int reminderDay = 0;
    string displayReminder;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // 날짜를 클릭하면 리마인더 표시
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                int col = (x - 50) / 100;
                int row = (y - 100) / 50;
                int day = col + row * 7 - firstWeekDayOfMonth + 1;
                if (day >= 1 && day <= numberOfDays)
                {
                    reminderDay = day;
                    string key = currentYearMonth + "-" + (day < 10 ? "0" : "") + to_string(day);
                    displayReminder = reminders.count(key) ? reminders[key] : "";
                    displayActive = true;
                    inputText.clear();
                }
            }
            
            // 키보드 이벤트
            if (event.type == sf::Event::KeyPressed)
            {
                // esc 누르면 모든 모드 종료
                if (event.key.code == sf::Keyboard::Escape)
                {
                    inputActive = false;
                    deleteActive = false;
                    displayActive = false;
                }
                // enter 누르면 리마인더 저장
                else if (inputActive && event.key.code == sf::Keyboard::Enter)
                {
                    string key = currentYearMonth + "-" + (reminderDay < 10 ? "0" : "") + to_string(reminderDay);
                    reminders[key] = inputText;
                    saveReminders(reminders, "reminders.txt");
                    inputActive = false;
                    displayActive = false;
                }
                // enter 누르면 리마인더 삭제
                else if (deleteActive && event.key.code == sf::Keyboard::Enter)
                {
                    string key = currentYearMonth + "-" + (reminderDay < 10 ? "0" : "") + to_string(reminderDay);
                    reminders.erase(key);
                    saveReminders(reminders, "reminders.txt");
                    deleteActive = false;
                    displayActive = false;
                }
                // insert 누르면 입력 모드
                else if (event.key.code == sf::Keyboard::Insert)
                {
                    inputActive = true;
                    deleteActive = false;
                    inputText.clear();
                }
                // delete 누르면 삭제 모드
                else if (event.key.code == sf::Keyboard::Delete)
                {
                    deleteActive = true;
                    inputActive = false;
                    inputText.clear();
                }
            }
            // 입력모드에서 텍스트 입력 처리
            if (inputActive && event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !inputText.empty())
                {
                    inputText.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                {
                    inputText += static_cast<char>(event.text.unicode);
                }
            }
        }

        window.clear(sf::Color::White);
        drawCalendar(window, weekDays, months[currentMonth] + " " + to_string(currentYear), firstWeekDayOfMonth, numberOfDays, reminders, currentDay, currentYearMonth);
        
        // 리마인더 추가
        if (inputActive)
        {
            sf::Text insertText;
            insertText.setFont(font);
            insertText.setString("Press Enter to input reminder for day " + to_string(reminderDay));
            insertText.setCharacterSize(24);
            insertText.setFillColor(sf::Color::Red);
            insertText.setPosition(50, window.getSize().y - 210);
            window.draw(insertText);

            sf::RectangleShape inputBox(sf::Vector2f(700, 100));
            inputBox.setFillColor(sf::Color::White);
            inputBox.setOutlineColor(sf::Color::Black);
            inputBox.setOutlineThickness(1);
            inputBox.setPosition(50, window.getSize().y - 150);
            window.draw(inputBox);

            sf::Text inputTextDisplay(inputText, font, 24);
            inputTextDisplay.setFillColor(sf::Color::Black);
            inputTextDisplay.setPosition(60, window.getSize().y - 150);
            window.draw(inputTextDisplay);
            
            // 선택된 날짜에 리마인더가 있다면 표시
            displayActive = true;
        }
        
        // 리마인더 삭제시 메시지 표시
        if (deleteActive)
        {
            sf::Text deleteText;
            deleteText.setFont(font);
            deleteText.setString("Press Enter to delete reminder for day " + to_string(reminderDay));
            deleteText.setCharacterSize(24);
            deleteText.setFillColor(sf::Color::Red);
            deleteText.setPosition(50, window.getSize().y - 210);
            window.draw(deleteText);

            // 선택된 날짜에 리마인더가 있다면 표시
            displayActive = true;
        }

        // 리마인더가 있으면 화면에 표시
        if (displayActive) {
            if (!displayReminder.empty())
            {
                sf::Text reminderDisplay("Reminder: " + displayReminder, font, 24);
                reminderDisplay.setFillColor(sf::Color::Black);
                reminderDisplay.setPosition(50, window.getSize().y - 185);
                window.draw(reminderDisplay);
            }
        }

        window.display();
    }
    //===========================python
    system("python main.py");

    return 0;
}
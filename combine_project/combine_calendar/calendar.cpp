#include "Calendar.hpp"

// 월과 연도를 입력받아 해당 월의 일 수를 반환하는 함수
int getNumberOfDays(int month, int year)
{
    if (month == 2) // 2월 (윤년 고려)
    {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else
        return 30;
}

// 달력을 그리는 함수
void drawCalendar(sf::RenderWindow& window, const vector<string>& weekDays, const string& currentMonthStr, int firstWeekDayOfMonth, int numberOfDays, const unordered_map<string, string>& reminders, int today, const string& currentYearMonth)
{
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cerr << "폰트 로드 실패." << endl;
        return;
    }

    int xOffset = 50, yOffset = 50;
    int cellWidth = 100, cellHeight = 50;

    // 현재 월 텍스트 표시
    sf::Text monthText;
    monthText.setFont(font);
    monthText.setString(currentMonthStr);
    monthText.setCharacterSize(30);
    monthText.setFillColor(sf::Color::Black);
    monthText.setPosition(50, 10);
    window.draw(monthText);

    // 요일 표시
    for (int w = 0; w < 7; ++w)
    {
        sf::Text dayText;
        dayText.setFont(font);
        dayText.setString(weekDays[w]);
        dayText.setCharacterSize(24);
        dayText.setFillColor(sf::Color::Black);
        dayText.setPosition(xOffset + w * cellWidth, yOffset);
        window.draw(dayText);
    }

    int tempBreak = 1;
    for (int w = 0; w < firstWeekDayOfMonth; w++)
    {
        tempBreak++;
    }

    // 날짜 표시
    for (int d = 1; d <= numberOfDays; d++)
    {
        sf::Text dayText;
        dayText.setFont(font);
        dayText.setString(to_string(d));
        dayText.setCharacterSize(24);

        string key = currentYearMonth + "-" + (d < 10 ? "0" : "") + to_string(d);

        if (d == today)
        {
            dayText.setFillColor(sf::Color::Green);
        }
        else if (reminders.count(key))
        {
            dayText.setFillColor(sf::Color::Blue);
        }
        else
        {
            dayText.setFillColor(sf::Color::Black);
        }

        dayText.setPosition(xOffset + (tempBreak - 1) * cellWidth, yOffset + cellHeight);

        if (reminders.count(key))
        {
            sf::RectangleShape reminderBox(sf::Vector2f(cellWidth, cellHeight));
            reminderBox.setFillColor(sf::Color::Yellow);
            reminderBox.setPosition(xOffset + (tempBreak - 1) * cellWidth, yOffset + cellHeight);
            window.draw(reminderBox);
        }

        window.draw(dayText);

        if (tempBreak >= 7)
        {
            yOffset += cellHeight;
            tempBreak = 0;
        }
        tempBreak++;
    }

    // 안내 텍스트 표시
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Insert: 알림 추가  Delete: 알림 삭제  ESC: 취소");
    instructions.setCharacterSize(14);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition(50, window.getSize().y - 220);
    window.draw(instructions);
}

// 알림을 파일에 저장하는 함수
void saveReminders(const unordered_map<string, string>& reminders, const string& filename)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "파일 열기 실패: " << filename << endl;
        return;
    }

    for (const auto& reminder : reminders)
    {
        outFile << reminder.first << ":" << reminder.second << endl;
    }
}

// 파일에서 알림을 불러오는 함수
void loadReminders(unordered_map<string, string>& reminders, const string& filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "파일 열기 실패: " << filename << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos)
        {
            string date = line.substr(0, colonPos);
            string message = line.substr(colonPos + 1);
            reminders[date] = message;
        }
    }
}

// 오늘의 알림을 별도의 창에 표시하는 함수
void showTodayReminder(const string& reminder, const string& todayDate)
{
    sf::RenderWindow reminderWindow(sf::VideoMode(400, 200), "오늘의 알림");

    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cerr << "폰트 로드 실패." << endl;
        return;
    }

    sf::Text reminderText;
    reminderText.setFont(font);
    reminderText.setString(reminder);
    reminderText.setCharacterSize(24);
    reminderText.setFillColor(sf::Color::Black);
    reminderText.setPosition(20, 80);

    sf::Text dateText;
    dateText.setFont(font);
    dateText.setString(todayDate + "\n오늘의 알림");
    dateText.setCharacterSize(18);
    dateText.setFillColor(sf::Color::Black);
    dateText.setPosition(20, 20);

    while (reminderWindow.isOpen())
    {
        sf::Event event;
        while (reminderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                reminderWindow.close();
        }

        reminderWindow.clear(sf::Color::White);
        reminderWindow.draw(reminderText);
        reminderWindow.draw(dateText);
        reminderWindow.display();
    }
}

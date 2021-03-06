#include <iostream>
#include <ctime>


struct Date
{
private:
    int _day, _month, _year;

    bool is_leap(int year) const
    {
        if (year % 400 == 0)
            return true;
        if ((year % 100 != 0) && (year % 4 == 0))
            return true;

        return false;
    }

    int num_of_days(int day, int month, int year) const
    {
        int result = 0;
        int num_leap = 0;
        for (int i = 0; i < year; ++i)
            if (is_leap(i))
                ++num_leap;

        result = year * 365 + num_leap;

        if (month == 1)
            return result + day;
        if (month == 2)
            return result + day + 31;
        else
        {
            result += 59;
            if (month < 9)
            {
                for (size_t i = 3; i < month; ++i)
                    if (i % 2 == 0)
                        result += 30;
                    else
                        result += 31;

                if (is_leap(month))
                    return result + day + 1;
                return result + day;
            }

            for (size_t i = 3; i < 8; ++i)
                if (i % 2 == 0)
                    result += 30;
                else
                    result += 31;

            for (size_t i = 8; i < month; ++i)
                if (i % 2 != 0)
                    result += 30;
                else
                    result += 31;

            if (is_leap(month))
                return result + day + 1;
            return result + day;
        }
    }

    int toInt(char symbol)
    {
        return (int)(symbol - '0');
    }

public:
    //Constructors
    Date()
    {
        time_t rawtime;
        time(&rawtime);
        struct tm timeinfo;
        localtime_s(&timeinfo, &rawtime);

        _day = timeinfo.tm_mday;
        _month = timeinfo.tm_mon + 1;
        _year = timeinfo.tm_year + 1900;
    }
    Date(int day, int month, int year)
    {
        _day = day;
        _month = month;
        _year = year;
    }
    Date(char* stroka)
    {
        _day = toInt(stroka[0]) * 10 + toInt(stroka[1]);
        _month = toInt(stroka[3]) * 10 + toInt(stroka[4]);
        _year = toInt(stroka[6]) * 1000 + toInt(stroka[7])*100+toInt(stroka[8])*10+toInt(stroka[9]);
    }

    //Methods
    int getDay() const { return _day; }
    int getMonth() const { return _month; }
    int getYear() const { return _year; }

    void PrintDate() const
    {
        std::cout << "Date: ";
        if (_day < 10)
            std::cout << '0';
        std::cout << _day << '.';

        if(_month<10)
            std::cout << '0';
        std::cout<< _month << '.' << _year << '\n';
    }

    int Period(Date const& date2) const
    {
        int d1 = num_of_days(_day, _month, _year);
        int d2 = num_of_days(date2._day, date2._month, date2._year);
        return abs(d1 - d2);
    }

};

//operators
inline std::ostream& operator<<(std::ostream& out, Date const& date)
{
    if (date.getDay() < 10)
        if (date.getMonth() < 10)
            return out << '0' << date.getDay() << ".0" << date.getMonth() << '.' << date.getYear() << '\n';
        else
            return out << '0' << date.getDay() << "." << date.getMonth() << '.' << date.getYear() << '\n';
    if (date.getMonth() < 10)
        return out << date.getDay() << ".0" << date.getMonth() << '.' << date.getYear() << '\n';
    return out << date.getDay() << "." << date.getMonth() << '.' << date.getYear() << '\n';
}

inline std::istream& operator>>(std::istream& in, Date& date)
{
    std::cout << "Input the date in the format: \"dd.mm.YYYY\"\n";
    char stroka[10];
    in >> stroka;
    date = Date(stroka);
    return in;
}

inline int operator-(Date const& date1, Date const& date2)
{
    return date1.Period(date2);
}


int main()
{
    Date today;
    today.PrintDate();

    char date[] = "10.01.2002";
    Date myday(date);
    myday.PrintDate();
    std::cout << myday;
    std::cin >> myday;

    std::cout << "The number of days between dates " << today.Period(myday) << '\n';
    std::cout << "Subtraction operator " << today - myday << '\n';
   
    system("pause");
    return 0;
}
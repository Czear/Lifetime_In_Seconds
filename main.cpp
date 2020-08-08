#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>

/**
 * Validates user input date values
 */
bool ValidateUserInput(int date_day, int date_month, int date_year) {
    if(!(date_day > 0 || date_month > 0)) {
        return false; /* 0 value inputs are not allowed except for year */
    }

    if(date_day > 31) {
        return false; /* Day value to big */
    }

    if(date_month > 12) {
        return false; /* Month value to big */
    }

    if(date_month == 2) { /* Special treatment for February */
        bool is_leap_year = !(date_year % 4);

        if(date_day > 29 || (!is_leap_year && date_day == 29)) {
            return false;
        }

    } else {
        std::vector<int> shorter_moths_indexes {4, 6, 9, 11};
        bool is_shorter_month = std::find(shorter_moths_indexes.begin(), shorter_moths_indexes.end(), date_month) != shorter_moths_indexes.end();

        if(is_shorter_month && (date_day == 31)) {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cout << "Enter your birth date (dd mm yyyy)" << std::endl << std::endl;

    int birth_day {}, birth_moth {}, birth_year {};
    std::cin >> birth_day >> birth_moth >> birth_year;


    if(!ValidateUserInput(birth_day, birth_moth, birth_year)) {
        return(1); /* Bad input */
    }

    struct tm birth_date {0};

    /* Adjust birth date based on user input */
    birth_date.tm_mday = birth_day;
    birth_date.tm_mon = birth_moth - 1; /* January has index 0 */
    birth_date.tm_year = birth_year - 1900; /* Time is tracked since 1990 */
    birth_date.tm_hour = -1; /* 0 sets hour value to 1AM */

    time_t birth_time = mktime(&birth_date);
    time_t now = time(nullptr);

    /* Parse science notation into decimal */
    std::stringstream ss;
    ss.precision(0);
    ss << std::fixed << difftime(now,birth_time);


    std::cout << std::endl << ss.str() << " seconds has passed since your birth" << std::endl;
    std::cout << "* assuming that you have been born at the start of that day";

    return(0);
}
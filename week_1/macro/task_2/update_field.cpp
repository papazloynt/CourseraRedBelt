#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

/// Operators for Date
ostream& operator << (ostream& os, const Date& date) {
    os << "Date:   "<< "Day: " << date.day
    << "; Month: " << date.month
    << "; Year: " << date.year << std::endl;
    return os;
}

bool operator==(const Date& lhs, const Date& rhs){
    if (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day)
        return true;
    return false;
}

bool operator<(const Date& lhs, const Date& rhs){
    return vector<int>{lhs.year, lhs.month, lhs.day} <
    vector<int>{rhs.year, rhs.month, rhs.day};
}

istream& operator>> (istream& is, Date& dt)
{
    is >> dt.year >> dt.month >> dt.day;
    dt.month = -dt.month;
    dt.day = - dt.day;
    return is;
}

/// Operators for Time
ostream& operator << (ostream& os, const Time& time) {
    os << "Time:   " << time.hours
    << ":" << time.minutes
    << std::endl;
    return os;
}

bool operator==(const Time& lhs, const Time& rhs){
    if (lhs.hours == rhs.hours && lhs.minutes == rhs.minutes)
        return true;
    return false;
}

bool operator<(const Time& lhs, const Time& rhs){
    return vector<int>{lhs.hours, lhs.minutes} <
    vector<int>{rhs.hours, rhs.minutes};
}

istream& operator>>(istream& is, Time& tm)
{
    std::string str, tmp;
    is >> str;
    for (auto s : str) {
        if (s != ':') {
            tmp += s;
        } else {
            tm.hours = stoi(tmp);
            tmp = "";
        }
    }
    tm.minutes = stoi(tmp);
    return is;
}

#define UPDATE_FIELD(ticket, field, values)                   \
if (values.find(#field) != values.end()) {                    \
    istringstream is(values.find(#field)->second);            \
    is >> ticket.field;                                       \
}












void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
            };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
            {"price", "12550"},
            {"arrival_time", "20:33"},
            };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
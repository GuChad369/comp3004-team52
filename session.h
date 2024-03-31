#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

class Session
{
public:
    Session(const string& date, const string& time);

    const string& getDate() const;
    const string& getTime() const;
    bool getNeedDeleted();
    void setNeedDeleted(bool b);




private:
    string date;
    string time;
    bool needDeleted;
};

#endif // SESSION_H

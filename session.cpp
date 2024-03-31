#include "session.h"

Session::Session(const string& date, const string& time):needDeleted(true)
{

    this->date = date;
    this->time = time;
}



const string& Session::getDate() const{
    return date;
};

const string& Session::getTime() const{
    return time;
};

bool Session::getNeedDeleted(){
    return needDeleted;
}
void Session::setNeedDeleted(bool b){
    this->needDeleted = b;
}

#include "User.h"

User::User()
{
    //ctor
}

string User::getUser() const
{
    return user;
}

void User::setUser(const string &value)
{
    user = value;
}

int User::getScore() const
{
    return score;
}

void User::setScore(int value)
{
    score = value;
}

ostream& operator << (ostream& os, const User& obj)
{
    os << obj.getUser() << "|" << obj.getScore();
    return os;
}

istream& operator >> (istream& is, User& obj)
{
    string aux;

    getline(is, aux, '|');
    if(aux.length())
    {
        obj.setUser(aux);
        getline(is, aux);
        obj.setScore(stoi(aux));
    }
    return is;
}

bool User::operator > (const User &obj) const
{
    return score > obj.getScore();
}

bool User::operator < (const User &obj) const
{
    return score < obj.getScore();
}

bool User::operator == (const User &otro) const
{
    return  score == otro.getScore();
}

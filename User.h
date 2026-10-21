#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User
{
    public:
        User();

        string getUser() const;
        void setUser(const string &value);

        int getScore() const;
        void setScore(int value);

        friend ostream& operator << (ostream& os, const User& obj);
        friend istream& operator >> (istream& is, User& obj);
        bool operator > (const User &obj) const;
        bool operator < (const User &obj) const;
        bool operator == (const User &otro) const;

    private:
        string user;
        int score;
};

#endif // USER_H

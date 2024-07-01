#pragma once
#include <iostream>
#include <string>
using namespace std;

class MemberQueueNode
{
private:


public:
    string name;
    int age;
    string date;
    char type;

    MemberQueueNode() {
        name = "";
        age = 0;
        date = "";
        type = '\0';
    }

    MemberQueueNode(const string& n, int a, const string& d, char t)
        : name(n), age(a), date(d), type(t) {}

    ~MemberQueueNode() {}

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    string getDate() const {
        return date;
    }

    char getType() const {
        return type;
    }
};
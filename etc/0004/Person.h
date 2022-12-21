#include <iostream>
#include <string>
using namespace std;

#ifndef __PERSON_H
#define __PERSON_H

class Person
{
private:
    string sex;
    int height;
    int weight;
public:
    Person(string sex, int height, int weight);
    string getSex();
    int getHeight();
    int getWeight();
};



#endif //__PERSON_H

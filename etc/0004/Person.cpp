#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

Person::Person(string sex, int height, int weight)
{
    this->sex = sex;
    this->height = height;
    this->weight = weight;
}

string Person::getSex()
{
    return sex;
}

int Person::getHeight()
{
    return height;
}

int Person::getWeight()
{
    return weight;
}
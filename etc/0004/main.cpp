#include "Person.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

vector <string> split(string input, char delimiter)
{
    vector <string> answer;
    stringstream ss(input);
    string temp;
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
};


vector <Person*> makeData()
{
    vector <Person*> PersList;
    ifstream myfile("file.txt");
    string str;
    while(getline(myfile, str))
    {
        vector <string> one_pers;
        one_pers = split(str,',');
        string sex = one_pers[0];
        int height = stoi(one_pers[1]);
        int weight = stoi(one_pers[2]);
        Person *person = new Person(sex, height, weight);
        PersList.push_back(person);
    }
    return PersList;
}

int main() {
    cout << "몸무게와 키가 저장된 검사자 데이터를 불러오는 중입니다." << endl;
    vector <Person*> PersList = makeData();
    cout << "1. 검사자 키 & 몸무게 평균" << endl;
    cout << "2. 여성 검사자 키 & 몸무게 평균" << endl;
    cout << "3. 남성 검사자 키 & 몸무게 평균" << endl;
    cout << "4. 검사자 체질량지수(BMI) 평균" << endl;
    cout << "5. 여성 검사자 체질량지수(BMI) 평균" << endl;
    cout << "6. 남성 검사자 체질량지수(BMI) 평균" << endl;
    cout << "7. 여성 검사자 비만도(PIBW) 평균" << endl;
    cout << "8. 남성 검사자 비만도(PIBW) 평균" << endl;
    cout << "---------------------------------" << endl;
    cout << "Select number ? ";
    int i = 0;
    cin >> i;
    cin.ignore();
    if(i==1)
    {
        int h_sum = 0;
        int w_sum = 0;
        float h_average;
        float w_average;
        for(int i =0; i < PersList.size() ; i++)
        {
            h_sum += PersList[i]->getHeight();
            w_sum += PersList[i]->getWeight();
        }
        h_average = h_sum/PersList.size();
        w_average = w_sum/PersList.size();
        cout << "키 평균 :" << h_sum << "몸무게 평균 :" << w_sum;
    }
    if(i==2)
    {

    }
    if(i==4)
    {

    }
    if(i==5)
    {

    }
    if(i==6)
    {

    }
    if(i==7)
    {

    }
    if(i==8)
    {

    }

    return 0;
}
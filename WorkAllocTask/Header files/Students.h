#ifndef STUDENTS_H
#define STUDENTS_H
#include <string>
using namespace std;

class Student{
    string Name, Surname, Patronymic, City;
    bool  Marital_Status = 0,  Kids = 0;
public:
    void Set_Name(string tmp){
        Name = tmp;
    }
    void Set_Surname(string tmp){
        Surname = tmp;
    }
    void Set_Patronymic(string tmp){
        Patronymic = tmp;
    }
    void Set_City(string tmp){
        City = tmp;
    }
    void Set_Marital_Status(bool tmp){
        Marital_Status = tmp;
    }
    void Set_Kids(bool tmp){
        Kids = tmp;
    }

    string Get_Name(){
        return Name;
    }
    string Get_Surname(){
        return Surname;
    }
    string Get_Patronymic() {
        return Patronymic;
    }
    string Get_City(){
        return City;
    }
    bool Get_Marital_Status(){
        return Marital_Status;
    }
    bool Get_Kids(){
        return Kids;
    }
    int Number_of_students = 0;

};
    extern Student *Arr;
#endif // STUDENTS_H

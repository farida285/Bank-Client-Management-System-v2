#pragma once
#include <iostream>
#include <string>
using namespace std;
class clsPerson
{
private:
   
    string _firstName;
    string _lastName;
    string _email;
    string _phoneNumber;
public:
    clsPerson( string firstName, string lastName, string email, string phoneNumber) {
      
        _firstName = firstName;
        _lastName = lastName;
        _email = email;
        _phoneNumber = phoneNumber;
    };
    void SetFirstName (string firstName) {
        _firstName = firstName;
    }
    string GetFirstName  ()const {
        return _firstName;
    }
    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

    void SetLastName(string lastName) {
        _lastName = lastName;
    }
    string GetLastName() const {
        return _lastName;
    }

    __declspec(property(get = GetLastName, put = SetLastName)) string LastName;

    void SetEmail(string email) {
        _email = email;
    }
    string GetEmail()const {
        return _email;
    }

    __declspec(property(get = GetEmail, put = SetEmail)) string Email;

    void SetPhoneNumber(string phoneNumber) {
        _phoneNumber = phoneNumber;
    }
    string GetPhoneNumber()const {
        return _phoneNumber;
    }

    __declspec(property(get = GetPhoneNumber, put = SetPhoneNumber)) string PhoneNumber;

    string FullName()const {
        return(_firstName + " " + _lastName);
    }

};


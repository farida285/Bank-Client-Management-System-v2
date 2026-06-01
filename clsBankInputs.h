#pragma once
#include "clsInputValidate.h"
#include "StringLibrary.h"
#include <cctype>

class clsBankInputs
{
private:
    static bool _IsOnlyNumbers(const string& text) {
        for (unsigned short i = 0; i < text.size(); i++) {
            if (!(isdigit(text[i]))) {
                return 0;
            }
        }
        return 1;
    }
    static bool _MyIspunctuations(char charcter) {
        int c = (int)charcter;
        return((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126));
    }
    static bool _IsNameContainSpecialChracterExpectoneHyphen(string s ) {
        size_t pos = s.find('-');
        if (pos != s.npos) {
            s.erase(pos, 1);

        }
        for (char& c : s) {
            if (_MyIspunctuations(c)) {
                return true;
            }
        }
        return false;

    }
    static bool _IsValidName(const string& name)
    {
        // 1. length + empty spaces check
        if (name.empty())
            return false;

        // 2. numbers
        if (clsString::ContainsNumber(name))
            return false;

        // 3. invalid characters
        if (_IsNameContainSpecialChracterExpectoneHyphen(name))
            return false;

        // 4. start/end rules
        if (name.front() == ' ' || name.back() == ' ' ||
            name.front() == '-' || name.back() == '-')
            return false;

        // 5. space/hyphen rules
  
        short hyphens = clsString::CountSpecificCharInString(name, '-', true);
        short spaces= clsString::CountSpecificCharInString(name, ' ', true);

        if (spaces > 1 || hyphens > 1)
            return false;

        if (spaces >= 1 && hyphens >= 1)
            return false;

        // 6. consecutive chars check
        for (int i = 1; i < name.size(); i++)
        {
            if ((name[i] == ' ' && name[i - 1] == ' ') ||
                (name[i] == '-' && name[i - 1] == '-'))
                return false;
        }

        return true;
    }   
    static bool _HasConsecutive(const string& s, char ch) {
        for (size_t i = 0; i + 1 < s.size(); i++) {
            if (s[i] == ch && s[i + 1] == ch)
                return true;
        }
        return false;
    }
    static bool _IsValidLocalPart(string l) {
        if (l == ""||l.find(' ')!=l.npos) {
            return false;
        }

   
        if ((isalpha(l[0]) == false && isdigit(l[0]) == false) || (isalpha(l[(l.size() - 1)]) == false && isdigit(l[(l.size() - 1)]) == false)) {
            return false;
        }

        string special = "._%+-";

        for (const char & c : l) {

            if (isalpha(c) || isdigit(c)) continue;

            if (special.find(c) == string::npos)
                return false;
        }

        if (_HasConsecutive(l, '.')) {
            return false;
       }

        return true;
    } 
    static bool _IsValidDomain(string d) {
        if (d == "" || d.find(' ') != d.npos) {
            return false;
        }
        if ((isalpha(d[0]) == false && isdigit(d[0]) == false) || (isalpha(d[(d.size() - 1)]) == false && isdigit(d[(d.size() - 1)]) == false)) {
            return false;
        }
        for (const char & dChar : d) {
            if ((isalpha(dChar) == false && isdigit(dChar) == false && dChar != '-')) {
                return false;
            }

        }


        if (_HasConsecutive(d, '-')) {
            return false;
        }

        return true;

    }
    static bool _IsValidExten(string e) {
        if (e == "" || e.find(' ') != e.npos||e.size()<2) {
            return false;
        }
        if (clsString::IsLettersOnly(e)) {
            return true;
        }
        else {

            return false;

        }

    }
    static bool _IsValidEmail(string email) {

        if (email.empty() || email.size() > 100 || email.find(' ') != string::npos)
            return false;

        string localPart, domain, extention;

        size_t atPos = email.find('@');
        if (atPos == string::npos || atPos != email.rfind('@'))
            return false;

        vector <string> eparts = clsString::SplitString(email, "@");
        if (eparts.empty() || eparts.size() != 2)
            return false;

        localPart = eparts[0];

        if (_IsValidLocalPart(localPart) == false) {
            return false;
        }

        vector <string> domainAndExtention = clsString::SplitString(eparts[1], ".");

        if (domainAndExtention.size() != 2) {
            return false;
        }

        domain = domainAndExtention[0];
        extention = domainAndExtention[1];

        if (_IsValidDomain(domain) == false || _IsValidExten(extention) == false) {
            return false;
        }


        return true;

    }
 

protected:

    static string _GetPhoneNumber(const string& message, unsigned short mustSize) {
        string text;
        unsigned size;
        bool invalid;
        do {
            cout << message;
            getline(cin >> ws, text);

            size = clsString::Trim(text).size();
            if (size != mustSize) {
                cout << "The phone number must be " << mustSize << " digits.\n";
            }
            if (invalid = (!(_IsOnlyNumbers(text)))) {
                cout << "Invalid phone number. It must contain digits only (no spaces, letters, or special characters).\n";
            }
        } while (size != mustSize || invalid);
        return text;
    }

    static string _GetName(const string& message) {
        string name;
        bool repeated;
        do {     
            name = clsInputValidate::GetStringInSize(2, 20, message, "Invalid input. Name must be 2 to 20 letters. A single space or hyphen (-) is allowed for compound names.\n");
            repeated = !_IsValidName(name);
            if (repeated)
            {
                cout << "Invalid input. Name must be 2 to 20 letters only. No numbers or special characters allowed.\n"
                    << "Use at most one space or one hyphen (not both), and do not start or end with them.\n";
            }
        } while (repeated);

          return name;
        
    }
    static string _GetEmail(const string& message) {
        string email;
        bool repeated;

        do {     
            email = clsInputValidate::GetStringInSize(6, 100, message, "Email length is not valid. Please enter an email between 6 and 100 characters.\n");
            repeated = !_IsValidEmail(email);
            if (repeated)
            {
                cout << "Invalid email format. Please enter a valid email like name@example.com.\nMake sure there are no spaces, only one '@',and a valid domain and extension (e.g. gmail.com).\n";
            }
        } while (repeated);

         return email;
        
    }

};

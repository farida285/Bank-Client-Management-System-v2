#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DateLibrary.h"
using namespace std;
class clsUtil
{
private:
    static string  Return1_19NumberString(unsigned short number) {
        string arr[20] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven",
        "Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
        return (arr[number]);
    }
    static string  Return20_90NumberString(unsigned short number) {
        string arr[10] = { "","","Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
        return (arr[number]);
    }
public:
    static void  Srand()
    {
        //Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }
    static string EncryptString(string Sentence, short EncryptionIndex) {
        for (short i = 0; i < Sentence.length(); i++) {
            Sentence[i] = char(int(Sentence[i] - EncryptionIndex * 2));
        }
        return  Sentence;
    }
    static string DecryptString(string Sentence, short EncryptionIndex) {
        for (short i = 0; i < Sentence.length(); i++) {
            Sentence[i] = char(int(Sentence[i] + EncryptionIndex * 2));
        };
        return Sentence;

    }
    static int RandomNumber(int from, int to) {
        return (rand() % (to - from + 1) + from);
    }
    enum enrandom { SmallLetter, CapitalLetter, Digit, MixChars };
    static char GetRandomCharacter(enrandom request) {
        if (request == MixChars) {
            request = (enrandom)RandomNumber(0, 2);
        }
        switch (request)
        {
        case enrandom::SmallLetter:
            return char(RandomNumber(97, 122));
        case enrandom::CapitalLetter:
            return char(RandomNumber(65, 90));
        case enrandom::Digit:
            return char(RandomNumber(48, 57));
        default:
            return char(0);
            break;
        };

    }
    static string GenerateRandomWord(enrandom randomtype, unsigned short length) {
        string word = "";
        for (unsigned short i = 1; i <= length; i++) {

            word = word + GetRandomCharacter(randomtype);

        }
        return word;
    }
    static string GenerateKey(unsigned short numberofwords, unsigned short lengthOfWord, enrandom typeofChar = enrandom::CapitalLetter) {
        string key = "";
        for (unsigned short i = 1; i <= numberofwords; i++) {
            key = key + GenerateRandomWord(typeofChar, lengthOfWord);
            if (i != numberofwords) {
                key = key + '-';
            }
        }
        return key;
    }
    static void FillArrayWithRandomNumbers(int array[], unsigned short length, int from, int to) {
        for (unsigned short i = 0; i < length; i++) {
            array[i] = RandomNumber(from, to);
        };
    }

    static void FillArrayWithRandomWords(string array[], unsigned short length, unsigned short sizeOfWord, enrandom typeOfWord) {
        for (unsigned short i = 0; i < length; i++)
        {
            array[i] = GenerateRandomWord(typeOfWord, sizeOfWord);
        }

    }

    static void FillArrayWithRandomKeys(string array[], unsigned short length, unsigned short numberofwords, unsigned short sizeOfWord, enrandom typeofChar = enrandom::CapitalLetter) {
        for (unsigned short i = 0; i < length; i++)
        {
            array[i] = GenerateKey(numberofwords, sizeOfWord, typeofChar);
        }

    }

    static string  Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
        }
        return t;

    }
    static int MaxOfArray(int array[], unsigned short length) {
        int max = array[0];
        for (unsigned short i = 0; i < length; i++) {
            if (array[i] > max) {
                max = array[i];
            }
        }
        return max;
    }

    static int MinOfArray(int array[], unsigned short length) {
        int min = array[0];
        for (unsigned short i = 0; i < length; i++) {
            if (array[i] < min) {
                min = array[i];
            }
        }
        return min;

    }

    static void Swap(double& number1, double& number2) {
        double temp;
        temp = number1;
        number1 = number2;
        number2 = temp;
    };

    static void Swap(int& number1, int& number2) {
        int temp;
        temp = number1;
        number1 = number2;
        number2 = temp;
    };

    static void Swap(long& number1, long& number2) {
        long  temp;
        temp = number1;
        number1 = number2;
        number2 = temp;
    };


    static void Swap(string& s1, string& s2) {
        string  temp;
        temp = s1;
        s1 = s2;
        s2 = temp;
    };

    static void Swap(char& c1, char& c2) {
        char  temp;
        temp = c1;
        c1 = c2;
        c2 = temp;
    };

    static void Swap(bool& bool1, bool& bool2) {
        bool  temp;
        temp = bool1;
        bool1 = bool2;
        bool2 = temp;
    };

    static void Swap(clsDate& date1, clsDate& date2) {
        clsDate::SwapDates(date1, date2);
    }

    static void ShuffleArray(int array[], unsigned short length) {

        for (unsigned short i = 0; i < length; i++) {
            swap(array[RandomNumber(0, length - 1)], array[RandomNumber(0, length - 1)]);
        };

    }

    static void ShuffleArray(string array[], unsigned short length) {

        for (unsigned short i = 0; i < length; i++) {
            swap(array[RandomNumber(0, length - 1)], array[RandomNumber(0, length - 1)]);
        }

    }
    static int  NumberPositionInArray(int array[], unsigned short length, int number) {
        for (unsigned short i = 0; i < length; i++) {
            if (array[i] == number) {
                return i;
            }
        }
        return -1;

    }
    static bool IsNumberInArray(int array[], unsigned short length, int number) {
        return(NumberPositionInArray(array, length, number) != -1);

    }

    static string ReturnTextNumber(long long  number) {

        if (number == 0) {
            return "Zero";
        }

        if (number >= 1 && number <= 19) {
            return (Return1_19NumberString(number));
        }

        if (number >= 20 && number <= 99) {

            if ((number % 10) == 0) {
                return(Return20_90NumberString(number / 10));
            }
            else {
                return(Return20_90NumberString(number / 10)) + " " + ReturnTextNumber(number % 10);
            }
        }

        if (number >= 100 && number <= 999) {

            if ((number % 100) == 0) {
                if ((number / 100) == 1) {
                    return("One Hundred");
                }
                else {
                    return(ReturnTextNumber(number / 100) + " Hundreds");
                }
            }
            else {
                if ((number / 100) == 1) {
                    return("One Hundred " + ReturnTextNumber((number % 100)));
                }
                else {
                    return(ReturnTextNumber(number / 100) + " Hundreds " + ReturnTextNumber((number % 100)));
                }

            }
        }

        if (number >= 1000 && number <= 999999) {

            if ((number % 1000) == 0) {
                if ((number / 1000) == 1) {
                    return("One Thousand");
                }
                else {
                    return(ReturnTextNumber(number / 1000) + " Thousands");
                }
            }
            else {
                if ((number / 1000) == 1) {
                    return("One Thousand " + ReturnTextNumber((number % 1000)));
                }
                else {
                    return(ReturnTextNumber(number / 1000) + " Thousands " + ReturnTextNumber((number % 1000)));
                }

            }
        }

        if (number >= 1000000 && number <= 999999999) {
            if ((number % 1000000) == 0) {
                if ((number / 1000000) == 1) {
                    return("One Million");
                }
                else {
                    return(ReturnTextNumber(number / 1000000) + " Millions");
                }
            }
            else {
                if ((number / 1000000) == 1) {
                    return("One Million " + ReturnTextNumber((number % 1000000)));
                }
                else {
                    return(ReturnTextNumber(number / 1000000) + " Millions " + ReturnTextNumber((number % 1000000)));
                }

            }

        }
        if (number >= 1000000000 && number <= 999999999999) {
            if ((number % 1000000000) == 0) {
                if ((number / 1000000000) == 1) {
                    return("One Billion");
                }
                else {
                    return(ReturnTextNumber(number / 1000000000) + " Billions");
                }
            }
            else {
                if ((number / 1000000000) == 1) {
                    return("One Billion " + ReturnTextNumber((number % 1000000000)));
                }
                else {
                    return(ReturnTextNumber(number / 1000000000) + " Billions " + ReturnTextNumber((number % 1000000000)));
                }

            }
        }
        if (number >= 1000000000000 && number <= 999999999999999) {
            if ((number % 1000000000000) == 0) {
                if ((number / 1000000000000) == 1) {
                    return("One Trillion");
                }
                else {
                    return(ReturnTextNumber(number / 1000000000000) + " Trillions");
                }
            }
            else {
                if ((number / 1000000000000) == 1) {
                    return("One Trillion " + ReturnTextNumber((number % 1000000000000)));
                }
                else {
                    return(ReturnTextNumber(number / 1000000000000) + " Trillions " + ReturnTextNumber((number % 1000000000000)));
                }

            }
        }
        return "";
    }
};


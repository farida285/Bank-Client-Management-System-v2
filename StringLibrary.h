#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class clsString
{
private:

    string   _value;


    static  bool MyIsUpper(const char letter) {
        return(letter >= 'A' && letter <= 'Z');
    }

    static  bool MyIsLower(const char letter) {
        return(letter >= 'a' && letter <= 'z');
    }

    static  char MyToUpper(char letter) {
        if (letter >= 'a' && letter <= 'z') {
            letter -= 32;
        }
        return letter;
    }

    static bool MyIsVowel(const char& charcter) {
        char c = MyToLower(charcter);
        return(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }

    static bool MyIspunctuations(char charcter) {
        int c = (int)charcter;
        return((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126));
    }

    static  char MyToLower(char letter) {
        if (letter >= 'A' && letter <= 'Z') {
            letter += 32;
        }
        return letter;
    }

    static  char InvertChar(char letter) {
        return (MyIsUpper(letter)) ? MyToLower(letter) : MyToUpper(letter);

    }


    static bool  MyIsAlpha(char c) {
        return (MyIsLower(c) || MyIsUpper(c));
    }

public:


    clsString() {
        _value = "";
    };
    clsString(string value) {
        _value = value;
    };

    void SetValue(const string& value) {
        _value = value;
    }
    string GetValue() {
        return _value;
    }

    static string UpperAllString(string text) {
        for (unsigned int i = 0; i < text.size(); i++) {
            if (text[i] != ' ') {
                text[i] = MyToUpper(text[i]);
            }
        }
        return text;
    }

    void UpperAllString() {
        _value = UpperAllString(_value);
    }

    static string LowerAllString(string text) {
        for (unsigned int i = 0; i < text.size(); i++) {
            if (text[i] != ' ') {
                text[i] = MyToLower(text[i]);
            }
        }
        return text;
    }

    void LowerAllString() {
        _value = LowerAllString(_value);
    }

    static string InvertAllCharsINString(string myText) {
        for (unsigned int i = 0; i < myText.size(); i++) {
            myText[i] = InvertChar(myText[i]);
        }
        return myText;
    }

    void InvertAllCharsINString() {
        _value = InvertAllCharsINString(_value);
    }

    static string UpperCaseTheFirstLetterinEachWord(string text) {
        bool afterSpace = true;
        for (unsigned int i = 0; i < text.size(); i++) {
            if (text[i] != ' ' && afterSpace) {
                text[i] = MyToUpper(text[i]);
            }
            afterSpace = (text[i] == ' ') ? true : false;
        }
        return text;
    }

    void UpperCaseTheFirstLetterinEachWord() {
        _value = UpperCaseTheFirstLetterinEachWord(_value);
    }

    static string LowerCaseTheFirstLetterinEachWord(string text) {
        bool afterSpace = true;
        for (unsigned int i = 0; i < text.size(); i++) {
            if (text[i] != ' ' && afterSpace) {
                text[i] = MyToLower(text[i]);
            }
            afterSpace = (text[i] == ' ') ? true : false;
        }
        return text;
    }

    void LowerCaseTheFirstLetterinEachWord() {
        _value = LowerCaseTheFirstLetterinEachWord(_value);
    }

    static unsigned int CountSpecificCharInString(const string& myText, char charcter, bool matchCase = true) {

        unsigned int count = 0;
        if (matchCase) {
            for (unsigned int i = 0; i < myText.size(); i++) {
                if (myText[i] == charcter) {
                    count++;
                }
            }
        }
        else {
            char inverted = InvertChar(charcter);
            for (unsigned int i = 0; i < myText.size(); i++) {
                if (myText[i] == charcter || myText[i] == inverted) {
                    count++;
                }
            }
        }

        return count;
    }

    unsigned int CountSpecificCharInString(char charcter, bool matchCase = true) {
        return CountSpecificCharInString(_value, charcter, matchCase);
    }


    enum enWhatCount { smallLetters = 0, capitalLetters, allLetters };

    static unsigned int CountInString(const string& myText, enWhatCount whatCount = enWhatCount::allLetters) {
        unsigned int count = 0;
        for (unsigned int i = 0; i < myText.size(); i++) {
            if (whatCount == enWhatCount::allLetters && MyIsAlpha(myText[i])) {
                count++;
            }
            else if (MyIsUpper(myText[i]) && whatCount == enWhatCount::capitalLetters) {
                count++;
            }
            else if (MyIsLower(myText[i]) && whatCount == enWhatCount::smallLetters) {
                count++;
            }
        }
        return count;
    }

    unsigned int CountInString(enWhatCount whatCount = enWhatCount::allLetters) {
        return CountInString(_value, whatCount);
    }

    static unsigned int CountVowel(const string& text) {
        unsigned int s = text.size();
        unsigned int count = 0;
        for (unsigned int i = 0; i < s; i++) {
            if (MyIsVowel(text[i])) {
                count++;
            }
        }
        return count;

    }

    unsigned int CountVowel() {
        return  CountVowel(_value);
    }

    static unsigned int StringLength(const string& text) {
        unsigned int count = 0;
        while (text[count] != '\0') {
            count++;
        }
        return count;
    }

    unsigned int StringLength() {
        return StringLength(_value);
    }

    static unsigned short CountEachWordInString(string s1) {
        string word = "";
        string space = " ";
        unsigned short count = 0;
        int position = 0;
        while ((position = s1.find(space)) != string::npos) {
            word = s1.substr(0, position);
            if (word != "") {
                count++;
            }
            s1.erase(0, position + space.length());
        }
        if (s1 != "") {
            count++;
        }
        return count;

    }

    unsigned short CountEachWordInString() {
        return  CountEachWordInString(_value);
    }

    static vector<string> SplitString(string s1, string separator) {
        vector<string> vsplit;
        string word = "";
        size_t position = 0;

        while ((position = s1.find(separator)) != s1.npos)
        {
            word = s1.substr(0, position);
            if (word != "") {
                vsplit.push_back(word);
            }
            s1.erase(0, position + separator.length());
        }
        if (s1 != "") {
            vsplit.push_back(s1);
        }
        return vsplit;

    }

    vector<string> SplitString(string separator) {
        return SplitString(_value, separator);
    }

    static string  TrimLeft(const string& s1) {
        unsigned int size = s1.length();
        for (unsigned int i = 0; i < size; i++) {
            if (s1[i] != ' ') {
                return (s1.substr(i, size - i));
            }
        }
        return "";
    }

    void TrimLeft() {
        _value = TrimLeft(_value);
    }

    static string  TrimRight(const string& s1) {
        int size = s1.length();
        for (int i = size - 1; i >= 0; i--) {
            if (s1[i] != ' ') {
                return (s1.substr(0, i + 1));
            }
        }
        return "";

    }

    void  TrimRight() {
        _value = TrimRight(_value);
    }

    static string  Trim(const string& s1) {

        return (TrimLeft(TrimRight(s1)));

    }

    void Trim() {
        _value = Trim(_value);
    }

    static string Join(const vector <string>& vword, string separator = " ") {
        string words = "";
        for (size_t i = 0; i < vword.size(); i++) {
            words += vword[i];
            if (i != vword.size() - 1)
                words += separator;
        }
        return(words);
    }

    static string ReverseWordsInString(const string& s1) {
        vector<string> vsplit = SplitString(s1, " ");
        string words = "";
        for (int i = (int)vsplit.size() - 1; i >= 0; i--) {
            words += vsplit[i];
            if (i != 0)
                words += " ";
        }
        return(words);
    }

    void ReverseWordsInString() {
        _value = ReverseWordsInString(_value);
    }

    static string ReplaceWordInString(string s1, string origWord, string newWord, char extraSeparator = ' ') {

        size_t  position = 0;

        while ((position = s1.find(origWord, position)) != string::npos)
        {
            bool leftOK = (position == 0 || (s1[position - 1] == ' ' || s1[position - 1] == extraSeparator));
            bool rightOk = (position + origWord.size() == s1.size() || (s1[position + origWord.size()] == ' ' || s1[position + origWord.size()] == extraSeparator));
            if (leftOK && rightOk) {
                s1 = s1.replace(position, origWord.size(), newWord);
                position += newWord.size();
            }
            else {
                position += origWord.size();
            }

        }
        return s1;

    }

    void ReplaceWordInString(string origWord, string newWord, char extraSeparator = ' ') {
        _value = ReplaceWordInString(_value, origWord, newWord, extraSeparator);

    }

    static string RemoveAllPunctuations(const string& s1) {
        string s2 = "";
        unsigned int size = s1.length();
        s2.reserve(size);
        for (unsigned int i = 0; i < size; i++) {
            if (!MyIspunctuations(s1[i])) {
                s2 += s1[i];
            }
        }
        return s2;
    }

    void RemoveAllPunctuations() {
        _value = RemoveAllPunctuations(_value);
    }


    static bool IsLettersOnly(string& s) {

        for (const char& c : s) {
            if (!MyIsAlpha(c)) {
                return false;
            }
        }

        return true;


    }

    bool IsLettersOnly() {

        return clsString::IsLettersOnly(_value);

    }

    static bool ContainsNumber(const string& str)
    {
        for (char ch : str)
        {
            if (ch >= '0' && ch <= '9')
            {
                return true;
            }
        }
        return false;
    }

    bool ContainsNumber() {
        return clsString::ContainsNumber(_value);
    }
    
    static string EncryptString(string Sentence, short EncryptionKey) {
        for (short i = 0; i < Sentence.length(); i++) {
            Sentence[i] = char(int(Sentence[i] - (EncryptionKey * 2)));
        }
        return  Sentence;
    }
    static string DecryptString(string Sentence, short EncryptionKey ) {
        for (short i = 0; i < Sentence.length(); i++) {
            Sentence[i] = char(int(Sentence[i] + (EncryptionKey * 2)));
        };
        return Sentence;

    }

    void EncryptString( short EncryptionKey) {
 
        _value=  EncryptString (_value,EncryptionKey) ;
    }
    void DecryptString ( short EncryptionKey) {
     
        _value = DecryptString (_value, EncryptionKey) ;

    }

};


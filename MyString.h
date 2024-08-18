#pragma once


#include<iostream>
#include<vector>
#include<string>
#include"MyChar.h"
using namespace std;
using namespace MyChar;


namespace MyString {

    vector<string> SplitString(string S1, string Delim) {
        vector <string> vString;
        short pos;
        string sWord;

        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);

            if (sWord != "") {
                vString.push_back(sWord);
            }

            S1.erase(0, pos + Delim.length());
        }

        if (S1 != "") {
            vString.push_back(S1);
        }

        return vString;
    }

    bool IsVowl(char Letter) {
        Letter = tolower(Letter);
        return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
    }

    void PrintFirstLetterOfEachWord(string S1) {

        bool isFirstLetter = true;
        cout << "\nFirst Letters of this string : \n";
        for (int i = 0; i < S1.length(); i++) {

            if (S1[i] != ' ' && isFirstLetter) {
                cout << S1[i] << endl;
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        cout << endl;
    }

    void PrintEachWord(string S1) {
        bool isFirstWord = true;
        cout << "\nYour String Words are : \n";
        for (int i = 0; i < S1.length(); i++) {
            if (S1[i] != ' ' && isFirstWord) {
                cout << S1[i];
                if (S1[i + 1] != ' ')
                    continue;
            }
            cout << endl;
            isFirstWord = (S1[i] == ' ' ? true : false);
        }
    }

    string UpperFirstLetterOfEachWord(string S1) {
        bool isFirstLetter = true;
        for (int i = 0; i < S1.length(); i++) {
            if (S1[i] != ' ' && isFirstLetter) {
                S1[i] = toupper(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    string LowerFirstLetterOfEachWord(string S1) {
        bool isFirstLetter = true;
        for (int i = 0; i < S1.length(); i++) {
            if (S1[i] != ' ' && isFirstLetter) {
                S1[i] = tolower(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    string UpperAllString(string S1) {
        for (int i = 0; i < S1.length(); i++) {
            S1[i] = toupper(S1[i]);
        }

        return S1;
    }

    string LowerAllString(string S1) {
        for (int i = 0; i < S1.length(); i++) {
            S1[i] = tolower(S1[i]);
        }

        return S1;
    }

    string InvertAllStringLettersCase(string S1) {

        for (int i = 0; i < S1.length(); i++) {
            S1[i] = MyChar::InvertLetterCase(S1[i]);
        }

        return S1;
    }

    short CountCapitalLetters(string S1) {
        short Counter = 0;
        for (int i = 0; i < S1.length(); i++) {
            //isupper(S1[i]) ? Counter++ : 0;
            if (isupper(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short CountSmallLetters(string S1) {
        short Counter = 0;
        for (int i = 0; i < S1.length(); i++) {
            //islower(S1[i]) ? Counter++ : 0;
            if (islower(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short CountLetter(string S1, char Letter, bool MatchCase = true) {
        short Counter = 0;
        for (int i = 0; i < S1.length(); i++) {
            if (MatchCase) {
                if (S1[i] == Letter)
                    Counter++;
            }
            else {
                if (tolower(S1[i]) == tolower(Letter))
                    Counter++;
            }

        }

        return Counter;
    }

    short CountVowls(string S1) {
        short Counter = 0;
        for (int i = 0; i < S1.length(); i++) {
            if (IsVowl(S1[i]))
                Counter++;
        }

        return Counter;
    }

    void PrintVowlsInString(string S1) {
        cout << "\nVowls in string are :  ";
        for (int i = 0; i < S1.length(); i++) {
            if (IsVowl(S1[i]))
                cout << S1[i] << "  ";
        }

        cout << endl;
    }

    short CountWordsInString(string S1) {

        string delim = " ";
        short pos;
        string sWord;
        short Counter = 0;

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);

            if (sWord != "") {
                Counter++;
            }

            S1.erase(0, pos + delim.length());
        }

        if (S1 != "") {
            Counter++;
        }

        return Counter;
    }

    string TrimLeft(string S1) {

        for (int i = 0; i < S1.length(); i++) {
            if (S1[i] != ' ') {
                // S1.erase(0, i);
                 //break;
                return S1.substr(i, S1.length() - 1);
            }
        }

        return "";
    }

    string TrimRight(string S1) {

        int Length = S1.length() - 1;
        for (int i = Length; i >= 0; i--) {
            if (S1[i] != ' ') {
                /* S1.erase(i+1, Length);
                 break;*/
                return S1.substr(0, i + 1);
            }
        }

        return "";
    }

    string Trim(string S1) {
        return TrimLeft(TrimRight(S1));
    }

    string JoinString(vector <string>& vString, string Delim) {
        string S1;

        /*  for (int i = 0; i < vString.size(); i++) {
              if (i != vString.size()-1)
                  S1 += vString[i] + Delim;
              else
                  S1 += vString[i];
          }*/

        for (string& Words : vString) {
            S1 += Words + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    string JoinString(string arrString[], string Delim, int Length) {
        string S1 = "";
        for (int i = 0; i < Length; i++) {
            S1 += arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    string ReverseWordsInString(string S1) {
        vector <string> vString;
        string S2;

        vString = SplitString(S1, " ");

        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin()) {
            --iter;

            S2 += *iter + " ";
        }

        // S2 = S2.substr(0, S2.length() - 1); //Remove the last space
        S2 = TrimRight(S2);
        return S2;

    }

    string ReplaceWordInStringUsingBuiltInFunction(string S1, string StringToReplace, string sReplaceTo) {

        short pos = S1.find(StringToReplace);

        while (pos != std::string::npos) {
            S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
            pos = S1.find(StringToReplace);
        }


        return S1;
    }

    string ReplaceWordInStringUsingSplit(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true) {
        vector <string> vString;
        vString = SplitString(S1, " ");

        for (string& s : vString) {

            if (MatchCase) {
                if (s == StringToReplace) {
                    s = sReplaceTo;
                }
            }
            else {
                if (LowerAllString(s) == LowerAllString(StringToReplace)) {
                    s = sReplaceTo;
                }
            }

        }

        return JoinString(vString, " ");
    }

    string RemovePunctuationsFromString(string S1) {

        string S2 = "";
        for (short i = 0; i < S1.length(); i++) {
            if (!ispunct(S1[i])) {
                S2 += S1[i];
            }
        }

        return S2;
    }



}
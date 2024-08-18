#pragma once



#include<iostream>
#include<vector>
#include<string>
using namespace std;


namespace MyChar {

    char ReadCharacter() {
        char c;
        cout << "\nPlease Enter a Character \n";
        cin >> c;
        return c;
    }

    char InvertLetterCase(char C) {
        return isupper(C) ? tolower(C) : toupper(C);
    }


}

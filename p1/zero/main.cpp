#include <string>
#include <iostream>

using namespace std;
unsigned char key;

void next_key() {
    unsigned char k = 1;
    key = (key >> k) | (key << (sizeof(key) * 8 - k));
}

void seed(unsigned char new_key) {
    key = new_key;
}

char cipher(char symbol, char gamma) {
    return symbol ^ gamma;
}

int main() {
    register string str;
    register string crypt_str;
    register unsigned char r;

    cout << "Enter string: ";

flag: getline(cin, str, '\n');
      if (str.length() == 0) {
          cout << "Error" << endl;
          goto flag;
      }

    crypt_str = str;

flag1: cout << "Enter key: ";
    cin >> r;
    if (r == 0) {
        cout << "Error" << endl;
        goto flag1;
    }

    cin.clear();
    cin.ignore();
    cout << "key " << r << endl;
    seed(r);

    cout << "Encrypted text: ";
    for (int i = 0; i < str.length(); i++) {
        crypt_str[i] = cipher(str[i], key);
        next_key();
    }
    cout << crypt_str << endl;

    
flag2: cout << "Enter key: ";
    cin >> r;
    if (r == 0) {
        cout << "Error" << endl;
        goto flag2;
    }

    cin.clear();
    cin.ignore();
    cout << "key " << r << endl;
    seed(r);

    cout << "Decrypted text: ";
    for (int i = 0; i < str.length(); i++) {
        str[i] = cipher(crypt_str[i], key);
        next_key();
    }
    cout << str << endl;

    return 0;
}


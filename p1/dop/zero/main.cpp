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
    getline(cin, str, '\n');
    crypt_str = str;

    cout << "Enter key: ";
    cin >> r;
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

    cout << "Enter key: ";
    cin >> r;
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


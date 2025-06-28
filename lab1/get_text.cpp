#include <iostream>
#include <string>

char* get_text() {
    char* temp = new char[9];
    for (int i = 0; i < 8; i++) {
        temp[i] = getchar();
    }
    temp[8] = '\0';
    return temp;
}

int main() {
    std::cout << get_text();
    return 0;
}

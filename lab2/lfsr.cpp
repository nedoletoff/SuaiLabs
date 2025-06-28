#include <iostream>
#include <fstream>
#include <bitset>
#include <ctime>
using namespace std;

#define MAX_BITSET_SIZE 15

#define FIRST_POLYNOMIAL_SIZE 4
#define SECOND_POLYNOMIAL_SIZE 7
#define THIRD_POLYNOMIAL_SIZE 9
#define SEED 0

class LFSR {
    private:
        bitset<MAX_BITSET_SIZE> mask;
        bitset<MAX_BITSET_SIZE> values;

        int size = 0;
        enum Mode {
            started,
            notStarted
        };
        Mode mode = notStarted;

    public:
        LFSR(bitset<MAX_BITSET_SIZE> m, int s) {
            size = s;
            for (int i = 1; i <= size; i++) {
                mask[i - 1] = m[i];
            }
        }

        bool getNext() {
            if (mode == notStarted) {
                initLFSR();
                mode = started;
            }

            bool res = values[size - 1] == 1 ? true : false;
            bitset<MAX_BITSET_SIZE> tmp;
            tmp.reset();

            for (int i = 0; i < size; i++) {
                tmp[i] = mask[i] & values[i];
            }

            for (int i = 1; i < size; i++) {
                tmp[0] = tmp[0] ^ tmp[i];
            }

            values <<= 1;
            values[size] = 0;
            values[0] = tmp[0] == 1 ? true : false;

            return res;
        }

        void initLFSR() {
            srand(SEED);
            for (int i = 0; i < size; i++)
                values[i] = rand() % 2;
        }
    };

int main() {
    //polynomial 4, 7, 9
    bitset<MAX_BITSET_SIZE> firstPolynomial{"11001"}; //x^4 + x + 1
    bitset<MAX_BITSET_SIZE> secondPolynomial{"10010001"}; // x^7 + x^3 + 1
    bitset<MAX_BITSET_SIZE> thirdPolynomial{"1000100001"};// x^9 + x^4 + 1

    LFSR* lfsr1 = new LFSR(firstPolynomial, FIRST_POLYNOMIAL_SIZE);
    LFSR* lfsr2 = new LFSR(secondPolynomial, SECOND_POLYNOMIAL_SIZE);
    LFSR* lfsr3 = new LFSR(thirdPolynomial, THIRD_POLYNOMIAL_SIZE);

    int limit = 100;
    bool res1;
    bool res2;
    bool res3;
    int counter1 = 0;
    int counter0 = 0;
    bool res;
    std::string resString = "";
    cout << "LFSR:" << endl;
    for (int i = 1; i <= limit; i++) {
        res1 = lfsr1->getNext();
        res2 = lfsr2->getNext();
        res3 = lfsr3->getNext();

        res = ((res1 & res2) ^ (res2 & res3) ^ (res1 & res3));

        resString += std::to_string(res) + ", ";
        if (res)
            counter1++;
        else
            counter0++;
        cout << res;
        if (i % 50 == 0)
            cout << ",\n";
        else
            cout << ", ";
    }
    cout << "Counter 0: " << counter0 << endl;
    cout << "Counter 1: " << counter1 << endl;

    resString.erase(resString.end() - 2);
    std::ofstream out;
    out.open("100bit.txt");
    if (out.is_open()) {
        out << resString << std::endl;
    }
    out.close();

    return 0;
}
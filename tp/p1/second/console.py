def getResult1(text):
    char = text[0]
    res = 0
    for c in text:
        if c == char:
            res += 1
    return res


def getResult2(text, char_a, char_b):
    return [(text[0] == char_a), (text[-1] == char_b)]


def func1():
    num = input("Enter the number ")
    while not num.isdigit():
        print("Number contains unsupported symbols")
        num = input("Enter the number ")
    print("The first digit occurred {} times".format(getResult1(num)))

    num_a = input("\nEnter the digit a ")
    while not num_a.isdigit() or len(num_a) != 1:
        print("It is not a digit")
        num_a = input("Enter the digit ")

    num_b = input("\nEnter the digit b ")
    while not num_b.isdigit() or len(num_b) != 1:
        print("It is not a digit")
        num_b = input("Enter the digit ")

    print("\nNumber starts with A({}) - {} and end with B({}) - {}".format(
        num_a, getResult2(num, num_a, num_b)[0], num_b, getResult2(num, num_a, num_b)[1]))


def func2():
    for i in range(1000, 10000):
        for j in range(10):
            if i.__str__().count(j.__str__()) == 2:
                print(i, end=' ')


if __name__ == '__main__':
    func2()

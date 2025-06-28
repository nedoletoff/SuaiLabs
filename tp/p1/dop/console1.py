def check_text(text):
    if text.isdigit():
        print("Text contains number")
        return True
    if len(text) == 0:
        print("Text is empty")
        return True
    if not text.isalpha():
        print("Text contains not supported symbols")
        return True
    return False


def write_unicode(text1, text2):
    min_len = min(len(text1), len(text2))
    max_len = max(len(text1), len(text2))
    rest_len = max_len - min_len
    unicode_name = text1[:min_len]
    unicode_name = unicode_name.encode("utf-8")
    unicode_surname = text2[:min_len]
    unicode_surname = unicode_surname.encode("utf-8")
    if rest_len == 0:
        rest = ""
    elif max_len == len(text1):
        rest = text1[-rest_len:]
    else:
        rest = text2[-rest_len:]

    res = bytearray()
    un = ""
    for x in unicode_name:
        un += hex(x)
        res.append(x)
        un += " "

    us = ""
    i = 0
    for x in unicode_surname:
        us += hex(x)
        res[i] ^= x
        i += 1
        us += " "

    print("Unicode name: ", un)
    print("Unicode surname: ", us)
    print("Rest of the string: ", rest)
    print("Result:", res.decode("utf-8"))


def main():
    name = input("Enter name: ")
    while check_text(name):
        name = input("Enter name: ")

    surname = input("Enter surname: ")
    while check_text(surname):
        surname = input("Enter surname: ")

    write_unicode(name, surname)


if __name__ == "__main__":
    main()

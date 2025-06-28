def sum_chars(text_chr: str, key_chr: str) -> str:
    if not key_chr.isalpha():
        raise Exception("Key contains wrong symbol")
    if text_chr.isalpha():
        text_chr = text_chr.lower()
        key_chr = key_chr.lower()
        temp = ord(key_chr) - ord('a') + 1
        if temp + ord(text_chr) > ord('z') + 1:
            temp = ord(key_chr) - ord('z')
        return chr(temp + ord(text_chr))

    else:
        return text_chr


def sub_chars(text_chr: str, key_chr: str) -> str:
    if not key_chr.isalpha():
        raise Exception("Key contains wrong symbol")
    if text_chr.isalpha():
        text_chr = text_chr.lower()
        key_chr = key_chr.lower()
        temp = ord(key_chr) - ord('a') + 1
        if - temp + ord(text_chr) < ord('a'):
            temp = ord(key_chr) - ord('z')
        return chr(-temp + ord(text_chr))

    else:
        return text_chr


def cipher(text: str, key: str) -> str:
    res = list()
    ltext = list(text)
    lkey = list(key)
    for i in range(len(text)):
        res.append(sum_chars(ltext[i], lkey[i % len(lkey)]))
    return ''.join(res)


def decipher(text, key) -> str:
    res = list()
    ltext = list(text)
    lkey = list(key)
    for i in range(len(text)):
        res.append(sub_chars(ltext[i], lkey[i % len(lkey)]))
    return ''.join(res)


if __name__ == '__main__':
    print(cipher('string with some text_label', 'tskdh'))
    print(decipher('mmcluz hlbb drtx ehfn_vdixe', 'tskdh'))
    print(cipher('qwertyuiopasdfghjklzxcvbnm', 'tskdh'))
    print(decipher('kppvbsntsxulojobcvphrvgfvg', 'tskdh'))


import random

import matplotlib.pyplot as plt


def Berlekamp_Massey_algorithm(sequence: list) -> (str, int):
    N = len(sequence)
    s = sequence[:]

    for k in range(N):
        if s[k] == 1:
            break
    f = {k + 1, 0}
    l = k + 1

    g = {0}
    a = k
    b = 0

    for n in range(k + 1, N):
        d = 0
        for ele in f:
            d ^= s[ele + n - l]

        if d == 0:
            b += 1
        else:
            if 2 * l > n:
                f ^= set([a - b + ele for ele in g])
                b += 1
            else:
                temp = f.copy()
                f = set([b - a + ele for ele in f]) ^ g
                l = n + 1 - l
                g = temp
                a = b
                b = n - l + 1

    def print_poly(polynomial):
        result = ''
        lis = sorted(polynomial, reverse=True)
        for i in lis:
            if i == 0:
                result += '1'
            else:
                result += 'x^%s' % str(i)

            if i != lis[-1]:
                result += ' + '

        return result

    return print_poly(f), l


def read_sequence(filename: str) -> list:
    text = ''
    with open(filename, "r") as f:
        for line in f:
            text += line
    sequence = text.split(", ")
    sequence.pop(-1)
    sequence = [int(i) for i in sequence]
    return sequence


def get_symbols(num: int, sequence: list) -> list:
    symbols = sequence[:num]
    return symbols


def draw_plot(linear_list: list, lenght_list: list, name="plot"):
    temp = [x / 2 for x in lenght_list]
    plt.plot(lenght_list, linear_list)
    plt.plot(lenght_list, temp, 'r')
    plt.xlabel('Length of sequence')
    plt.ylabel('Linear complexity')
    plt.title(f'Linear complexity {name}')
    plt.savefig(name + ".png")
    plt.show()


def write_result(seq: list, filename: str):
    with open(filename, "w") as f:
        for i in range(1, len(seq) + 1):
            temp_poly, temp_linear = Berlekamp_Massey_algorithm(get_symbols(i, seq))
            f.write(f"Length: {i:3d}, \tLinear: {temp_linear:2d}, \tPolynomial: {temp_poly};\n")


def generate_file_with_random_sequence(len_of_sequence: int, filename: str):
    with open(filename, "w") as f:
        for i in range(len_of_sequence - 1):
            f.write(str(random.randint(0, 1)))
            f.write(", ")
        f.write(str(random.randint(0, 1)))


def get_linear(seq: list) -> list:
    linear_list = []
    for i in range(1, len(seq) + 1):
        _, linear = Berlekamp_Massey_algorithm(get_symbols(i, seq))
        linear_list.append(linear)
    return linear_list


if __name__ == '__main__':
    # generate_file_with_random_sequence(100, "random_seq.txt")
    seq = read_sequence("random_seq.txt")
    seq1 = read_sequence("sequence.txt")

    linear_list = get_linear(seq)
    linear_list1 = get_linear(seq1)

    write_result(seq, "result_random_seq.txt")
    write_result(seq1, "result_seq.txt")
    draw_plot(linear_list, list(range(1, len(seq) + 1)), "random sequence")
    draw_plot(linear_list1, list(range(1, len(seq1) + 1)), "generated sequence")

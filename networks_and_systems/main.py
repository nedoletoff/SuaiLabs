import itertools
import json
import math
import random
import matplotlib.pyplot as plt
import threading
import time


class Coder:
    def __init__(self, polynomial='1101', d=3, k=4, n=7,
                 vector_e=None):  # input from the highest degree of the polynomial in left
        if vector_e is None:
            vector_e = [0, 0, 0, 0, 0, 0, 0]
        # vector_e = vector_e[::-1]
        self.polynomial = []
        for symbol in polynomial:
            if symbol == '1':
                self.polynomial.append(1)
            elif symbol == '0':
                self.polynomial.append(0)
            else:
                raise Exception('Неправильный ввод полинома')
        self.polynomial = self.polynomial[::-1]  # highest degree of the polynomial in right
        self.k = k
        self.n = n
        self.d = d
        self.vector_e = vector_e

    def __str__(self):
        res = ''
        for i, symbol in enumerate(self.polynomial):
            if symbol == 1:
                res += 'x^' + str(i)
                res += '+'
        res = res[:-1]
        res += ' = ' + str(self.polynomial)
        res += '\n'
        res += 'k = ' + str(self.k) + '\n'
        res += 'n = ' + str(self.n) + '\n'
        res += 'd = ' + str(self.d) + '\n'
        # res += 'Вектор ошибки: ' + str(self.vector_e) + '\n'
        return res

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        return self.polynomial == other.polynomial and self.k == other.k and self.n == other.n and \
               self.vector_e == other.vector_e and self.d == other.d

    def code(self, message: str) -> list:
        # highest degree of the message in right
        m = []
        for i in message:
            if i == '1':
                m.append(1)
            elif i == '0':
                m.append(0)
            else:
                raise Exception('Неправильный ввод последовательности')
        r = len(self.polynomial) - 1
        mes = [0] * r + m
        _, c = poly_div_mod(mes, self.polynomial)
        a = poly_sum(c, mes)
        return a

    def add_errors(self, a: list) -> list:
        _a = a.copy()
        for i in range(len(_a)):
            _a[i] = (_a[i] + self.vector_e[i]) % 2
        return _a

    def decode(self, b: list) -> bool:
        _, s = poly_div_mod(b, self.polynomial)
        # print(f'{s=}')
        for i in s:
            if i != 0:
                return True
        return False


def poly_prod(a_p: list, b_p: list) -> list:  # highest degree of the polynomial in right
    a_p = a_p.copy()
    b_p = b_p.copy()
    # highest degree of the polynomial in left
    a_p = a_p[::-1]
    b_p = b_p[::-1]
    res = [0] * (len(a_p) + len(b_p) - 1)
    for i in range(len(a_p)):
        for j in range(len(b_p)):
            res[i + j] += (a_p[i] * b_p[j])
    res = res[::-1]
    # highest degree of the polynomial in right
    return [x % 2 for x in res]


def poly_div_mod(a_p: list, b_p: list) -> (list, list):  # highest degree of the polynomial in right
    a_p = a_p.copy()
    b_p = b_p.copy()
    a_p = a_p[::-1]
    b_p = b_p[::-1]
    # highest degree of the polynomial in left
    while a_p[0] == 0 and len(a_p) > 1:
        a_p = a_p[1:]
    while b_p[0] == 0 and len(b_p) > 1:
        b_p = b_p[1:]
    # delete the leading zeros
    a_deg = len(a_p) - 1
    b_deg = len(b_p) - 1
    temp_deg = a_deg - b_deg
    quotient = []
    _a = a_p.copy()
    while temp_deg >= 0:
        _b = b_p.copy() + [0] * temp_deg
        if (_a[0] + _b[0]) == 1:
            temp_deg -= 1
            quotient.append(0)
            _a = _a[1:]
            continue

        for i, ab in enumerate(zip(_a, _b)):
            a_i = ab[0]
            b_i = ab[1]
            _a[i] = (a_i + b_i) % 2

        quotient.append(1)
        temp_deg -= 1
        _a = _a[1:]
        a_p = _a.copy()

    # delete the leading zeros
    while len(a_p) > 1 and a_p[0] == 0:
        a_p = a_p[1:]
    while len(quotient) > 1 and quotient[0] == 0:
        quotient = quotient[1:]
    # highest degree of the polynomial in right
    quotient = quotient[::-1]
    a_p = a_p[::-1]
    return quotient, a_p


def poly_sum(a_p: list, b_p: list) -> list:
    a_p = a_p.copy()
    b_p = b_p.copy()
    if len(a_p) < len(b_p):
        a_p, b_p = b_p, a_p
    for i in range(len(b_p)):
        a_p[i] += b_p[i]
    res = [x % 2 for x in a_p]
    return res


def main():
    coder = Coder()
    print(coder)
    l = '1001'
    print("a = " + str(a := coder.code(l)))
    print("b  = " + str(b := coder.add_errors(a)))
    print(f'E = : {coder.decode(b)}\n')

    coder.vector_e = [1, 0, 1, 0, 0, 0, 1]
    print(coder)
    print("a = " + str(a := coder.code(l)))
    print("b  = " + str(b := coder.add_errors(a)))
    print(f'E = : {coder.decode(b)}')


def get_pr_error_not_find():
    coder = Coder()
    print(coder)
    errors = 0
    all_var = 0
    temp_vector_e = list(range(7))
    all_combinations = []
    '''
    all_combinations = list(itertools.combinations(temp_vector_e, 1)) + list(itertools.combinations(temp_vector_e, 2)) + \
                    list(itertools.combinations(temp_vector_e, 3))
    '''
    for i in range(4, 7 + 1):
        all_combinations += list(itertools.combinations(temp_vector_e, i))
    all_vectors_e = []
    for i in all_combinations:
        temp_vector_e = [0] * 7
        for j in i:
            temp_vector_e[j] = 1
        all_vectors_e.append(temp_vector_e.copy())

    l = '1001'
    print("a = " + str(a := coder.code(l)))
    for i in all_vectors_e:
        coder.vector_e = i
        # print("b  = " + str(b := coder_.add_errors(a)))
        # print(f'E = : {coder_.decode(b)}')
        b = coder.add_errors(a)
        if coder.decode(b):
            errors += 1
        else:
            print(f'vector_e: {i}')
        all_var += 1
    print(f'pr(нашел ошибку) = {errors}/{all_var} = {errors / all_var}')


def get_pr_error_in_decode_random(epsilon, p_error, len_l, coder_, res=None):
    if res is None:
        res = [0]
    N_examples = 9 / (4 * math.pow(epsilon, 2))
    N_examples = int(N_examples)
    errors_n = 0
    for i in range(N_examples):
        l = ''
        for j in range(len_l):
            l += str(random.randint(0, 1))
        a = coder_.code(l)

        vector_e = [0] * len(a)
        for j in range(len(a)):
            if random.random() < p_error:
                vector_e[j] = 1
        coder_.vector_e = vector_e

        b = coder_.add_errors(a)
        if not (coder_.decode(b)) and vector_e.__contains__(1):
            errors_n += 1
    res[0] = errors_n / N_examples
    return errors_n, N_examples


def get_pr_error_in_decode_const(epsilon, p_error, coder_, l, res=None):
    if res is None:
        res = [0]
    N_examples = 9 / (4 * math.pow(epsilon, 2))
    N_examples = int(N_examples)
    errors_n = 0
    for i in range(N_examples):
        a = coder_.code(l)

        vector_e = [0] * len(a)
        for j in range(len(a)):
            if random.random() < p_error:
                vector_e[j] = 1
        coder_.vector_e = vector_e

        b = coder_.add_errors(a)
        if not (coder_.decode(b)) and vector_e.__contains__(1):
            errors_n += 1
    res[0] = errors_n / N_examples
    return errors_n, N_examples


def test_poly():
    a = [0, 0, 0, 1, 1, 1, 1]
    l = [1, 0, 1, 1]
    print(poly_div_mod(a, l))
    print(poly_div_mod([0, 1, 1, 0], [1, 1]))
    print(p := poly_prod([1, 1, 1, 1], [1, 1]))
    print(p := poly_sum(p, [1, 1, 1, 1, 1]))
    print(poly_div_mod(p, [1, 1]))


def find_error():
    coder = Coder('11101', 4, 3, 7)
    print(coder)
    m = '11111'
    temp_vector_e = list(range(9))
    all_combinations = list(itertools.combinations(temp_vector_e, 2))
    all_vectors_e = []
    for i in all_combinations:
        temp_vector_e = [0] * 9
        for j in i:
            temp_vector_e[j] = 1
        all_vectors_e.append(temp_vector_e.copy())

    a = coder.code(m)
    print(a)
    for vector_e in all_vectors_e:
        coder.vector_e = vector_e
        b = coder.add_errors(a)
        if not coder.decode(b) and vector_e.__contains__(1):
            print(f'a: {a}')
            print(f'vector_e: {vector_e}')
            print(f'b: {b}')


def no_threading():
    probabilities = []
    m1, m2, m3 = [], [], []
    coder = Coder()
    print(coder)
    for i in range(11):
        probabilities.append(i / 10)

    for j in range(2, 7 + 1):
        #print('len l = ' + str(j))
        res = []
        for p in probabilities:
            #print('p = ' + str(p))
            errors_n, N_examples = get_pr_error_in_decode_random(0.02, p, j, coder)
            #print(f'{errors_n=}, {N_examples=}, {errors_n / N_examples=:.2f}')
            res.append(errors_n / N_examples)
        plt.plot(probabilities, res, label=f'len l= {j}')
        m1.append(res)
    plt.legend()
    plt.xlabel('p ошибки при передаче')
    plt.ylabel('pr(не нашел ошибку)')
    plt.title('График ошибок декодирования k = 4 random')
    plt.grid()
    plt.savefig('graph_rand.png')
    # plt.show()
    plt.close()

    l1_s = ['11', '110', '1101', '11001', '110001', '1100001']
    l2_s = ['10', '101', '1010', '10100', '101000', '1010001']

    for l in l1_s:
        #print(f'{l=}')
        res = []
        for p in probabilities:
            #print('p = ' + str(p))
            errors_n, N_examples = get_pr_error_in_decode_const(0.02, p, coder, l)
            #print(f'{errors_n=}, {N_examples=}, {errors_n / N_examples=:.2f}')
            res.append(errors_n / N_examples)
        plt.plot(probabilities, res, label=f'len l= {len(l)}')
        m2.append(res)
    plt.legend()
    plt.xlabel('p ошибки при передаче')
    plt.ylabel('pr(не нашел ошибку)')
    plt.title('График ошибок декодирования k = 4 const 1')
    plt.grid()
    plt.savefig('graph_const1.png')
    # plt.show()
    plt.close()
    for l in l2_s:
        #print(f'{l=}')
        res = []
        for p in probabilities:
            #print('p = ' + str(p))
            errors_n, N_examples = get_pr_error_in_decode_const(0.02, p, coder, l)
            #print(f'{errors_n=}, {N_examples=}, {errors_n / N_examples=:.2f}')
            res.append(errors_n / N_examples)
        plt.plot(probabilities, res, label=f'len l= {len(l)}')
        m3.append(res)
    plt.legend()
    plt.xlabel('p ошибки при передаче')
    plt.ylabel('pr(не нашел ошибку)')
    plt.title('График ошибок декодирования k = 4 const 2')
    plt.grid()
    plt.savefig('graph_const2.png')
    # plt.show()
    plt.close()
    res = [[] for _ in range(len(m1))]
    for i in range(len(m1)):
        for j in range(len(m1[i])):
            res[i].append(max(abs(m1[i][j] - m2[i][j]), abs(m2[i][j] - m3[i][j]), abs(m1[i][j] - m3[i][j])))

    for i in range(len(res)):
        plt.plot(probabilities, res[i], label=f'max diff l={i+2}')

    plt.plot(probabilities, [0.02] * len(probabilities), label='epsilon')
    plt.legend()
    plt.xlabel('p ошибки при передаче')
    plt.ylabel('разница')
    plt.title('График разницы')
    plt.grid()
    plt.savefig('graph_diff.png')
    # plt.show()
    plt.close()


if __name__ == '__main__':
    no_threading()

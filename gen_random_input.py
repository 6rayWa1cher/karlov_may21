import random


def gen_long_number(length):
    out = 0
    for _ in range(length):
        out = out * 10 + random.randint(0, 10)
    return out


def main():
    a_len = random.randint(10000, 20000)
    b_len = random.randint(10000, 20000)
    with open("input.txt", "w") as out:
        a = gen_long_number(a_len)
        b = gen_long_number(b_len)
        c = a * b
        for x in [a, b, c]:
            print(x, file=out)


if __name__ == '__main__':
    main()

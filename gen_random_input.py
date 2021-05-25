import random


def gen_long_number(length):
    out = 0
    for _ in range(length):
        out = out * 10 + random.randint(0, 10)
    return out


def main():
    a_len = 15000
    b_len = 30000
    with open("input.txt", "w") as out:
        a = gen_long_number(a_len)
        b = gen_long_number(b_len)
        c = a * b
        for x in [a, b, c]:
            print(x, file=out)


if __name__ == '__main__':
    main()

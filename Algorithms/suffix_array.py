# python3
import sys


def build_suffix_array(text):
    result = [i for i in range(len(text))]
    result.sort(key=lambda x: text[x:])
    return result


if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    print(" ".join(map(str, build_suffix_array(text))))

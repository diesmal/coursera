# python3
import sys

def BWT(text):
    text_length = len(text)
    shifted_texts = []

    for offset in range(text_length):
        text_break = text_length - offset - 1
        shifted_text = text[text_break:] + text[:text_break]
        shifted_texts.append(shifted_text)

        shifted_texts.sort()

    result = ''.join(shifted_text[text_length - 1] for shifted_text in shifted_texts)

    return result

if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    print(BWT(text))
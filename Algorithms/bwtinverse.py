# python3
import sys

def InverseBWT(bwt):
    bwt_length = len(bwt)
    first_colum_idx = [i for i in range(bwt_length)]
    first_colum_idx.sort(key=lambda x: bwt[x])
    last_colum_links = [0] * bwt_length
    for idx in first_colum_idx:
        last_colum_links[first_colum_idx[idx]] = idx
    result = ['$'] * bwt_length

    cur_idx = 0
    for idx in range(bwt_length):
        symbol = bwt[first_colum_idx[cur_idx]]
        result[bwt_length - idx - 1] = symbol
        cur_idx = last_colum_links[cur_idx]

    return ''.join(x for x in result)


if __name__ == '__main__':
    bwt = sys.stdin.readline().strip()
    print(InverseBWT(bwt))
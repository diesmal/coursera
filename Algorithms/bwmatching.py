# python3
import sys

symbolToNumber = {
    '$' : 0,
    'A' : 1,
    'C' : 2,
    'G' : 3,
    'T' : 4
}


def PreprocessBWT(bwt):
    bwt_length = len(bwt)
    first_colum_idx = [i for i in range(bwt_length)]
    first_colum_idx.sort(key=lambda x: bwt[x])

    starts = [-1] * len(symbolToNumber)
    endSymbol = bwt[first_colum_idx[len(first_colum_idx) - 1]]
    for idx in range(len(first_colum_idx)):
        symbol = bwt[first_colum_idx[idx]]
        symbol_key = symbolToNumber[symbol]
        if starts[symbol_key] == -1:
            starts[symbol_key] = idx
            if symbol == endSymbol:
                break

    occ_count_before = []

    for idx in range(len(symbolToNumber)):
        occ_count_before.append([0])

    for idx in range(len(bwt)):
        symbol = bwt[idx]
        symbol_key = symbolToNumber[symbol]
        if idx != 0:
            for key_idx in range(len(symbolToNumber)):
                occ_count_before[key_idx].append(occ_count_before[key_idx][idx - 1])
        occ_count_before[symbol_key][idx] = occ_count_before[symbol_key][idx] + 1

    return [starts, occ_count_before]


def CountOccurrences(pattern, bwt, starts, occ_counts_before):
    """
  Compute the number of occurrences of string pattern in the text
  given only Burrows-Wheeler Transform bwt of the text and additional
  information we get from the preprocessing stage - starts and occ_counts_before.
  """
    # Implement this function yourself

    top = 0
    bottom = len(bwt) - 1
    symbol_idx = len(pattern) - 1

    while top <= bottom:
        if symbol_idx >= 0:
            symbol = pattern[symbol_idx]
            symbol_idx = symbol_idx - 1
            symbol_key = symbolToNumber[symbol]

            before_top = 0
            if top > 0:
                before_top = occ_counts_before[symbol_key][top - 1]
            before_bottom = occ_counts_before[symbol_key][bottom]
            if before_bottom - before_top > 0:
                top = starts[symbol_key] + before_top
                bottom = starts[symbol_key] + before_bottom - 1
            else:
                return 0
        else:
            return bottom - top + 1
    return 0


if __name__ == '__main__':
    bwt = sys.stdin.readline().strip()
    pattern_count = int(sys.stdin.readline().strip())
    patterns = sys.stdin.readline().strip().split()
    # Preprocess the BWT once to get starts and occ_count_before.
    # For each pattern, we will then use these precomputed values and
    # spend only O(|pattern|) to find all occurrences of the pattern
    # in the text instead of O(|pattern| + |text|).
    starts, occ_counts_before = PreprocessBWT(bwt)
    occurrence_counts = []
    for pattern in patterns:
        occurrence_counts.append(CountOccurrences(pattern, bwt, starts, occ_counts_before))
    print(' '.join(map(str, occurrence_counts)))

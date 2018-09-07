import java.lang.reflect.Array;
import java.util.*;
import java.io.*;
import java.util.zip.CheckedInputStream;

public class SuffixArrayLong {
    class FastScanner {
        StringTokenizer tok = new StringTokenizer("");
        BufferedReader in;

        FastScanner() {
            in = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() throws IOException {
            while (!tok.hasMoreElements())
                tok = new StringTokenizer(in.readLine());
            return tok.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    private static final int AlphabetCount = 5;

    int numberFromLetter(char letter) {
        switch (letter) {
            case 'A':
                return 1;
            case 'C':
                return 2;
            case 'G':
                return 3;
            case 'T':
                return 4;
        }
        return 0;
    }

    int[] sortCharacters(String text) {
        int textLength = text.length();
        int[] order = new int[textLength];
        int[] count = new int[AlphabetCount];
        Arrays.fill(count, 0);

        for (char letter : text.toCharArray()) {
            count[numberFromLetter(letter)]++;
        }
        for (int idx = 1; idx < AlphabetCount; idx++) {
            count[idx] += count[idx - 1];
        }
        for (int idx = textLength - 1; idx >= 0; idx--) {
            int letterIdx = numberFromLetter(text.charAt(idx));
            count[letterIdx]--;
            order[count[letterIdx]] = idx;
        }
        return order;
    }

    int[] computeCharClasses(String text, int[] order) {
        int textLength = text.length();
        int[] cls = new int[textLength];
        cls[order[0]] = 0;
        for (int idx = 1; idx < textLength; idx++) {
            int curOrd = order[idx];
            int prvOrd = order[idx - 1];

            if (text.charAt(curOrd) != text.charAt(prvOrd)) {
                cls[curOrd] = cls[prvOrd] + 1;
            } else {
                cls[curOrd] = cls[prvOrd];
            }
        }
        return cls;
    }

    int[] sortDoubled(String text, int L, int[] order, int[] cls) {
        int textLength = text.length();
        int[] count = new int[textLength];
        Arrays.fill(count, 0);
        int[] newOrder = new int[textLength];

        for (int idx = 0; idx < textLength; idx++) {
            count[cls[idx]] = count[cls[idx]] + 1;
        }
        for (int idx = 1; idx < textLength; idx++) {
            count[idx] += count[idx - 1];
        }
        for (int idx = textLength - 1; idx >= 0; idx--) {
            int start = (order[idx] - L + textLength) % textLength;
            int cl = cls[start];
            count[cl]--;
            newOrder[count[cl]] = start;
        }
        return newOrder;
    }

    int[] updateClasses(int[] newOrder,  int[] cls, int L) {
        int orderLength = newOrder.length;
        int[] newCls = new int[orderLength];
        newCls[newOrder[0]] = 0;

        for(int idx = 1; idx < orderLength; idx++) {
            int cur = newOrder[idx];
            int prev = newOrder[idx - 1];
            int mid = cur + L;
            int midPrev = (prev + L) % orderLength;

            if (cls[cur] != cls[prev]) {
                newCls[cur] = newCls[prev] + 1;
            } else if (cls[mid] != cls[midPrev]) {
                newCls[cur] = newCls[prev] + 1;
            } else {
                newCls[cur] = newCls[prev];
            }
        }
        return newCls;
    }


    // Build suffix array of the string text and
    // return an int[] result of the same length as the text
    // such that the value result[i] is the index (0-based)
    // in text where the i-th lexicographically smallest
    // suffix of text starts.
    public int[] computeSuffixArray(String text) {
        int[] order = sortCharacters(text);
        int[] cls = computeCharClasses(text, order);

        for (int L = 1; L < text.length(); L *= 2) {
            order = sortDoubled(text, L, order, cls);
            cls = updateClasses(order, cls, L);
        }

        return order;
    }


    static public void main(String[] args) throws IOException {
        new SuffixArrayLong().run();
    }

    public void print(int[] x) {
        for (int a : x) {
            System.out.print(a + " ");
        }
        System.out.println();
    }

    public void run() throws IOException {
        FastScanner scanner = new FastScanner();
        String text = scanner.next();
        int[] suffix_array = computeSuffixArray(text);
        print(suffix_array);
    }
}

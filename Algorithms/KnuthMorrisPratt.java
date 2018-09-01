import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class KnuthMorrisPratt {
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

    // Find all the occurrences of the pattern in the text and return
    // a list of all positions in the text (starting from 0) where
    // the pattern starts in the text.
    public List<Integer> findPattern(String pattern, String text) {
        ArrayList<Integer> result = new ArrayList<Integer>();

        int patternLength = pattern.length();
        String kmpText = pattern + "$" + text;
        int kmpLength = kmpText.length();

        ArrayList<Integer> borders = new ArrayList<Integer>(Collections.nCopies(kmpLength, -1));
        borders.set(0, 0);

        for(int idx = 1; idx < kmpLength; idx++) {
            int border = borders.get(idx - 1);

            do {
                if (kmpText.charAt(idx) == kmpText.charAt(border)) {
                    borders.set(idx, border + 1);
                    if (border == patternLength - 1) {
                        result.add(idx - patternLength*2);
                    }
                } else if (border == 0) {
                    borders.set(idx, 0);
                } else {
                    border = borders.get(border - 1);
                }
            } while (borders.get(idx) == -1);

        }
        return result;
    }

    static public void main(String[] args) throws IOException {
        new KnuthMorrisPratt().run();
    }

    public void print(List<Integer> x) {
        for (int a : x) {
            System.out.print(a + " ");
        }
        System.out.println();
    }

    public void run() throws IOException {
        FastScanner scanner = new FastScanner();
        String pattern = scanner.next();
        String text = scanner.next();
        List<Integer> positions = findPattern(pattern, text);
        print(positions);
    }
}

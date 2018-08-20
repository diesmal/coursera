import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Trie {
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

    List<Map<Character, Integer>> buildTrie(String[] patterns) {
        List<Map<Character, Integer>> trie = new ArrayList<Map<Character, Integer>>();

        Integer lastNode = 1;

        for (String pattern : patterns) {
            Integer currentNode = 0;

            for (char character : pattern.toCharArray()) {
                Map<Character, Integer> node = getAtIndex(trie, currentNode);
                Map.Entry<Character, Integer> entry = getWithChar(node, character);
                if (entry != null) {
                    currentNode = entry.getValue();
                } else {
                    node.put(character, lastNode);
                    currentNode = lastNode;
                    lastNode++;
                }
            }
        }

        return trie;
    }

    static  public Map.Entry<Character, Integer> getWithChar(Map<Character, Integer> node, char c) {
        for(Map.Entry<Character, Integer> entry : node.entrySet()) {
            if (c == entry.getKey()) {
                return entry;
            }
        }
        return null;
    }

    static  public  Map<Character, Integer> getAtIndex(List<Map<Character, Integer>> trie, Integer index) {
        if (trie.size() <= index) {
            for (Integer idx = trie.size(); idx <= index; idx++) {
                trie.add(new HashMap<Character, Integer>());
            }
        }
        return trie.get(index);
    }

    static public void main(String[] args) throws IOException {
        new Trie().run();
    }

    public void print(List<Map<Character, Integer>> trie) {
        for (int i = 0; i < trie.size(); ++i) {
            Map<Character, Integer> node = trie.get(i);
            for (Map.Entry<Character, Integer> entry : node.entrySet()) {
                System.out.println(i + "->" + entry.getValue() + ":" + entry.getKey());
            }
        }
    }

    public void run() throws IOException {
        FastScanner scanner = new FastScanner();
        int patternsCount = scanner.nextInt();
        String[] patterns = new String[patternsCount];
        for (int i = 0; i < patternsCount; ++i) {
            patterns[i] = scanner.next();
        }

        List<Map<Character, Integer>> trie = buildTrie(patterns);
        print(trie);
    }
}

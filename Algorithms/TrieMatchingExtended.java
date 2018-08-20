import java.io.*;
import java.util.*;

class Node
{
	public static final int Letters =  4;
	public static final int NA      = -1;
	public int next [];

	Node ()
	{
		next = new int [Letters];
		Arrays.fill (next, NA);
	}

	boolean isLeaf() {
		return next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA;
	}
}

class PrefixTree {
	private List<Node> tree;

	PrefixTree(List <String> patterns) {
		tree = buildTrie(patterns);
		//print();
	}

	private List<Node> buildTrie(List <String> patterns) {

		List<Node> newTree = new ArrayList<Node>();

        patterns.sort(Comparator.comparingInt(String::length));

		int lastNode = 1;

		for (String pattern : patterns) {
			Node node = getAtIndex(newTree, 0);

			for (char character : pattern.toCharArray()) {
				Node entry = getNextNode(newTree, node, character);
				if (entry != null) {
					node = entry;
					if (node.isLeaf()) {
					    break;
                    }
				} else {
					int nextIndex = letterToIndex(character);
					node.next[nextIndex] = lastNode;
					node = getAtIndex(newTree, lastNode);
					lastNode++;
				}
			}
		}

		return newTree;
	}

	private Node getNextNode(List<Node> t, Node n, char c) {
		int index = letterToIndex(c);
		int nextIndex = n.next[index];
		if (nextIndex != Node.NA) {
			return t.get(nextIndex);
		}
		return null;
	}

	private Node getAtIndex(List<Node> t, int index) {
		if (t.size() <= index) {
			for (int idx = t.size(); idx <= index; idx++) {
				t.add(new Node());
			}
		}
		return t.get(index);
	}

	private int letterToIndex (char letter) {
		switch (letter) {
			case 'A': return 0;
			case 'C': return 1;
			case 'G': return 2;
			case 'T': return 3;
			default: assert (false); return Node.NA;
		}
	}

	public Node getAtIndex(int index) {
		return getAtIndex(tree, index);
	}

	public Node getNextNode(Node currentNode, char letter) {
		int nextIdx = letterToIndex(letter);
		if (currentNode.next[nextIdx] != Node.NA) {
			return getAtIndex(currentNode.next[nextIdx]);
		}
		return null;
	}

	public void print() {
		for (Node n : tree) {
			int index = tree.indexOf(n);

			String out = new  String(index + "->");
			if (n.next[0] != Node.NA) out += " ( A, " + n.next[0] + " )";
			if (n.next[1] != Node.NA) out += " ( C, " + n.next[1] + " )";
			if (n.next[2] != Node.NA) out += " ( G, " + n.next[2] + " )";
			if (n.next[3] != Node.NA) out += " ( T, " + n.next[3] + " )";

			System.out.println(out);
		}
	}
}

public class TrieMatchingExtended implements Runnable {
	List <Integer> solve (String text, int n, List <String> patterns) {
		List <Integer> result = new ArrayList <Integer> ();

		PrefixTree pfxTree = new PrefixTree(patterns);


		for (int idx = 0; idx < text.length(); idx++) {
			Node currentNode = pfxTree.getAtIndex(0); //Root
			int currentIdx = idx;

			while (currentNode != null) {
				if (currentNode.isLeaf()) {
					result.add(idx);
					currentNode = null;
				} else if (currentIdx < text.length()){
					char letter = text.charAt(currentIdx);
					currentNode = pfxTree.getNextNode(currentNode, letter);
					currentIdx++;
				} else {
					currentNode = null;
				}
			}
		}

		return result;
	}

	public void run () {
		try {
			BufferedReader in = new BufferedReader (new InputStreamReader (System.in));
			String text = in.readLine ();
		 	int n = Integer.parseInt (in.readLine ());
		 	List <String> patterns = new ArrayList <String> ();
			for (int i = 0; i < n; i++) {
				patterns.add (in.readLine ());
			}

			List <Integer> ans = solve (text, n, patterns);

			for (int j = 0; j < ans.size (); j++) {
				System.out.print ("" + ans.get (j));
				System.out.print (j + 1 < ans.size () ? " " : "\n");
			}
		}
		catch (Throwable e) {
			e.printStackTrace ();
			System.exit (1);
		}
	}

	public static void main (String [] args) {
		new Thread (new TrieMatchingExtended ()).start ();
	}
}

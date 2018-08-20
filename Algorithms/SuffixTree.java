import java.util.*;
import java.io.*;
import java.util.zip.CheckedInputStream;


class Node {
    public final static int NA = -1;
    public final static int Letters = 5;
	public int position;
    public int length;

    public int childrens[];

    Node(int _position, int _length) {
	    position = _position;
	    length = _length;
	    childrens = new int[Letters];
	    Arrays.fill(childrens, NA);
    }

    private int indexFromLetter(char letter) {
    	switch (letter) {
		    case 'A': return 0;
		    case 'T': return 1;
		    case 'G': return 2;
		    case 'C': return 3;
		    case '$': return 4;
	    }
	    return NA;
    }

    public int getChildIndex(char link) {
    	int nextIdx = NA;
	    int linkIdx = indexFromLetter(link);
    	if (linkIdx != NA) {
    		nextIdx = childrens[linkIdx];
	    } else {
    		System.out.println("Letter is not in scope (" + link + ").");
	    }
	    return nextIdx;
    }

    public void setChild(int childIdx, char link) {
	    int linkIdx = indexFromLetter(link);
	    if (childrens[linkIdx] == NA) {
		    childrens[linkIdx] = childIdx;
	    } else {
		    System.out.println("Try to rewrite the child (" + childrens[linkIdx] + ").");
	    }
    }

    public void clearChildrens() {
	    Arrays.fill(childrens, NA);
    }
}

class Tree {
	private ArrayList<Node> nodes = new ArrayList<Node>();
	private String text;
	private int textLength;

	Tree(String _text) {
		text = _text;
		textLength = text.length();
		buildTree();
	}

	Node root() {
		Node rootNode = null;

		if (nodes.size() > 0) {
			rootNode = nodes.get(0);
		} else {
			rootNode = new Node(Node.NA, Node.NA);
			nodes.add(rootNode);
		}

		return rootNode;
	}

	private Node next(Node currentNode, char link) {
		Node nextNode = null;
		int nextIdx = currentNode.getChildIndex(link);
		if (nextIdx != Node.NA) {
			if (nextIdx < nodes.size()) {
				nextNode = nodes.get(nextIdx);
			} else {
				System.out.println("Node have nonexistent child index.");
			}
		}
		return nextNode;
	}

	private Node addNodeAfter(Node parent, int position, int length) {
		char link = text.charAt(position);
		Node newNode = new Node(position, length);
		if (nodes.add(newNode)) {
			int newNodeIdx = nodes.indexOf(newNode);
			parent.setChild(newNodeIdx, link);
		} else {
			System.out.println("Failed trying add node to nodes array.");
		}
		return newNode;
	}

	private void splitNode(Node node, int splitPosition) {

		if (splitPosition < node.length) {
			int newNodePosition = node.position + splitPosition;
			int newNodeLength = node.length - splitPosition;

			int childrens[] = Arrays.copyOf(node.childrens, Node.Letters);
			node.clearChildrens();
			Node newNode = addNodeAfter(node, newNodePosition, newNodeLength);
			newNode.childrens = childrens;
			node.length = splitPosition;
		} else {
			System.out.println("Try to split (" + splitPosition + ")" + " but length is (" + node.length + ").");
		}
	}

	private void addSubstring(int startIdx) {
		Node currentNode = root();

		boolean substringAdded = false;
		int textIdx = startIdx;
		int nodeOffset = 0;

		while (substringAdded == false) {
			char letter = text.charAt(textIdx);

			if (currentNode.length <= nodeOffset) {
				Node nextNode = next(currentNode, letter);
				if (nextNode != null) {
					nodeOffset = 1;
					currentNode = nextNode;
				} else {
					int length = text.length() - textIdx;
					addNodeAfter(currentNode, textIdx, length);
					substringAdded = true;
				}
			} else {
				int position = currentNode.position + nodeOffset;
				char nodeLetter = text.charAt(position);
				if (nodeLetter == letter) {
					nodeOffset++;
				} else {
					splitNode(currentNode, nodeOffset);
					int length = text.length() - textIdx;
					addNodeAfter(currentNode, textIdx, length);
					substringAdded = true;
				}
			}
			textIdx++;
			if (textIdx >= textLength) {
				substringAdded = true;
			}
		}
	}

	private void buildTree() {
		for (int textIdx = 0; textIdx < textLength; textIdx++) {
			addSubstring(textIdx);

		}
	}

	public List<String> getValues() {
		List<String> result = new ArrayList<String>();
		for (Node node : nodes) {
			int beginIndex = node.position;
			int endIndex = node.position + node.length;
			if (beginIndex < endIndex) {
				String nodeContent = text.substring(beginIndex, endIndex);
				result.add(nodeContent);
			}
		}
		return result;
	}

}

public class SuffixTree {
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


    // Build a suffix tree of the string text and return a list
    // with all of the labels of its edges (the corresponding 
    // substrings of the text) in any order.
    public List<String> computeSuffixTreeEdges(String text) {
        Tree tree = new Tree(text);
        return tree.getValues();
    }


    static public void main(String[] args) throws IOException {
        new SuffixTree().run();
    }

    public void print(List<String> x) {
        for (String a : x) {
            System.out.println(a);
        }
    }

    public void run() throws IOException {
        FastScanner scanner = new FastScanner();
        String text = scanner.next();
        List<String> edges = computeSuffixTreeEdges(text);
        print(edges);
    }
}

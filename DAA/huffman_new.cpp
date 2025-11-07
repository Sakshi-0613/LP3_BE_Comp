//-------------------------------------------------------------
// Huffman Encoding using Greedy Strategy
//-------------------------------------------------------------

#include <iostream>
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

// Create new node
Node* createNode(char ch, int freq) {
    Node* newNode = new Node();
    newNode->ch = ch;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Build Huffman Tree using simple greedy selection
Node* buildHuffmanTree(char chars[], int freq[], int n) {
    // Array of node pointers
    Node* nodes[50];  

    for(int i = 0; i < n; i++)
        nodes[i] = createNode(chars[i], freq[i]);

    // Repeat until only one node remains (root)
    while(n > 1) {
        // Find two smallest frequency nodes
        int min1 = 0, min2 = 1;

        if(nodes[min2]->freq < nodes[min1]->freq)
            swap(min1, min2);

        for(int i = 2; i < n; i++) {
            if(nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            }
            else if(nodes[i]->freq < nodes[min2]->freq)
                min2 = i;
        }

        // Create new combined node
        Node* newNode = createNode('$', nodes[min1]->freq + nodes[min2]->freq);
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        // Replace nodes[min1] with new node, remove nodes[min2]
        nodes[min1] = newNode;
        nodes[min2] = nodes[n-1];
        n--; 
    }

    return nodes[0]; // Root of Huffman tree
}

// Print Huffman Codes using recursion
void printCodes(Node* root, string code) {
    if(root == NULL)
        return;

    // Leaf node -> print character and its code
    if(root->left == NULL && root->right == NULL) {
        cout << root->ch << " : " << code << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    char chars[n];
    int freq[n];

    cout << "Enter characters:\n";
    for(int i = 0; i < n; i++)
        cin >> chars[i];

    cout << "Enter frequencies:\n";
    for(int i = 0; i < n; i++)
        cin >> freq[i];

    Node* root = buildHuffmanTree(chars, freq, n);

    cout << "\nHuffman Codes:\n";
    printCodes(root, "");

    return 0;
}

/*

Enter number of characters: 4
Enter characters:
A B C D
Enter frequencies:
5 9 12 13

output:
A : 110
B : 111
C : 10
D : 0

*/
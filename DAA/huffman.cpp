//-------------------------------------------------------------
// Huffman Encoding (Simplified Version)
//-------------------------------------------------------------

#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;

// Structure for a node in the Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

// Function to create a new node
Node* createNode(char ch, int freq) {
    Node* node = new Node;
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Compare two nodes (used in min-heap)
struct compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to generate Huffman codes
void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
        codes[root->ch] = code;
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Function to encode text
string encodeText(string text, map<char, string>& codes) {
    string encoded = "";
    for (int i = 0; i < text.size(); i++)
        encoded += codes[text[i]];
    return encoded;
}

// Function to decode text
string decodeText(string encoded, Node* root) {
    string decoded = "";
    Node* curr = root;
    for (int i = 0; i < encoded.size(); i++) {
        if (encoded[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == NULL && curr->right == NULL) {
            decoded += curr->ch;
            curr = root;
        }
    }
    return decoded;
}

int main() {
    string text;
    cout << "Enter text to encode: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Text cannot be empty!";
        return 0;
    }

    // Step 1: Count frequency of characters
    map<char, int> freq;
    for (int i = 0; i < text.size(); i++)
        freq[text[i]]++;

    // Step 2: Create a priority queue (min-heap)
    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto it = freq.begin(); it != freq.end(); it++)
        pq.push(createNode(it->first, it->second));

    // Step 3: Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* newNode = createNode('#', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    Node* root = pq.top();

    // Step 4: Generate Huffman Codes
    map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "\nGenerated Huffman Codes:\n";
    for (auto it = codes.begin(); it != codes.end(); it++)
        cout << it->first << ": " << it->second << endl;

    // Step 5: Encode and Decode
    string encoded = encodeText(text, codes);
    cout << "\nEncoded Bit String: " << encoded;

    string decoded = decodeText(encoded, root);
    cout << "\nDecoded Text: " << decoded << endl;

    return 0;
}

/*


# **📌 Goal of the Program**

We are implementing **Huffman Encoding**, which is a **lossless compression technique**.

* Characters that appear **more frequently** get **shorter binary codes**
* Characters that appear **less frequently** get **longer binary codes**

This reduces the overall size of encoded text.

---

# ✅ **Line-by-Line Explanation**

```cpp
#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;
```

* `iostream` → For input/output.
* `queue` → To use **priority_queue** (min-heap).
* `map` → To store character frequencies and final codes.
* `string` → To handle text and encoded bit strings.

---

### **Structure of a Huffman Tree Node**

```cpp
struct Node {
    char ch;
    int freq;
    Node *left, *right;
};
```

* Each node stores:

  * `ch` → character
  * `freq` → how many times that character appears
  * `left`, `right` → pointers to child nodes
* Internal nodes (not leaf) will store `'#'` or no meaningful character.

---

### **Function to Create a New Node**

```cpp
Node* createNode(char ch, int freq) {
    Node* node = new Node;
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}
```

* Allocates memory for node.
* Sets character, frequency.
* Sets children to NULL (leaf initially).

---

### **Comparator For Priority Queue**

```cpp
struct compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};
```

* Makes the priority queue **sort nodes in increasing order of frequency** → smallest freq = highest priority.

---

### **Generate Huffman Codes (Recursive Tree Traversal)**

```cpp
void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (root == NULL)
        return;

    // If leaf node → store the generated binary code
    if (root->left == NULL && root->right == NULL)
        codes[root->ch] = code;

    // Traverse left → add '0'
    generateCodes(root->left, code + "0", codes);

    // Traverse right → add '1'
    generateCodes(root->right, code + "1", codes);
}
```

* Traverse tree:

  * Left = `0`
  * Right = `1`
* When a leaf is reached, the code formed so far becomes the character's Huffman code.

---

### **Encode Text**

```cpp
string encodeText(string text, map<char, string>& codes) {
    string encoded = "";
    for (int i = 0; i < text.size(); i++)
        encoded += codes[text[i]];
    return encoded;
}
```

* Replace each character in text with its Huffman code.

---

### **Decode Encoded Text**

```cpp
string decodeText(string encoded, Node* root) {
    string decoded = "";
    Node* curr = root;
    for (int i = 0; i < encoded.size(); i++) {
        if (encoded[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == NULL && curr->right == NULL) {
            decoded += curr->ch;  // Found a character
            curr = root;          // Go back to start of tree
        }
    }
    return decoded;
}
```

* Follow bits down the tree.
* When leaf reached → append character.

---

# **Main Function Logic**

```cpp
string text;
cout << "Enter text to encode: ";
getline(cin, text);
```

* Input the text to compress.

---

### **Step 1: Count Frequency**

```cpp
map<char, int> freq;
for (int i = 0; i < text.size(); i++)
    freq[text[i]]++;
```

* Count how many times each character appears.

---

### **Step 2: Insert Nodes into Min-Heap**

```cpp
priority_queue<Node*, vector<Node*>, compare> pq;
for (auto it = freq.begin(); it != freq.end(); it++)
    pq.push(createNode(it->first, it->second));
```

* Each character becomes a node in the priority queue (sorted by frequency).

---

### **Step 3: Build Huffman Tree**

```cpp
while (pq.size() > 1) {
    Node* left = pq.top(); pq.pop();
    Node* right = pq.top(); pq.pop();
    Node* newNode = createNode('#', left->freq + right->freq);
    newNode->left = left;
    newNode->right = right;
    pq.push(newNode);
}
Node* root = pq.top();
```

* Remove two lowest-frequency nodes.
* Create a new internal node with their **combined frequency**.
* Attach them as left and right children.
* Push back into heap.
* Repeat until only one node remains → this becomes the **Huffman Tree root**.

---

### **Step 4: Generate Codes**

```cpp
map<char, string> codes;
generateCodes(root, "", codes);
```

* Traverse tree to assign binary codes.

---

### **Step 5: Encode and Decode**

```cpp
string encoded = encodeText(text, codes);
string decoded = decodeText(encoded, root);
```

---

# **📌 Output Explanation**

* Prints frequency-based Huffman Codes
* Encoded binary
* Decoded original text

---

# **How to Explain in Viva (just say this)**

> Huffman Encoding assigns shorter binary codes to frequently occurring characters and longer codes to rare characters.
> We first count character frequencies, then create a min-heap to build a Huffman Tree.
> Traversing left adds 0, right adds 1, generating each character’s code.
> Encoding replaces characters with binary codes and decoding follows the tree back to characters.

*/

#include <iostream>
#include <string>
#include <vector>

#define SIZE 10
#define ALPHABET_SIZE 26

using namespace std;

vector <string> Hints(SIZE);
int Count = 0;


struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    bool isEmpty(TrieNode* root);
    bool isLastNode(struct TrieNode* root);
    void insert(struct TrieNode* root, string key);
    void PrintSearch(TrieNode* root, string key);
    void printAllWords(TrieNode* node, string& wordArray, int n);
};

TrieNode* getNewNode(void) {
    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

bool TrieNode::isEmpty(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

bool TrieNode::isLastNode(struct TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

void TrieNode::insert(struct TrieNode* root, string key) {
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!node->children[index]) {
            node->children[index] = getNewNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}


void TrieNode::printAllWords(TrieNode* node, string& wordArray, int n) {
    if (node->isEndOfWord) {
        cout << Count << ". " << wordArray << endl;
        Hints[Count] = wordArray;
        Count++;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            wordArray.push_back(i + 'a');
            printAllWords(node->children[i], wordArray, n);
        }
    }
    wordArray.pop_back();
}

void TrieNode::PrintSearch(TrieNode* root, string key) {
    
    struct TrieNode* pNode = root;
    string wordArray(key.length(), 0);
    wordArray.clear();

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (isEmpty(root)) {
            cout << "Error. No words in the Base." << endl;
            return;
        }
        else if (!root->children[index]) {
            cout << "No similar words have been found" << endl;
            return;
        }
        else {
            root = root->children[index];
            wordArray.push_back(index + 'a');
        }
    }
    int n = (wordArray.length());
    printAllWords(root, wordArray, n);
}


int main() {

    TrieNode* root = getNewNode();

    string keys[] = { "the", "and", "have", "with", "you", "but", "from", "they", "say", "one", 
        "would", "what", "about", "which", "make", "can", "like", "time", "just", "know", "take", 
        "people", "year", "good", "some", "see", "other", "now", "look", "only", "come", "think", 
        "also", "back", "after", "work", "first", "two", "because", "use", "work", "want", "give", "most"};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root->insert(root, keys[i]);
    }


    root->insert(root, "and");
    root->insert(root, "ant");
    root->insert(root, "bake");

    string Words;    
    string Message;
    char letter = 's';


    cout << "\t \tHello, User!\n" << endl;
    cout << "List of comands: 1 - Show similar words in Vocabulary, 0 - Exet" << endl;
    cout << "\tFor space type '!'" << endl;
    cout << "\nPlease, enter your message letter by letter: \n" << endl;

    while (letter != '0') {
        cin >> letter;
        if (letter >= char(97) && letter <= char(122)) {
            Words += letter;
            cout << "You're typing a word: " << Words << endl;
        }
        else if (letter == char(49)) {
            if (Words.empty()) {
                cout << "Enter your message first!" << endl;
            }
            else {
                root->PrintSearch(root, Words);
                cout << "\nDo you want choose any of these words?" << endl;
                cout << "1 - Yes, 2 - No" << endl;
                int choice;
                cin >> choice;
                if (choice == 1) {
                    cout << "Choose the word: ";
                    int choice2;
                    cin >> choice2;
                    if (choice2 < 0 || choice2 > Count) {
                        cout << "Someting is wrong" << endl;
                    }
                    else {
                        Message += Hints.at(choice2);
                        Message.push_back(' ');
                        Hints.clear();
                        Count = 0;
                        Words.erase(Words.begin(), Words.end());
                        cout << "\nYour current message: " << Message << "\n" << endl;
                    }
                }
                else if (choice == 2) {
                    cout << "You can continue writting еру word manually" << endl;
                }
            }
        }
        else if (letter > char(33) && letter < char(97)) {
            cout << "Please use only lowercase letters and no special characters" << endl;
        }
        else if (letter == char(33)) {
            Message += Words;
            Message.push_back(' ');
            cout << "\nYour current message: " << Message << "\n" << endl;
            Words.erase(Words.begin(), Words.end());
        }
        else {
            cout << "Something is wrong!" << endl;
        }
    }

    return 0;
}
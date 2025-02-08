#include "huffman.h"


using namespace std;

// Функция для создания нового узла дерева
Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

Node* buildHuffmanTree(const string& text, unordered_map<char, string>& huffmanCode) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto pair : freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }


    Node* root = pq.top();
    encode(root, "", huffmanCode);
    return root;

}

void writeEncodedMessageToFile(const string& encodedString, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    size_t bitLength = encodedString.size();
    outFile.write(reinterpret_cast<const char*>(&bitLength), sizeof(size_t));

    for (size_t i = 0; i < encodedString.length(); i += 8) {
        string byteStr = encodedString.substr(i, 8);
        if (byteStr.length() < 8) {
            byteStr.append(8 - byteStr.length(), '0');
        }

        unsigned char byte = 0;
        for (int j = 0; j < 8; ++j) {
            if (byteStr[j] == '1') {
                byte |= (1 << (7 - j));
            }
        }

        outFile.put(byte);
    }

    outFile.close();
}

string readEncodedMessageFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Не удалось открыть файл для чтения: " << filename << endl;
        return "";
    }

    size_t bitLength = 0;
    inFile.read(reinterpret_cast<char*>(&bitLength), sizeof(size_t));

    string encodedBits = "";
    char byte;

    while (inFile.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            encodedBits += ((byte & (1 << i)) ? '1' : '0');
        }
    }

    inFile.close();

    if (bitLength < encodedBits.size()) {
        encodedBits = encodedBits.substr(0, bitLength);
    }

    return encodedBits;
}

void decode(Node* root, int& index, const string& str, string& decodedString) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        decodedString += root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str, decodedString);
    else
        decode(root->right, index, str, decodedString);
}

void decodeMessageFromFile(const string& inputFilename, const string& outputFilename, Node* root) {
    string encodedMessage = readEncodedMessageFromFile(inputFilename);
    if (encodedMessage.empty()) {
        cerr << "Закодированное сообщение пустое или файл не найден." << endl;
        return;
    }

    string decodedMessage = "";
    int index = -1;

    while (index < (int)encodedMessage.size() - 1) {
        decode(root, index, encodedMessage, decodedMessage);
    }

    ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << outputFilename << endl;
        return;
    }

    outFile << decodedMessage;
    outFile.close();
}

string loadTextFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return content;
}

void CompressionRatio(const string& inputFile, const string& encodedFile) {

    ifstream input(inputFile, ios::binary | ios::ate);

    size_t inputFileSize = input.tellg(); 
    input.close();


    ifstream encoded(encodedFile, ios::binary | ios::ate);

    size_t encodedFileSize = encoded.tellg(); 
    encoded.close();

    double ratio = (1.0 - static_cast<double>(encodedFileSize) / inputFileSize) * 100;

    cout << "\nFile Compression Statistics:\n";
    cout << "Input file size: " << inputFileSize << " bytes\n";
    cout << "Encoded file size: " << encodedFileSize << " bytes\n";
    cout << "Compression ratio: " << ratio << "%\n";
}

void TextCompressionRatio(const string& originalText, const unordered_map<char, string>& huffmanCode) {
    size_t originalBits = originalText.size() * 8;

    size_t encodedBits = 0;
    for (const char& ch : originalText) {
        encodedBits += huffmanCode.at(ch).size();
    }

    double averageCodeLength = static_cast<double>(encodedBits) / originalText.size();

    double ratio = (1.0 - static_cast<double>(encodedBits) / originalBits) * 100;

    cout << "\nText Compression Statistics:\n";
    cout << "Original text size: " << originalBits << " bits\n";
    cout << "Encoded text size: " << encodedBits << " bits\n";
    cout << "Compression ratio: " << ratio << "%\n";
    cout << "Average code length: " << averageCodeLength << " bits/symbol\n";
}
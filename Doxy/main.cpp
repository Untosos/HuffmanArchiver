#include "huffman.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    string inputText = loadTextFromFile("input.txt");
    if (inputText.empty()) {
        cerr << "Ошибка: входной файл пуст или не найден!" << endl;
        return 1;
    }

    unordered_map<char, string> huffmanCode;
    Node* root = buildHuffmanTree(inputText, huffmanCode);

    string encodedString = "";
    for (char ch : inputText) {
        encodedString += huffmanCode[ch];
    }

    writeEncodedMessageToFile(encodedString, "encoded.bin");

    cout << "Huffman Codes (Character -> Code):\n";
    for (const auto& pair : huffmanCode) {
        if (pair.first == ' ') {
            cout << "' ' -> " << pair.second << '\n'; // Для пробела явно указываем
        }
        else {
            cout << "'" << pair.first << "' -> " << pair.second << '\n';
        }
    }
    cout << '\n';

    decodeMessageFromFile("encoded.bin", "decoded.txt", root);

    cout << "Процесс завершён. Проверьте файлы encoded.bin и decoded.txt." << endl;

    CompressionRatio("input.txt", "encoded.bin");
    TextCompressionRatio(inputText, huffmanCode);

    return 0;
}

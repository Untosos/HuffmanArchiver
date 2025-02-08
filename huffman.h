#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <queue>

// Узел дерева Хаффмана
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

// Функция для загрузки текста из файла
std::string loadTextFromFile(const std::string& filename);

// Построение дерева Хаффмана и получение кодов
Node* buildHuffmanTree(const std::string& text, std::unordered_map<char, std::string>& huffmanCode);

// Запись закодированного сообщения в бинарный файл
void writeEncodedMessageToFile(const std::string& encodedString, const std::string& filename);

// Чтение закодированного сообщения из бинарного файла
std::string readEncodedMessageFromFile(const std::string& filename);

// Декодирование сообщения из файла
void decodeMessageFromFile(const std::string& inputFilename, const std::string& outputFilename, Node* root);

void CompressionRatio(const std::string& inputFile, const std::string& encodedFile);

void TextCompressionRatio(const std::string& originalText, const std::unordered_map<char, std::string>& huffmanCode);


#endif

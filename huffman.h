#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <queue>

// ���� ������ ��������
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

// ������� ��� �������� ������ �� �����
std::string loadTextFromFile(const std::string& filename);

// ���������� ������ �������� � ��������� �����
Node* buildHuffmanTree(const std::string& text, std::unordered_map<char, std::string>& huffmanCode);

// ������ ��������������� ��������� � �������� ����
void writeEncodedMessageToFile(const std::string& encodedString, const std::string& filename);

// ������ ��������������� ��������� �� ��������� �����
std::string readEncodedMessageFromFile(const std::string& filename);

// ������������� ��������� �� �����
void decodeMessageFromFile(const std::string& inputFilename, const std::string& outputFilename, Node* root);

void CompressionRatio(const std::string& inputFile, const std::string& encodedFile);

void TextCompressionRatio(const std::string& originalText, const std::unordered_map<char, std::string>& huffmanCode);


#endif

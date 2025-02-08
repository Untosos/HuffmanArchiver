/**
 * @file huffman.h
 * @brief Header file for the Huffman encoding algorithm.
 *
 * Contains data structures and functions for text compression using the Huffman algorithm,
 * including tree construction, encoding and decoding messages, and calculating compression ratios.
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <queue>

 /**
  * @struct Node
  * @brief Node of the Huffman tree.
  *
  * Represents a character, its frequency in the text, and pointers to child nodes.
  */
struct Node {
    char ch;         /**< Character */
    int freq;        /**< Frequency of the character */
    Node* left;      /**< Pointer to the left child */
    Node* right;     /**< Pointer to the right child */
};

/**
 * @brief Loads text from a specified file.
 *
 * @param filename Name of the input file.
 * @return Contents of the file as a string.
 */
std::string loadTextFromFile(const std::string& filename);

/**
 * @brief Builds the Huffman tree and generates character codes.
 *
 * @param text Input text to encode.
 * @param huffmanCode Reference to a map for storing character codes.
 * @return Pointer to the root of the Huffman tree.
 */
Node* buildHuffmanTree(const std::string& text, std::unordered_map<char, std::string>& huffmanCode);

/**
 * @brief Writes the encoded message to a binary file.
 *
 * @param encodedString The encoded string.
 * @param filename Name of the output file.
 */
void writeEncodedMessageToFile(const std::string& encodedString, const std::string& filename);

/**
 * @brief Reads an encoded message from a binary file.
 *
 * @param filename Name of the input file.
 * @return The encoded string read from the file.
 */
std::string readEncodedMessageFromFile(const std::string& filename);

/**
 * @brief Decodes a message from a binary file and writes the result to a text file.
 *
 * @param inputFilename Name of the file containing the encoded message.
 * @param outputFilename Name of the output file for the decoded text.
 * @param root Pointer to the root of the Huffman tree.
 */
void decodeMessageFromFile(const std::string& inputFilename, const std::string& outputFilename, Node* root);

/**
 * @brief Calculates the compression ratio based on the sizes of the input and encoded files.
 *
 * @param inputFile Name of the input file with the original text.
 * @param encodedFile Name of the file with the encoded text.
 */
void CompressionRatio(const std::string& inputFile, const std::string& encodedFile);

/**
 * @brief Calculates the compression ratio based on the original text and Huffman code table.
 *
 * @param originalText The original text.
 * @param huffmanCode Map with character codes.
 */
void TextCompressionRatio(const std::string& originalText, const std::unordered_map<char, std::string>& huffmanCode);

#endif

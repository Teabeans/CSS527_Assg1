#pragma once

#include <iostream>
#include <string>
#include <fstream>

#define MAX_MSG_LENGTH 1024

class sbox {
  public:
  // Substitution boxes
  unsigned char S1[4][4]; // [row][col]
  unsigned char S2[4][4]; // [row][col]

  unsigned char K1[4];
  unsigned char K2[4];

  unsigned char plaintext[ MAX_MSG_LENGTH ];
  unsigned char ciphertext[ MAX_MSG_LENGTH ];

  sbox();
  ~sbox();

  // Scrubber
  void tareFields();

  // Loaders
  bool loadText( std::string filename );
  bool loadSbox( std::string filenameS1, std::string filenameS2 );
  bool loadKeys( std::string filename );

  // Render the text
  void renderText( );
  int convertBinaryToInt( std::string binaryString );
  char convertIntToChar( int input );
};
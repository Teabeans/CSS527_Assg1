#include "sbox.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {
  std::cerr << "Hello, World!" << std::endl;
  sbox theBox;
  theBox.renderText();

  // Test Sbox load
  theBox.loadSbox( "S1.txt", "S2.txt" );

  // Test key load
  theBox.loadKeys( "keys.txt" );

  // Test text load
  theBox.loadText( "plaintext.txt" );

  // Test S-box encryption using K1 (rather than K2)
  // Key 1, Row 0
  theBox.encrypt( "K1", 0 );

  theBox.renderCiphertext( 16 );

  return 1;
}
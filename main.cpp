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

  return 1;
}
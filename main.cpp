#include "sbox.h"
#include <iostream>
#include <string>
#include <fstream>

#define DEBUG true

int main() {
  if( DEBUG ) {
  	std::cerr << "Generating an sbox instance..." << std::endl << std::endl;
  }
  sbox theBox;
  theBox.renderPlaintext( 40 );

  // Test Sbox load
  theBox.loadSbox( "S1.txt", "S2.txt" );

  // Test key load
  theBox.loadKeys( "keys.txt" );

  // Test text load
  theBox.loadPlaintext( "plaintext.txt" );

  theBox.renderPlaintext( 40 );

  // Test S-box encryption using K1
  // Key 1, Row 0
  for( int i = 0 ; i < 10 ; i++ ) {
    theBox.encrypt( "K1", i );
  }

  std::cerr << "Rendering ciphertext from K1..." << std::endl;
  theBox.renderCiphertext( 40 );

  // Test S-box encryption using K2)
  // Key 1, Row 0
  for( int i = 0 ; i < 10 ; i++ ) {
    theBox.encrypt( "K2", i );
  }

  std::cerr << "Rendering ciphertext from K2..." << std::endl;
  theBox.renderCiphertext( 40 );

  // Reset encryption to K1
  for( int i = 0 ; i < 10 ; i++ ) {
    theBox.encrypt( "K1", i );
  }

  std::cerr << "Generating a comparison box..." << std::endl << std::endl;

  sbox compareBox;
  compareBox.loadSbox( "S1.txt", "S2.txt" );
  compareBox.loadKeys( "keys.txt" );
  compareBox.loadPlaintext( "plaintext_1bit.txt" );
  for( int i = 0 ; i < 10 ; i++ ) {
    compareBox.encrypt( "K1", i );
  }
  compareBox.renderCiphertext( 40 );

  std::cerr << "Converting ComparisonBox messages 0 to 9 to binary string..." << std::endl;
  std::cerr << compareBox.cipherToString( 0, 9) << std::endl << std::endl;

  std::cerr << "Rendering DefaultBox messages 0 to 9 binary string to blocks..." << std::endl;
  compareBox.renderBinaryString( theBox.cipherToString(0, 9) );
  std::cerr << std::endl;

  std::cerr << "Rendering ComparisonBox messages 0 to 9 binary string to blocks..." << std::endl;
  compareBox.renderBinaryString( compareBox.cipherToString(0, 9) );
  std::cerr << std::endl;

  std::cerr << "Testing string comparison with 'abcdeg' vs 'abceeg'..." << std::endl;
  std::cerr << theBox.avalancheCompare( "abcdeg", "abceeg" ) << std::endl << std::endl;

  std::cerr << "Comparing original ciphertext binary string to ComparisonBox binary string..." << std::endl;
  std::cerr << theBox.avalancheCompare( theBox.cipherToString( 0, 9), compareBox.cipherToString( 0, 9) ) << "\% different." << std::endl;

  return 1;
}
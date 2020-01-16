//-------|---------|---------|---------|---------|---------|---------|---------|
//
// UW CSS 527 - Assg1 - Substitution Boxes
// sbox.cpp
//
//-------|---------|---------|---------|---------|---------|---------|---------|

//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2020.01.15
// Modified: 2020.--.-- (TODO)
// For the University of Washington Bothell, CSS 527
// Winter 2020, Masters in Cybersecurity Engineering (MCSE)
//

//-----------------------------------------------------------------------------|
// File Description
//-----------------------------------------------------------------------------|
//
// TODO

//-----------------------------------------------------------------------------|
// Package Files
//-----------------------------------------------------------------------------|
//
// TODO

//-----------------------------------------------------------------------------|
// Useage
//-----------------------------------------------------------------------------|
//
// Compile with:
// $ ./compile.sh
//


//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       DEFINES
//
//-------|---------|---------|---------|---------|---------|---------|---------|

#define DEBUG true
#define MAX_MSG_LENGTH 1024

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       INCLUDES
//
//-------|---------|---------|---------|---------|---------|---------|---------|

#include "sbox.h"

#include <iostream>
#include <string>
#include <fstream>

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PUBLIC FIELDS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       CONSTRUCTOR / DESTRUCTOR
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
sbox::sbox( ) {
  this->tareFields();
}

// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
sbox::~sbox( ) {
  this->tareFields();
}

void sbox::tareFields( ) {
  for( int row = 0 ; row < 4 ; row++ ) {
    this->K1[row] = (unsigned char)0;
    this->K2[row] = (unsigned char)0;
    for( int col = 0 ; col < 4 ; col++ ) {
      this->S1[row][col] = (unsigned char)0;
      this->S2[row][col] = (unsigned char)0;
    }
  }
  for( int i = 0 ; i < MAX_MSG_LENGTH ; i++ ) {
  	this->plaintext[ i ]  = '\0';
  	this->ciphertext[ i ] = '\0';

  }

}
//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PUBLIC METHOD IMPLEMENTATIONS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
bool sbox::loadText( std::string filename ) {
  std::ifstream plaintext;
  plaintext.open( filename );
  std::string quartet1;
  std::string quartet2;
  std::string octet;
  int currByte = 0;

  while( !plaintext.eof() ) {
    plaintext >> quartet1;
    plaintext >> quartet2;
    octet = quartet1 + quartet2;
    this->plaintext[ currByte ] = (unsigned char)std::stoi( octet, nullptr, 2 );
    currByte++;
  }
  this->plaintext[ currByte ] = '\0';

  if( DEBUG ) {
    std::cerr << "Plaintext loaded: " << std::endl;
    std::cerr << this->plaintext << std::endl;
    for( int i = 0 ; i < 20 ; i++ ) {
      std::cerr << (unsigned int)this->plaintext[ i ] << " ";
    }
    std::cerr << std::endl;
  }
  return true;
}


// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
bool sbox::loadSbox( std::string filenameS1, std::string filenameS2 ) {
  // Load S1
  std::ifstream S1txt;
  S1txt.open( filenameS1 );
  int substitution;
  for( int row = 0 ; row < 4 ; row++ ) {
    for( int col = 0 ; col < 4 ; col++ ) {
      S1txt >> substitution;
      this->S1[row][col] = (unsigned char)substitution;
    }
  }
  S1txt.close();

  // Load S2
  std::ifstream S2txt;
  S2txt.open( filenameS2 );
  for( int row = 0 ; row < 4 ; row++ ) {
    for( int col = 0 ; col < 4 ; col++ ) {
      S2txt >> substitution;
      this->S2[row][col] = (unsigned char)substitution;
    }
  }
  S2txt.close();

  // Check results:
  if( DEBUG ) {
    std::cerr << "Substitution Box S1:" << std::endl;
    for( int row = 0 ; row < 4 ; row++ ) {
      for( int col = 0 ; col < 4 ; col++ ) {
        std::cerr << (unsigned int)this->S1[row][col] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "Substitution Box S2:" << std::endl;
    for( int row = 0 ; row < 4 ; row++ ) {
      for( int col = 0 ; col < 4 ; col++ ) {
        std::cerr << (unsigned int)this->S2[row][col] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << std::endl;

  }

  return true;
}

// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
bool sbox::loadKeys( std::string filename ) {
  std::ifstream myfile;
  myfile.open( "keys.txt" );
  std::string keyline;

  // Load K1
  for( int i = 0 ; i < 4 ; i++ ) {
    myfile >> keyline;
    K1[i] = (unsigned char)std::stoi( keyline, nullptr, 2 );
  }
  // Load K2
  for( int i = 0 ; i < 4 ; i++ ) {
    myfile >> keyline;
    K2[i] = (unsigned char)std::stoi( keyline, nullptr, 2 );
  }

  if( DEBUG ) {
    std::cerr << "Key K1:" << std::endl;
    for( int i = 0 ; i < 4 ; i++ ) {
      std::cerr << (unsigned int)K1[i] << " ";
      if( i == 3 ) {
        std::cerr << std::endl << std::endl;
      }
    }

    std::cerr << "Key K2:" << std::endl;
    for( int i = 0 ; i < 4 ; i++ ) {
      std::cerr << (unsigned int)K2[i] << " ";
      if( i == 3 ) {
        std::cerr << std::endl << std::endl;
      }
    }

  }
  return true;
}

// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
void sbox::renderText( ) {
  std::cerr << "I am sbox-rendered text! Yay!" << std::endl;
}

// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
int sbox::convertBinaryToInt( std::string binaryString ) {
  unsigned int retval = std::stoi( binaryString, nullptr, 2);
  return retval;
}

// (+) --------------------------------|
// #TODO( )
// ------------------------------------|
// Desc:    TODO
// Params:  TODO
// PreCons: TODO
// PosCons: TODO
// RetVal:  TODO
char sbox::convertIntToChar( int input ) {
  char retchar = (char)input;
  return retchar;
}

// End of file sbox.cpp

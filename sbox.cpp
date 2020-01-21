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
#include <stdio.h>
#include <iomanip>

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

void sbox::renderCiphertext( int length ) {
  if( DEBUG ) {
    std::cerr << "--------|--------|-------- CIPHERTEXT --------|--------|--------" << std::endl;
  }
  for( int i = 0 ; i < length ; i++ ) {
  	std::cerr << std::setw(3) << (unsigned int)this->ciphertext[i];
  	if( i % 4 == 3 ) {
      std::cerr << std::endl;
  	}
  }
  if( DEBUG ) {
  	std::cerr << "--------|--------|-------- CIPHERTEXT --------|--------|--------" << std::endl;
  }
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
  for( int i = 0 ; i < 16 ; i++ ) {
  	this->S1Linear[i] = (unsigned char)0;
  	this->S2Linear[i] = (unsigned char)0;
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
      this->S1[row][col]            = (unsigned char)substitution;
      this->S1Linear[((row*4)+col)] = (unsigned char)substitution;
    }
  }
  S1txt.close();

  // Load S2
  std::ifstream S2txt;
  S2txt.open( filenameS2 );
  for( int row = 0 ; row < 4 ; row++ ) {
    for( int col = 0 ; col < 4 ; col++ ) {
      S2txt >> substitution;
      this->S2[row][col]            = (unsigned char)substitution;
      this->S2Linear[((row*4)+col)] = (unsigned char)substitution;
    }
  }
  S2txt.close();

  // Check results:
  if( DEBUG ) {
    std::cerr << "Substitution Box S1:" << std::endl;
    for( int row = 0 ; row < 4 ; row++ ) {
      for( int col = 0 ; col < 4 ; col++ ) {
        std::cerr << std::setw(3) << (unsigned int)this->S1[row][col] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "Substitution Box S2:" << std::endl;
    for( int row = 0 ; row < 4 ; row++ ) {
      for( int col = 0 ; col < 4 ; col++ ) {
        std::cerr << std::setw(3) << (unsigned int)this->S2[row][col] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "SBoxes (Linear):" << std::endl;
    for( int i = 0 ; i < 16 ; i++ ) {
      std::cerr << std::setw(3) << (unsigned int)this->S1Linear[i];
    }
    std::cerr << std::endl;
    for( int i = 0 ; i < 16 ; i++ ) {
      std::cerr << std::setw(3) << (unsigned int)this->S2Linear[i];
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
void sbox::encrypt( std::string keyDesignate, int row ) {
  // Transfer the keys into the method
  unsigned char key[4];
  if( keyDesignate == "K1" ) {
    for( int i = 0 ; i < 4 ; i++ ) {
      key[i] = this->K1[i];
    }
  }
  else if( keyDesignate == "K2" ) {
    for( int i = 0 ; i < 4 ; i++ ) {
      key[i] = this->K2[i];
    }
  }
  // Copy the row from the store to the method
  unsigned char plaintextRow[4];
  for( int i = 0 ; i < 4 ; i++ ) {
    plaintextRow[i] = this->plaintext[ (row*4) + i];
  }
  // Implement the cipher
  unsigned char cipherIndex1 = plaintextRow[1] ^ key[0];
  unsigned char cipherIndex2 = plaintextRow[3] ^ key[2];
  unsigned char cipherIndex3 = plaintextRow[4] ^ key[1];
  unsigned char cipherIndex4 = plaintextRow[2] ^ key[3];
  unsigned char cipherRow[4];
  cipherRow[0] = S1Linear[cipherIndex1];
  cipherRow[1] = S2Linear[cipherIndex2];
  cipherRow[2] = S1Linear[cipherIndex3];
  cipherRow[3] = S2Linear[cipherIndex4];
  if( DEBUG ) {
    std::cerr << "----- ENCRYPTION COMPLETE -----" << std::endl;
    for( int i = 0 ; i < 4 ; i++ ){
      std::cerr << std::setw(3) << (unsigned int)cipherRow[i];
    }
    std::cerr << std::endl;
  }
  for( int i = 0 ; i < 4 ; i++ ) {
    this->ciphertext[i + (row*4)] = cipherRow[i];
  }
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

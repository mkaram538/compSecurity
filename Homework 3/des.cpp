#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int permutationTable[64] =
  {58,50,42,34,26,18,10,2
  ,60,52,44,36,28,20,12,4
  ,62,54,46,38,30,22,14,6
  ,64,56,48,40,32,24,16,8
  ,57,49,41,33,25,17,9,1
  ,59,51,43,35,27,19,11,3
  ,61,53,45,37,29,21,13,5
  ,63,55,47,39,31,23,15,7};

int halfPermutationTable[32] =
{16,7,20,21,
  29,12,28,17,
  1,15,23,26,
  5,18,31,10,
  2,8,24,14,
  32,27,3,9,
  19,13,30,6,
  22,11,4,25};

int expansionTable[48] =
{32,1,2,3,4,5,
  4,5,6,7,8,9,
  8,9,10,11,12,13,
  12,13,14,15,16,17,
  16,17,18,19,20,21,
  20,21,22,23,24,25,
  24,25,26,27,28,29,
  28,29,30,31,32,1};

int sBoxTable[8][64] = {
{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},

{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},

{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},

{7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},

{2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},

{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},

{4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},

{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}};

int globalKey[48];

int numRounds = 1;

void expand(int halfBlock[], int expandedBlock[]) {
  int oldIndex;
  for (int i = 0; i < 48; i++) {
    oldIndex = expansionTable[i] - 1;
    expandedBlock[i] = halfBlock[oldIndex];
  }
}

void sBox(int expandedBlock[], int shrankBlock[]) {
  int row;
  int column;
  int newValue;

  int currentBlock;

  for (int i = 0; i < 8; i++) {
    currentBlock = 6 * i;
    row = 2 * expandedBlock[currentBlock] + expandedBlock[currentBlock + 5];
    column = 8 * expandedBlock[currentBlock + 1] + 4 * expandedBlock[currentBlock + 2] +
      2 * expandedBlock[currentBlock + 3] + expandedBlock[currentBlock + 4];
    newValue = sBoxTable[i][row * 16 + column];

    for (int p = 3; p >= 0; p--){
      shrankBlock[i * 4 + p] = newValue % 2;
      newValue /= 2;
    }
  }
}

void halfPermutation(int block[], int permutedBlock[]) {
  int oldIndex;
  for (int i = 0; i < 32; i++) {
    oldIndex = halfPermutationTable[i] - 1;
    permutedBlock[i] = block[oldIndex];
  }
}

void mangler(int halfBlock[], int mangledBlock[]) {
  int expandedBlock[48];
  expand(halfBlock, expandedBlock);

  for (int i = 0; i < 48; i++) {
    expandedBlock[i] ^= globalKey[i];
  }
  int shrankBlock[32];
  sBox(expandedBlock, shrankBlock);

  halfPermutation(shrankBlock, mangledBlock);
}

void feistal(int leftBlock[], int rightBlock[]) {
  int mangledRight[32];
  int tempBit;

  mangler(rightBlock, mangledRight);

  for (int i = 0; i < 32; i++) {
    mangledRight[i] ^= leftBlock[i];
    leftBlock[i] = rightBlock[i];
    rightBlock[i] = mangledRight[i];
  }
}

void permutation(int block[], int permutedBlock[]) {
  int oldIndex;

  for (int i = 0; i < 64; i++) {
    oldIndex = permutationTable[i] - 1;
    permutedBlock[i] = block[oldIndex];
  }
}

void swapHalves(int leftBlock[], int rightBlock[]) {
  int tempBit;

  for (int i = 0; i < 32; i++) {
    tempBit = leftBlock[i];
    leftBlock[i] = rightBlock[i];
    rightBlock[i] = tempBit;
  }
}

void splitHalves(int block[], int leftBlock[], int rightBlock[]) {
  for (int i = 0; i < 64; i++) {
    i / 32 == 0 ? leftBlock[i] = block[i] : rightBlock[i-32] = block[i];
  }
}

void combineHalves(int block[], int leftBlock[], int rightBlock[]) {
  for (int i = 0; i < 64; i++) {
    i / 32 == 0 ? block[i] = leftBlock[i] : block[i] = rightBlock[i-32];
  }
}

void roundHandler(int block[]) {
  int permutedBlock[64];
  int leftBlock[32];
  int rightBlock[32];

  permutation(block, permutedBlock);
  splitHalves(permutedBlock, leftBlock, rightBlock);
  for (int i = 0; i < numRounds; i++) {
    feistal(leftBlock, rightBlock);
  }
  swapHalves(leftBlock, rightBlock);
  combineHalves(permutedBlock, leftBlock, rightBlock);
  permutation(permutedBlock, block);
}

void printBlock(int block[], int index) {
  int currentChar;

  cout << "Final Block: " << endl;
  for (int i = 0; i < 8; i++) {
    for (int p = 0; p < 8; p++){
      cout << block[i*8 + p];
    }
    cout << endl;
  }

  cout << endl;
  
  cout << "Cipher Text: " << endl;

  for (int i = 0; i < 8; i++) {
    currentChar = 0;
    for (int p = 0; p < 8; p++){
      currentChar += block[i * 8 + p] * pow(2, (7 - p));
    }
    cout << currentChar << " ";
  }
}

void blockPrep(string blockString, int index) {
  int block[64];
  int remainder;

  for (int i = 0; i < 8; i++) {
    remainder = blockString[i];
    for (int p = 7; p >= 0; p--){
      block[i * 8 + p] = remainder % 2;
      remainder >>= 1;
    }
  }
  roundHandler(block);
  printBlock(block, index);
}

int main() {
  string plaintext = "This was";

  unsigned char byteKey[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc};
  int remainder;
  for (int i = 0; i < 6; i++) {
    remainder = (int) byteKey[i];
    for (int p = 7; p >= 0; p--){
      globalKey[i * 8 + p] = remainder % 2;
      remainder >>= 1;
    }
  }

  for (int i = 0; i < plaintext.length() / 8; i++) {
    blockPrep(plaintext.substr(i * 8, 8), i);
  }
  cout << endl;

  return 0;
}

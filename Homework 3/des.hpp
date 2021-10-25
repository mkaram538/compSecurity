#ifndef DES_H
#define DES_H

#include <string>

using namespace std;

class DES {

private:
  int numRounds;
  string plaintext;
  int bitKey[48];

public:
  DES(int numRounds, string plaintext);

  void expand(int halfBlock[], int expandedBlock[]);
  void sBox(int expandedBlock[], int shrankBlock[]);
  void halfPermutation(int block[], int permutedBlock[]);
  void mangler(int halfBlock[], int mangledBlock[]);
  void feistal(int leftBlock[], int rightBlock[]);
  void permutation(int block[], int permutedBlock[]);
  void swapHalves(int leftBlock[], int rightBlock[]);
  void splitHalves(int block[], int leftBlock[], int rightBlock[]);
  void combineHalves(int block[], int leftBlock[], int rightBlock[]);
  void roundHandler(int block[]);
  void printBlock(int block[]);
  void blockPrep(string blockString);
};

#endif

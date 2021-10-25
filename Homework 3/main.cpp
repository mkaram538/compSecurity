#include <iostream>
#include <string>
#include "des.hpp"
using namespace std;

int main() {
  string plaintext = "This was a top secret assignment";

  DES oneRoundDes = DES(1, plaintext);

  return 0;
}

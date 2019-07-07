#include "root.h"
#include <iostream>

Root::Root(std::string category, std::string type, char letter, int gReq, int buy, int sell):Crop(category, type, letter, gReq, buy, sell) {
}

void Root::fertilise() { //function for fertilising root: instantly ready for harvest
  growthP = growthReq;
  fertilised = true;
  updateLetter();
}

//inherited pure virtual functions not implemented in Root
void Root::harvestReset() {
}

int Root::getRemainingYields() {
  return 1;
}

int Root::getYieldNum() {
  return 1;
}

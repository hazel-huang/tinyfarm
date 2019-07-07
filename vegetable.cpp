#include "vegetable.h"

#include <string>
#include <iostream>

Vegetable::Vegetable(std::string category, std::string type, char letter, int gReq, int buy, int sell):Crop(category, type, letter, gReq, buy, sell) {
  remainingYields = 3;
}

//return functions
int Vegetable::getYieldNum() {
  return 1;
}

int Vegetable::getRemainingYields() {
  return remainingYields;
}


void Vegetable::fertilise() { //function for fertilising root crop
  growthP = growthReq;
  updateLetter();
  fertilised = true;
}

void Vegetable::harvestReset() { //function for what happens when veg is harvested
  if (remainingYields > 0) {
    growthP = 0;
    remainingYields--;
  }
  fertilised = false;
  updateLetter();
}

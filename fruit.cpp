#include "fruit.h"

Fruit::Fruit(std::string category, std::string type, char letter, int gReq, int buy, int sell):Crop(category, type, letter, gReq, buy, sell) {
  yieldNum = 3;
}

//return functions
int Fruit::getYieldNum() {
  return yieldNum;
}

int Fruit::getRemainingYields() {
  return 1;
}


void Fruit::fertilise() { //increases fruit yield for this harvest
  yieldNum+=2;
  fertilised = true;
}

void Fruit::harvestReset() { //function for what happens when fruit is harvested from tree
  growthP = 0;
  fertilised = false;
  if (cropType == "lemon") {
    growthReq = 2;
  } else if (cropType == "avocado") {
    growthReq = 3;
  }
  updateLetter();
}

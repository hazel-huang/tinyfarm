#include "crop.h"
#include <string>
#include <cctype>

Crop::Crop() { //default crop constructor
  cropType = "?";
}

Crop::Crop(std::string category, std::string type, char letter, int gReq, int buy, int sell) { //crop constructor with parameters
  cropCategory = category;
  cropType = type;
  fieldLetter = letter;
  growthReq = gReq;
  growthP = 0;
  fertilised = false;
  buyPrice = buy;
  sellPrice = sell;
}

std::string Crop::getCategory() {
  return cropCategory;
}


std::string Crop::getType() {
  return cropType;
}

void Crop::updateLetter() { //changes fieldLetter as needed (lowercase to upper when mature, X when rotten)
  if (growthP < growthReq) {
    fieldLetter = tolower(fieldLetter); //to lower case if not mature
  }
  if (growthP == growthReq) {
    fieldLetter = toupper(fieldLetter); //to upper case when mature
  }
  if (growthP == growthReq+2) { //to X when rotten
    fieldLetter = 'X';
  }
}

char Crop::getFieldLetter() {
  return fieldLetter;
}

int Crop::getGrowthReq() {
  return growthReq;
}

int Crop::getGrowthP() {
  return growthP;
}

void Crop::grow() { //function that increments growth p and updates fieldLetter
  growthP++;
  updateLetter();
}

int Crop::getBuyPrice() {
  return buyPrice;
}

int Crop::getSellPrice() {
  return sellPrice;
}

bool Crop::isFertilised() {
  return fertilised;
}

Crop::~Crop() {
}

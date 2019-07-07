#include "farm.h"
#include "crop.h"
#include "root.h"
#include "vegetable.h"
#include "fruit.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>

//required tinyfarm.cpp functions
extern void winGame();
extern void bankrupt();

Farm::Farm() {

  //initialising variables
  funds = 300;
  fertiliser = 0;

  //initialising dynamically allocated arrays & vector
  Crop **fieldptr = new Crop*[16];
  Crop **seedptr = new Crop*[16];
  std::vector<Crop*> harvested;

  for (int i=0; i<16; i++) { //making sure all array elements are = NULL
    fieldptr[i] = NULL;
    seedptr[i] = NULL;
  }

  //changing pointers to point to arrays
  field = fieldptr;
  seeds = seedptr;

}


//FUNDS FUNCTIONS

int Farm::getFunds() {
  return funds;
}

void Farm::fundsAdd(int addThis) {
  funds = funds + addThis;
}

void Farm::fundsTake(int takeThis) {
  funds = funds - takeThis;
}

//check if taking these funds will end in bankruptcy
bool Farm::checkIfBankrupt(int takeThis) {
  if (funds - takeThis >= 0) {
    return false;
  } else {
    return true;
  }
}

//FERTILISER FUNCTIONS

int Farm::getFertiliser() {
  return fertiliser;
}

void Farm::addFertiliser() {
  fertiliser++;
}

void Farm::takeFertiliser() {
  fertiliser--;
}


//ARRAY RETURN FUNCTIONS

Crop **Farm::getField() {
  return field;
}

Crop **Farm::getSeeds() {
  return seeds;
}

std::vector<Crop*> Farm::getHarvested() {
  return harvested;
}




//CROP ACTION FUNCTIONS

//adds crop to specified array
bool Farm::addCrop(Crop *addThis, Crop **array) {
  for (int i=0; i<16; i++) { //check for first "empty" spot in array
    if (array[i] == NULL) {
      array[i] = addThis;
      return true;
    }
  }
  return false;
}


//removes crop from specified array
void Farm::removeCrop(Crop *removeThis, Crop **array) {
  for (int i=0; i<16; i++) {
    if (array[i]->getType() == removeThis->getType()) {
      array[i] = NULL;
      break;
    }
    break;
  }
}


//adds +1 growthP to all crops in field
void Farm::waterCrops() {
  for (int i=0; i<16; i++) {
    if (field[i] != NULL) { //growing crops in field
      fundsTake(1);
      field[i]->grow();
    }
  }
}


//function for harvesting crops
void Farm::harvestCrops() {
  for (int i=0; i<16; i++) {
    if (field[i] != NULL) { //check if field[i] is empty

      //check if crops are mature
      if (field[i]->getGrowthP() == field[i]->getGrowthReq() || field[i]->getGrowthP() == field[i]->getGrowthReq()+1) {

        //harvest functionality for root crops
        if (field[i]->getCategory() == "root") {
          fundsAdd(field[i]->getSellPrice()); //harvesting mature crop and earning money
          harvested.push_back(field[i]);
          field[i] = NULL;
          continue;
        }

        //harvest functionality for vegetable crops
        if (field[i]->getCategory() == "vegetable") {
            if (field[i]->getRemainingYields() > 0) {
              harvested.push_back(field[i]);
              fundsAdd(field[i]->getSellPrice());
              field[i]->harvestReset();
            } else if (field[i]->getRemainingYields() == 0){
              fundsAdd(field[i]->getSellPrice()); //harvesting mature crop and earning money
              harvested.push_back(field[i]); //add to harvest vector for harvestPrint
              field[i] = NULL;
              continue;
            }
          }

          //harvest functionality for fruit crops
        if (field[i]->getCategory() == "fruit") {
          harvested.push_back(field[i]);
          fundsAdd(field[i]->getYieldNum()*field[i]->getSellPrice()); //harvesting mature crop and earning money
          field[i]->harvestReset();
        }

      //if crop rotten, remove with no earnings but +1 fertiliser
      } else if (field[i]->getGrowthP() == field[i]->getGrowthReq()+2) {
          harvested.push_back(field[i]);
          field[i] = NULL;
          fertiliser++;
      }
    }
  }
}


//plant crop - add crop to field
void Farm::plantCrop(Crop *plantCrop) {
  addCrop(plantCrop, field);
}


//function to fertilise a crop
void Farm::fertiliseCrop(Crop *needFertiliser) {
  for (int i=0; i<16; i++) {
    if (field[i]->getType() == needFertiliser->getType()) {
      field[i]->fertilise();
      fertiliser--;
      break;
    }
  }
}


void Farm::clearHarvested() {
  harvested.clear();
}


//farm destructor
Farm::~Farm() {
  delete[] field;
  delete[] seeds;
}

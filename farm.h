

#ifndef FARM_H
#define FARM_H

#include "crop.h"
#include "root.h"
#include <string>
#include <vector>

class Farm {

  private:
    Crop **field; //double pointer array representing the 'field'
    Crop **seeds; //double pointer array representing the player's seed collection
    int funds; //farms funds
    int fertiliser; //farms fertiliser count
    std::vector<Crop*> harvested; //vector to store crops per harvest

  public:
          Farm(); //constructor

          //funds
          int getFunds(); //returns funds
          void fundsAdd(int addThis); //adds to funds
          void fundsTake(int takeThis); //takes from funds
          bool checkIfBankrupt(int takeThis); //check if taking these funds will end in bankruptcy

          //fertiliser
          int getFertiliser(); //returns fertiliser count
          void addFertiliser(); //adds a fertiliser
          void takeFertiliser(); //takes a fertiliser

          //return arrays & vectors
          Crop **getField(); //returns field
          Crop **getSeeds(); //returns seeds
          std::vector<Crop*> getHarvested(); //returns harvested

          //crop actions
          bool addCrop(Crop *addThis, Crop **array); //adds a Crop object to a specified array (true if added, false if full)
          void removeCrop(Crop *removeThis, Crop **array); //removes a Crop object from a specified array
          void waterCrops(); //add +1 growth to all crops in field
          void harvestCrops(); //moves mature crops from field to harvested
          void plantCrop(Crop *plantCrop); //moves crop from seeds to field
          void fertiliseCrop(Crop *needFertiliser); //fertilises a crop
          void clearHarvested(); //clears harvested vector

          ~Farm(); //destructor
};


#endif //FARM_H

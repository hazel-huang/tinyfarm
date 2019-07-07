#include "crop.h"
#ifndef VEGETABLE_H
#define VEGETABLE_H

#include <string>

class Vegetable : public Crop {
  
  private:
    int remainingYields; //stores number of remaining yields of the crop (how many more times it can be harvested)

  public:
    Vegetable(std::string category, std::string type, char letter, int gReq, int buy, int sell); //constructor with parameters
    void fertilise(); //function for fertilising root crop
    void harvestReset(); //function for what happens when harvested
    int getRemainingYields(); //returns remainingYields
    int getYieldNum(); //inherited

};

#endif //VEGETABLE_H

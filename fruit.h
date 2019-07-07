#include "crop.h"

#ifndef FRUIT_H
#define FRUIT_H

#include <string>

class Fruit : public Crop {

  private:
    int yieldNum; //number of yield per harvest

  public:
    Fruit(std::string category, std::string type, char letter, int gReq, int buy, int sell);
    void harvestReset(); //function for what happens after fruit is harvested from tree
    int getYieldNum(); //returns yield num
    int getRemainingYields(); //inherited
    void fertilise(); //inherited
};

#endif //FRUIT_H

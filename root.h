#include "crop.h"
#ifndef ROOT_H
#define ROOT_H

#include <string>

class Root : public Crop {
  public:
    Root(std::string category, std::string type, char letter, int gReq, int buy, int sell); //root constructor
    void fertilise(); //fertilise to be instantly ready for harvest
    void harvestReset(); ///inherited
    int getRemainingYields(); //inherited
    int getYieldNum(); //inherited
};

#endif //ROOT_H

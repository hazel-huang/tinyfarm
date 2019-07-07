#ifndef CROP_H
#define CROP_H

#include <string>

class Crop {

  private:
    int buyPrice; //price to buy seed of crop
    int sellPrice; //price harvested crop is worth when sold

  protected:
    Crop(); //default crop constructor
    Crop(std::string category, std::string type, char letter, int gReq, int buy, int sell); //crop constructor with parameters
    std::string cropCategory; //stores type of crop i.e. root/veg/fruit?
    std::string cropType; //stores string describing type of crop e.g. onion, carrot
    char fieldLetter; //stores letter representing crop in field output
    int growthReq; //growth points required for plant to be mature and harvested
    int growthP; //number of current growth points
    int fertilised; //is plant fertilised?

  public:
    //functions to return crop data
    std::string getCategory(); //returns cropCategory
    std::string getType(); //returns crop type
    char getFieldLetter(); //returns fieldLetter
    int getBuyPrice(); //returns buyPrice
    int getSellPrice(); //returns sellPrice
    int getGrowthReq(); //returns growthReq
    int getGrowthP(); //returns growthP
    bool isFertilised();

    //functions to update crop data
    void grow(); //function that increments growth P
    void updateLetter(); //changes fieldLetter as needed (lowercase to upper when mature, X when rotten)

    //pure virtual functions
    virtual void fertilise() = 0; //fertilises plant, different definition for each subclass
    virtual void harvestReset() = 0; //resets harvest for veg and fruit crops
    virtual int getRemainingYields() = 0; //returns remainingYields (veg only)
    virtual int getYieldNum() = 0; //returns yieldNum (fruit only)
    virtual ~Crop(); //deconstructor

};

#endif //CROP_H

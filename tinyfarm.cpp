//include libraries
#include <cctype>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <stdio.h>

//include header files
#include "farm.h"
#include "crop.h"
#include "vegetable.h"
#include "root.h"
#include "fruit.h"

//forward declaration of functions where required
void visit();
void goField();
void fieldChoice();
void goShop();
void goMarket();
void plantMenu();
void harvestPrint();
void noHarvest();
void buySeeds(std::string cropName, char symbol, int growth, int buy, int sell, std::string cropCategory);
void winGame();
int checkAnyMatureCrops();

//creating farm objects and variables
Farm *tinyfarm = new Farm();
Crop **field = tinyfarm->getField();
Crop **seeds = tinyfarm->getSeeds();





//FUNCTIONS FOR GAME FUNCTIONALITY

//function to "clear" the screen using ASCII escape characters
void clearScreen() {
  std::cout << "\033[2J\033[1;1H";
}

//function to check if array is empty
bool checkEmptyArr(Crop **checkArray) {

  int empty = 0;

  for (int i=0; i<16; i++) {
    if (checkArray[i] == NULL) {
      empty++;
    }
  }

  if (empty == 16) {
    return true;
  } else {
    return false;
  }
}

//function to check if array is full
bool checkFullArr(Crop **checkArray) {

  int full = 0;

  for (int i=0; i<16; i++) {
    if (checkArray[i] != NULL) {
      full++;
    }
  }

  if (full == 16) {
    return true;
  } else {
    return false;
  }

}

//function to count number of occupied elements in an array
int countArr(Crop **countArray) {
  int count = 0;
  for (int i=0; i<16; i++) {
    if (countArray[i] != NULL) {
      count++;
    }
  }
  return count;
}

//function to print the field and funds
void printField() {
  std::cout << std::endl;
  std::cout << "    FUNDS: $" << tinyfarm->getFunds() << std::endl;
  std::cout << std::endl;
  for (int i=0; i<16; i++) {
    std::cout << "  ";
    if (field[i] == NULL) {
      std::cout << " #";
    } else {
      field[i]->updateLetter();
      std::cout << " " << field[i]->getFieldLetter();
    }
    if ((i+1) % 4 == 0) { //print endline at end of every row of 4
    std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

//output for bankruptcy
void bankrupt() {
  clearScreen();
  std::cout << "You don't have enough money left to complete this action." << std::endl;
}

//function to handle invalid user input
void invalidChoice() {
  std::cout << std::endl;
  std::cout << "Invalid input option." << std:: endl;
  std::cout << "Please enter one of the numbers above." << std::endl;
}

//function to continue cin in a looped switch statement
void switchCinContinue() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//function to end and quit the game, clearing memory
void endGame() {
  std::cout << std::endl;
  std::cout << "- - - - -  Thanks for visiting Tiny Farm!  - - - - -" << std::endl;
  std::cout << std::endl;
  delete tinyfarm;
}





//STARTING SCREEN MECHANISMS

//starting menu choice handler
void startMenu() {

  bool choiceLoop = true;
  int choice;
  std::cin >> choice; //user inputs choice

  while (choiceLoop == true) {
    switch (choice) { //direct program to next game screen based on input
      case 1:
              visit();
              choiceLoop = false;
              break;
      case 2:
              clearScreen();
              endGame();
              choiceLoop = false;
              break;
      default:
              invalidChoice();
              switchCinContinue();
              std::cin >> choice;
              break;
    }
  }
}


//starting scren string output
void start() {

  clearScreen();

  //introduction interface output
  std::cout << std::endl;

  std::cout << "- - - - -  WELCOME TO TINY FARM!  - - - - -" << std::endl;

  std::cout << std::endl;

  std::cout << "Your goal is to reach funds of $500 by selling crops you've grown." << std::endl;
  std::cout << std::endl;
  std::cout << "Crops can only be harvested once mature," << std::endl;
  std::cout << "i.e. when their growth requirement is fulfilled." << std::endl;
  std::cout << "Each time you water a crop, it gains +1 growth." << std::endl;
  std::cout << std::endl;
  std::cout << "When mature, a crop's signifier will go from lowercase to uppercase." << std::endl;
  std::cout << std::endl;
  std::cout << "Don't let your plants continue to grow for too long." << std::endl;
  std::cout << "After they're mature, they can rot and become fertiliser!" << std::endl;
  std::cout << std::endl;
  std::cout << "During the game, select the action you'd like to take by typing its number." << std::endl;
  std::cout << std::endl;

  std::cout << "1. START" << std::endl;
  std::cout << "2. EXIT" << std::endl;

  startMenu();

}

//location options handler
void visitChoice() {

  //interface output
  std::cout << std::endl;
  std::cout << "VISIT:" << std::endl;
  std::cout << "1. FIELD" << std::endl;
  std::cout << "2. SHOP" << std::endl;
  std::cout << "3. EXIT" << std::endl;

  bool choiceLoop = true;
  int choice;
  std::cin >> choice; //user inputs choice

  while (choiceLoop == true) {
    switch (choice) { //direct program to next game screen based on input
      case 1:
              goField();
              choiceLoop = false;
              break;
      case 2:
              goShop();
              choiceLoop = false;
              break;
      case 3:
              clearScreen();
              endGame();
              choiceLoop = false;
              break;
      default:
              invalidChoice();
              switchCinContinue();
              std::cin >> choice;
              break;
    }
  }
}

//function called from start() - prints location options
void visit() {
  clearScreen();
  visitChoice();
}





//PLANTING CROPS MECHANISMS

//user chooses which seed to plant
void plantChoice() {

  clearScreen();
  std::cout << "Which seed would you like to plant?" << std::endl;
  std::cout << std::endl;

  int seedIndex = 0;

  //print list of user's seeds with ordered index
  for (int i=0; i<16; i++) {
    if (seeds[i] != NULL) {
      seedIndex++;
      std::cout << seedIndex << ". " << seeds[i]->getType() << std::endl;
    }
  }

  std::cout << std::endl;
  std::cout << "0. GO BACK" << std::endl;

  //setting up choice cin loop
  bool choiceLoop = true;
  int choice;
  std::cin >> choice;

  int notNullCounter;
  int choiceIndex;

  while (choiceLoop == true) {

    notNullCounter = 1;
    choiceIndex = 0;

    //finding the seed index of choice input
    for (int i=1; i<=16; i++) {
      if (seeds[i-1] != NULL) {
        if (notNullCounter == choice) {
          choiceIndex = i-1;
        }
        notNullCounter++;
      }
    }

    if (choice == 0) {
      clearScreen();
      printField();
      fieldChoice();
    }

    if (notNullCounter <= choice) { //check if user selection is valid
      invalidChoice();
      switchCinContinue();
      std::cin >> choice;
    } else { //if choice valid,
      //plants seed and updates field
      tinyfarm->plantCrop(seeds[choiceIndex]);
      clearScreen();
      printField();
      std::cout << "You have planted a " << seeds[choiceIndex]->getType() << " seed!" << std::endl;
      std::cout << std::endl;
      seeds[choiceIndex] = NULL;
      fieldChoice();
      choiceLoop = false;

    }
  }
}

//directs user according to whether they have any seeds
void plantMenu() {
  if (checkEmptyArr(seeds) == true) { //if no seeds in seeds array redirect to visit()
    clearScreen();
    std::cout << std::endl;
    std::cout << "You have no seeds! Try buying some at the shop." << std::endl;
    visitChoice();
  } else { //takes to menu to choose which seed to plant
    plantChoice();
  }
}




//FERTILISER MECHANISMS

//asks user which crop they want to fertilise
void fertiliseChoice() {

  clearScreen();
  std::cout << std::endl;
  std::cout << "FERTILISERS: " << tinyfarm->getFertiliser() << std::endl; //display fertiliser count
  std::cout << std::endl;
  std::cout << "Which plant would you like to fertilise?" << std::endl;

  for (int i=0; i<16; i++) { //print list of unfertilised crops in field
    if (field[i] != NULL && field[i]->isFertilised() == false) {
      std::cout << i+1 << ". " << field[i]->getType() << std::endl;
    }
  }

  //setting up cin loop
  bool choiceLoop = true;
  int choice;
  std::cin >> choice;

  while (choiceLoop == true) {

    if (field[choice-1] == NULL ) {

      //if user selects crop not on the list above,
      invalidChoice();
      switchCinContinue();
      std::cin >> choice;

    } else if (field[choice-1]->isFertilised() == 0) { //if crop is not fertilised yet:

      //fertilise + update field, subtract 1 fertiliser, go to fieldChoice()
      tinyfarm->fertiliseCrop(field[choice-1]);
      clearScreen();
      printField();
      std::cout << "You've fertilised " << field[choice-1]->getType() << "!" << std::endl;
      std::cout << std::endl;
      fieldChoice();
      choiceLoop = false;

    }
  }
}

//check if every crop in the field is fertilised
bool checkFieldFertilised() {

  int numFertilised = 0;

  for (int i=0; i<16; i++) {
    if (field[i] != NULL) {
      if (field[i]->isFertilised() == true) {
        numFertilised++;
      }
    }
  }
  if (numFertilised == countArr(field)) {
    return true;
  }
  return false;
}

//fertilising options handler
void fertiliseMenu() {
  clearScreen();
  if (tinyfarm->getFertiliser() == 0) { //if no fertiliser, redirect to visit()
    std::cout << std::endl;
    std::cout << "You have no fertiliser! Try buying some at the shop." << std::endl;
    std::cout << "Rotten crops (X in the field) become fertiliser when harvested, too." << std::endl;
    std::cout << std::endl;
    std::cout << "It helps your fruit trees grow an extra fruit per harvest," << std::endl;
    std::cout << "and fully grows all other crops instantly." << std::endl;
    visitChoice();
  } else if (checkEmptyArr(field) == true) { //if no crops, redirect to visit()
    std::cout << "You have no crops to fertilise!" << std::endl;
    std::cout << "Try buying some seeds at the shop and planting them." << std::endl;
    visitChoice();
  } else if (checkFieldFertilised() == true) { //if all crops already fertilised, redirect to visit()
    std::cout << "All your crops have already been fertilised." << std::endl;
    std::cout << "Try buying some seeds at the shop and planting them." << std::endl;
    visitChoice();
  } else {
    fertiliseChoice();
  }
}





//FUNCTIONS FOR THE FIELD

//field action options string output
void fieldOutput() {
  std::cout << std::endl;
  std::cout << "What would you like to do?" << std::endl;
  std::cout << "1. Plant crops" << std::endl;
  std::cout << "2. Water crops" << std::endl;
  std::cout << "3. Harvest crops" << std::endl;
  std::cout << "4. Fertilise crops" << std::endl;
  std::cout << "5. Go elsewhere" << std::endl;
}

//field action choices menu
void fieldChoice() {

  fieldOutput();

  //setting up loop for switch and cin
  bool choiceLoop = true;
  int choice;

  std::cout << std::endl;
  std::cin >> choice;

  while (choiceLoop == true) {

    switch(choice) { //field action based on user input

      case 1: //plant crops
              std::cout << std::endl;
              plantMenu();
              choiceLoop = false;
              break;

      case 2: //water crops
              if (tinyfarm->checkIfBankrupt(countArr(field)) == false) { //if you can afford to water all crops:
                tinyfarm->waterCrops();
                clearScreen();
                printField();
                if (checkEmptyArr(field) == false) { //output for empty/not empty field
                  std::cout << "You've watered all of your crops." << std:: endl;
                } else {
                  std::cout << "You have no crops to water! Try planting some seeds." << std:: endl;
                }
                fieldOutput();
                switchCinContinue();
                std::cin >> choice;
                break;
              } else { //if you can't afford to water all crops:
                printField();
                bankrupt();
                std::cout << std::endl; //player guide output
                std::cout << "Harvest any crops you can to earn some money. However, if" << std::endl;
                std::cout << "you have no crops to harvest, then unfortunately you" << std:: endl;
                std::cout << "can't make any more money, since you can't afford to grow" << std:: endl;
                std::cout << "more crops to sell. " << std:: endl;
                fieldOutput();
                switchCinContinue();
                std::cin >> choice;
                break;
              }

      case 3: //harvest crops

              if (checkAnyMatureCrops() == 0) {
                noHarvest();
              } else {
                tinyfarm->harvestCrops();
                clearScreen();
                printField();
                std::cout << std::endl;
                harvestPrint();
              }

              //trigger winGame if funds exceed 500
              if (tinyfarm->getFunds() >= 500){
                winGame();
                choiceLoop = false;
                break;
              }

              fieldOutput();
              switchCinContinue();
              std::cin >> choice;
              break;

      case 4: //fertilise crops
              fertiliseMenu();
              choiceLoop = false;
              break;

      case 5: //back to location selection
              visit();
              choiceLoop = false;
              break;

      default:
              invalidChoice();
              switchCinContinue();
              std::cin >> choice;
              break;
    };
  }
}

//function called from visit() - prints field and options
void goField() {

  clearScreen();
  printField();
  fieldChoice();

}





//FUNCTIONS FOR THE SHOP

//menu listing user choices for after buying something
void menuAfterBuying() {

  std::cout << std::endl;
  std::cout << "1. Return to shop" << std::endl;
  std::cout << "2. Go elsewhere" << std::endl;
  std::cout << std::endl;

  //setting up cin & switch statement loop
  bool choiceLoop = true;
  int choice;
  std::cin >> choice;

  while (choiceLoop == true) {
    switch(choice) {
      case 1:
              goShop();
              choiceLoop = false;
              break;
      case 2:
              visit();
              choiceLoop = false;
              break;

      default:
              invalidChoice();
              switchCinContinue();
              std::cin >> choice;
              break;
    }
  }
}


// SEED TRANSACTION SCREEN
void buySeeds(std::string cropName, char symbol, int growth, int buy, int sell, std::string cropCategory) {

  clearScreen();
  int buyNum;

  std::cout << std::endl;
  std::cout << "How many "<< cropName <<" seeds would you like to buy?" << std::endl;
  std::cout << std::endl;
  std::cin >> buyNum; //user input for buying qty

  if (tinyfarm->checkIfBankrupt(buy*buyNum) == false) { //if you can afford:

    //create desired object and add to seeds array
    for (int i=0; i<buyNum; i++) {
      tinyfarm->fundsTake(buy);
      if (checkFullArr(seeds) == false){
        if (cropCategory.compare("root") == 0){
          tinyfarm->addCrop(new Root(cropCategory, cropName, symbol, growth, buy, sell), seeds);
        } else if (cropCategory.compare("vegetable") == 0){
          tinyfarm->addCrop(new Vegetable(cropCategory, cropName, symbol, growth, buy, sell), seeds);
        } else {
          tinyfarm->addCrop(new Fruit(cropCategory, cropName, symbol, growth, buy, sell), seeds);
        }
      } else { //string output for when seeds = full, redirect to location menu
        std::cout << "You've reached the max seed storage capacity of 16." << std::endl;
        std::cout << "Please plant some then buy more." << std::endl;
        visitChoice();
        break;
      }
    }

    //string output stating what has been bought, with cases for plural and non-plural statements
    std::cout << "You have bought " << buyNum << " " << cropName << " seed";
    if (buyNum > 1){
      std::cout<<"s";
    }
    std::cout<<"."<<std::endl;

  } else { //if you can't afford:
    bankrupt();
  }
  menuAfterBuying();
}

//fertiliser transaction screen
void buyFertiliser() {

  clearScreen();
  int buyNum;

  std::cout << std::endl;
  std::cout << "How many fertilisers would you like to buy?" << std::endl;
  std::cout << std::endl;
  std::cin >> buyNum; //user input for buying qty

  //fertiliser buying
  if (tinyfarm->checkIfBankrupt(buyNum*2) == false) { //can afford:

    tinyfarm->fundsTake(buyNum*2);
    tinyfarm->addFertiliser();
    std::cout << "You have bought " << buyNum << " " << "fertiliser"; //string output stating what has been bought
    if (buyNum > 1){                                                  // cases for plural and non-plural statements
      std::cout<<"s";
    }
    std::cout<<"."<<std::endl;

  } else { //can't afford:
    bankrupt();
  }

  menuAfterBuying();

}

//switch statement for what user is buying at shop
void shopChoice() {

  //setting up switch statement repeat loop
  bool choiceLoop = true;
  int choice;
  std::cin >> choice;

  //initialising empty data variables
  std::string cropName = "";
  std::string cropCategory = "";
  char symbol = '?';
  int growth, buy, sell;

  while (choiceLoop == true) {

    cropName = ""; //reset cropName to empty

    switch(choice) { //create object data based on user input
      case 1:
              buyFertiliser();
              choiceLoop = false;
              break;
      case 2:
              cropName = "onion";
              symbol = 'o';
              growth = 1;
              buy = 3;
              sell = 9;
              cropCategory = "root";
              choiceLoop = false;
              break;
      case 3:
              cropName = "carrot";
              symbol = 'c';
              growth = 3;
              buy = 5;
              sell = 16;
              cropCategory = "root";
              choiceLoop = false;
              break;
      case 4:
              cropName = "eggplant";
              symbol = 'e';
              growth = 5;
              buy = 8;
              sell = 18;
              cropCategory = "vegetable";
              choiceLoop = false;
              break;
      case 5:
              cropName = "broccoli";
              symbol = 'b';
              growth = 8;
              buy = 10;
              sell = 26;
              cropCategory = "vegetable";
              choiceLoop = false;
              break;
      case 6:
              cropName = "lemon";
              symbol = 'l';
              growth = 10;
              buy = 45;
              sell = 20;
              cropCategory = "fruit";
              choiceLoop = false;
              break;
      case 7:
              cropName = "avocado";
              symbol = 'a';
              growth = 15;
              buy = 65;
              sell = 29;
              cropCategory = "fruit";
              choiceLoop = false;
              break;
      case 8:
              visit();
              choiceLoop = false;
              break;
      default:
              invalidChoice();
              switchCinContinue();
              std::cin >> choice;
              break;
    }

    if (cropName.compare("") != 0){
      buySeeds(cropName, symbol, growth, buy, sell, cropCategory);
    }
  }
}


//'SHOP' LOCATION - BUY CROP SEEDS & FERTILISER; SHOWS INFO ABOUT THE ITEMS
void goShop() {

  clearScreen();

  std::cout << "____________" << std::endl;
  std::cout << "----SHOP----    FUNDS: $" << tinyfarm->getFunds() << std::endl;
  std::cout << "‾‾‾‾‾‾‾‾‾‾‾‾" << std::endl;
  std::cout << "$2  | FERTILISER     | grows roots and vegetables instantly, +1 fruit yield" << std::endl;
  std::cout << "$3  | ONION BULB     | mature @ 1 growth; single harvest" << std::endl;
  std::cout << "$5  | CARROT SEED    | mature @ 3 growth; single harvest" << std::endl;
  std::cout << "$8  | EGGPLANT SEED  | mature @ 5 growth; can harvest 3 times" << std::endl;
  std::cout << "$10 | BROCCOLI SEED  | mature @ 8 growth; can harvest 3 times" << std::endl;
  std::cout << "$45 | LEMON TREE     | mature @ 10 growth; harvest every +2 growth after maturity" << std::endl;
  std::cout << "$65 | AVOCADO TREE   | mature @ 10 growth; harvest every +3 growth after maturity" << std::endl;


  std::cout << "What would you like to buy today?" << std::endl;

  std::cout << std::endl;

  std::cout << "1. Fertiliser" << std::endl;
  std::cout << "2. Onion bulb" << std::endl;
  std::cout << "3. Carrot seed" << std::endl;
  std::cout << "4. Eggplant seed" << std::endl;
  std::cout << "5. Broccoli seed" << std::endl;
  std::cout << "6. Lemon tree" << std::endl;
  std::cout << "7. Avocado tree" << std::endl;
  std::cout << "8. Go elsewhere" << std::endl;

  shopChoice();

}

//function to check if field has mature crops
int checkAnyMatureCrops() {
  int matureCrops = 0;
  for (int i=0; i<16; i++) {
    if (field[i] != NULL) {
      if (field[i]->getGrowthP() >= field[i]->getGrowthReq()) {
        matureCrops++;
      }
    }
  }
  return matureCrops;
}

//output for when there are no crops to harvest
void noHarvest() {
  std::cout << "None of your crops are ready to be harvested yet!" << std::endl;
  std::cout << "Try watering or fertilising your crops." << std:: endl;
  std::cout << std::endl;
}

//PRINTS LIST OF HARVESTED CROPS
void harvestPrint() {

  std::cout << "All mature crops have been harvested and sold!" << std::endl;
  std::cout << "You harvested:" << std:: endl;
  std::cout << std::endl;

  int cropCountArr[] = {0, 0, 0, 0, 0, 0};
  std::string cropNamesArr[] = {"onion", "carrot", "eggplant", "broccoli", "lemon", "avocado"};

  std::vector<Crop*> harvested;
  harvested = tinyfarm->getHarvested();

  for (int i=0; i<harvested.size(); i++) { //counting up how many of each type of crop was harvested
    std::string type = harvested[i]->getType();
    for (int i=0; i<6; i++) {
      if (type == cropNamesArr[i]) {
        cropCountArr[i]++;
      }
    }
  }

  for (int i=0; i<6; i++) {
    if (cropCountArr[i] > 0){
      std::cout << " " << cropCountArr[i] << " " << cropNamesArr[i];
      if (cropCountArr[i] > 1){
        std::cout<<"s";
      }
      std::cout << std::endl;
    }
  }
  tinyfarm->clearHarvested();

}


//text output when win condition is met ($500+)
void winGame() {
  clearScreen();
  std::cout << std::endl;
  std::cout << "You've hit your goal of $500!" << std::endl;
  std::cout << "Congratulations, you've won the game!" << std::endl;
  for (int i=0; i<5; i++) {
    std::cout << std::endl;
    std::cout << std::endl;
  }
  endGame();
}

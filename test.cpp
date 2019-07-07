#include "farm.h"
#include "crop.h"
#include "vegetable.h"
#include "root.h"
#include "fruit.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>

std::string rootType = "carrot";
std::string root = "root";
char rootLetter = 'c';
int rootGReq = 2;
int rootBuyPrice = 2;
int rootSellPrice = 5;


std::string fruitType = "lemon";
std::string fruit = "fruit";
char fruitLetter = 'l';
int fruitGReq = 2;
int fruitBuyPrice = 3;
int fruitSellPrice = 7;


std::string vegType = "eggplant";
std::string vegetable = "vegetable";
char vegLetter = 'e';
int vegGReq = 4;
int vegBuyPrice = 5;
int vegSellPrice = 3;



std::string checkString(std::string results, std::string expected){
	if (results.compare(expected) == 0){
		return "Passed";
	} else {
		return "Expected: " + expected + "   but got: " + results;
	}
}

std::string checkInt(int results, int expected){
	if (results == expected){
		return "Passed";
	} else {
		return "Expected: " + std::to_string(expected) + "   but got: " + std::to_string(results);
	}
}

std::string checkChar(char results, char expected){
	if (results == expected){
		return "Passed";
	} else {
		std::string output = "Expected: ";
		output += expected;
		output += "   but got: ";
		output += results;
		return output;
	}
}

std::string doublePtrToString(Crop** doublePtr, int n){
	std::string str = "";
	for (int i = 0; i < n; i++){
		if (doublePtr[i] == NULL){
			str += " ";
		} else {
			str += doublePtr[i]->getFieldLetter();
		}
	}
	return str;
}

void testCrop(){

	// Test root
	Root* testRoot = new Root(root, rootType, rootLetter, rootGReq, rootBuyPrice, rootSellPrice);

	std::cout << "--------------- TESTING CROP.CPP (ROOT) ---------------" <<  std::endl;
	std::cout << "Test getType: " << checkString(testRoot->getType(), rootType) << std::endl;
	std::cout << "Test getFieldLetter: " << checkChar(testRoot->getFieldLetter(), rootLetter) << std::endl;
	std::cout << "Test getGrowthReq: " << checkInt(testRoot->getGrowthReq(), rootGReq) << std::endl;
	std::cout << "Test getBuyPrice: " << checkInt(testRoot->getBuyPrice(), rootBuyPrice) << std::endl;
	std::cout << "Test getSellPrice: " << checkInt(testRoot->getSellPrice(), rootSellPrice) << std::endl;
	std::cout << "Test getCategory: " << checkString(testRoot->getCategory(), root) << std::endl;


	std::cout << "Test getGrowthP: " << checkInt(testRoot->getGrowthP(), 0) << std::endl;

	testRoot->grow();
	std::cout << "Test growth: " << checkInt(testRoot->getGrowthP(), 1) << std::endl;

	testRoot->grow();
	std::cout << "Test updateLetter(grown): " << checkChar(testRoot->getFieldLetter(), toupper(rootLetter)) << std::endl;

	testRoot->grow();
	testRoot->grow();
	std::cout << "Test growth (part 2): " << checkInt(testRoot->getGrowthP(), 4) << std::endl;
	std::cout << "Test updateLetter(rotten): " << checkChar(testRoot->getFieldLetter(), 'X') << std::endl;

	testRoot = new Root(root, rootType, rootLetter, rootGReq, rootBuyPrice, rootSellPrice);
	std::cout << "Test fertilise (before): " << checkInt(testRoot->getGrowthP(), 0) << std::endl;
	testRoot -> fertilise();
	std::cout << "Test fertilise (after): " << checkInt(testRoot->getGrowthP(), rootGReq) << std::endl;




	// Test fruit
	Fruit* testFruit = new Fruit(fruit, fruitType, fruitLetter, fruitGReq, fruitBuyPrice, fruitSellPrice);

	std::cout << std::endl << std::endl;
	std::cout << "--------------- TESTING CROP.CPP (FRUIT) ---------------" <<  std::endl;
	std::cout << "Test getType: " << checkString(testFruit->getType(), fruitType) << std::endl;
	std::cout << "Test getFieldLetter: " << checkChar(testFruit->getFieldLetter(), fruitLetter) << std::endl;
	std::cout << "Test getGrowthReq: " << checkInt(testFruit->getGrowthReq(), fruitGReq) << std::endl;
	std::cout << "Test getBuyPrice: " << checkInt(testFruit->getBuyPrice(), fruitBuyPrice) << std::endl;
	std::cout << "Test getSellPrice: " << checkInt(testFruit->getSellPrice(), fruitSellPrice) << std::endl;
	std::cout << "Test getCategory: " << checkString(testFruit->getCategory(), fruit) << std::endl;


	std::cout << "Test getGrowthP: " << checkInt(testFruit->getGrowthP(), 0) << std::endl;

	int yieldNum = 3;
	std::cout << "Test getYieldNum: " << checkInt(testFruit->getYieldNum(), yieldNum) << std::endl;
	testFruit->fertilise();
	std::cout << "Test fertilise: " << checkInt( testFruit->getYieldNum(), yieldNum + 2) << std::endl;


	testFruit->grow();
	std::cout << "Test growth: " << checkInt(testFruit->getGrowthP(), 1) << std::endl;

	testFruit->grow();
	testFruit->grow();
	std::cout << "Test updateLetter(became tree): " << checkChar(testFruit->getFieldLetter(), toupper(fruitLetter)) << std::endl;
	std::cout << "Test growth (became tree): " << checkInt(testFruit->getGrowthReq(), 2) << std::endl;

	testFruit->grow();
	testFruit->grow();
	std::cout << "Test updateLetter(rotten): " << checkChar(testFruit->getFieldLetter(), 'X') << std::endl;



	// Test vegetable
	Vegetable* testVeg = new Vegetable(vegetable, vegType, vegLetter, vegGReq, vegBuyPrice, vegSellPrice);

	std::cout << std::endl << std::endl;
	std::cout << "--------------- TESTING CROP.CPP (VEGETABLE) ---------------" <<  std::endl;
	std::cout << "Test getType: " << checkString(testVeg->getType(), vegType) << std::endl;
	std::cout << "Test getFieldLetter: " << checkChar(testVeg->getFieldLetter(), vegLetter) << std::endl;
	std::cout << "Test getGrowthReq: " << checkInt(testVeg->getGrowthReq(), vegGReq) << std::endl;
	std::cout << "Test getBuyPrice: " << checkInt(testVeg->getBuyPrice(), vegBuyPrice) << std::endl;
	std::cout << "Test getSellPrice: " << checkInt(testVeg->getSellPrice(), vegSellPrice) << std::endl;
	std::cout << "Test getCategory: " << checkString(testVeg->getCategory(), vegetable) << std::endl;


	std::cout << "Test getGrowthP: " << checkInt(testVeg->getGrowthP(), 0) << std::endl;

	int remainingYields = 3;
	std::cout << "Test getRemainingYields: " << checkInt(testVeg->getRemainingYields(), remainingYields) << std::endl;
	testVeg->fertilise();
	std::cout << "Test fertilise: " << checkInt( testVeg->getGrowthP(), vegGReq) << std::endl;
std::cout << "Test updateLetter(fertilised): " << checkChar(testVeg->getFieldLetter(), toupper(vegLetter)) << std::endl;

	testVeg->harvestReset();
	std::cout << "Test harvestReset (growth points): " << checkInt( testVeg->getGrowthP(), 0) << std::endl;
	std::cout << "Test harvestReset (remaining yields): " << checkInt( testVeg->getRemainingYields(), remainingYields-1) << std::endl;

	for (int i = 0; i < remainingYields-1; i++){
		testVeg->fertilise();
		testVeg->harvestReset();
	}
	std::cout << "Test remainingYields: " << checkInt( testVeg->getRemainingYields(), 0) << std::endl;
}




void testFarm(){
	Farm *testfarm = new Farm();
	int initialFunds = 300;

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "--------------- TESTING FARM.CPP ---------------" <<  std::endl;
	std::cout << "Test getFunds: " << checkInt(testfarm->getFunds(), initialFunds) << std::endl;

	int initialFertiliser = 0;
	std::cout << "Test getFertiliser: " << checkInt(testfarm->getFertiliser(), initialFertiliser) << std::endl;

	int FIELD_LENGTH = 16;
	int SEEDS_LENGTH = 16;
	int HARVEST_LENGHT = 20;

	Root* c1 = new Root(root, rootType, rootLetter, rootGReq, rootBuyPrice, rootSellPrice);
	Root* c2 = new Root(root, rootType, rootLetter, rootGReq, rootBuyPrice, rootSellPrice);
	Root* c3 = new Root(root, rootType, rootLetter, rootGReq, rootBuyPrice, rootSellPrice);

	Fruit* c4 = new Fruit(fruit, fruitType, fruitLetter, fruitGReq, fruitBuyPrice, fruitSellPrice);
	Fruit* c5 = new Fruit(fruit, fruitType, fruitLetter, fruitGReq, fruitBuyPrice, fruitSellPrice);

	Root* c6 = new Root(root, rootType, rootLetter, rootGReq, rootBuyPrice, rootSellPrice);

	Fruit* c7 = new Fruit(fruit, fruitType, fruitLetter, fruitGReq, fruitBuyPrice, fruitSellPrice);
	Fruit* c8 = new Fruit(fruit, fruitType, fruitLetter, fruitGReq, fruitBuyPrice, fruitSellPrice);

	Vegetable* c9 = new Vegetable(vegetable, vegType, vegLetter, vegGReq, vegBuyPrice, vegSellPrice);

	testfarm->plantCrop(c1);
	testfarm->plantCrop(c2);
	testfarm->plantCrop(c3);
	testfarm->plantCrop(c4);
	testfarm->plantCrop(c5);
	testfarm->plantCrop(c6);
	testfarm->plantCrop(c7);
	testfarm->plantCrop(c8);
	testfarm->plantCrop(c9);

	std::string expectedField = "cccllclle       ";
	std::string currentField = doublePtrToString(testfarm->getField(), FIELD_LENGTH);
	std::cout << "Test plantCrop: " << checkString( currentField, expectedField ) << std::endl;
}


// void testField() {
// 	Farm *testFarm = new Farm();
// 	Crop **testField = testFarm->getField();
// 	for (int i=0; i<16; i++) {
// 		std::cout << testField[i] << std::endl;
// 	}
// }



int main() {
	testCrop();
	testFarm();
	return 0;
}

COMPILE_CMD = g++ -std=c++11
main: crop.cpp vegetable.cpp root.cpp fruit.cpp farm.cpp tinyfarm.cpp main.cpp
	${COMPILE_CMD} crop.cpp vegetable.cpp root.cpp fruit.cpp farm.cpp tinyfarm.cpp main.cpp -o main
test: crop.cpp vegetable.cpp root.cpp fruit.cpp farm.cpp tinyfarm.cpp test.cpp
	${COMPILE_CMD} crop.cpp vegetable.cpp root.cpp fruit.cpp farm.cpp tinyfarm.cpp test.cpp -o test
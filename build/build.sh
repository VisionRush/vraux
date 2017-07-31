# ***************************
# Dynamic link library model
# ***************************
# compile dynamic lib
g++ -std=c++11 -fPIC -shared ../src/*.cpp -o libvraux.so
# link dynamic-lib to main
g++ -std=c++11 ../test/*.cpp -o main -I ../src -L . -lvraux


# ***************************
# Dynamic link library model
# ***************************
# compile static lib
g++ -std=c++11 -c ../src/*.cpp
ar -crv libvraux.a *.o
rm *.o
# link static-lib to main
g++ -std=c++11 ../test/*.cpp -o main -I ../src -L . libvraux.a
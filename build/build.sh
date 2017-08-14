# ***************************
# Dynamic link library model
# ***************************
# compile dynamic lib
g++ -std=c++11 -fPIC -shared -Wl,-soname,libvraux.so.0 -o libvraux.so.0.1.5 ../src/*.cpp -I ../include
ln -s libvraux.so.0.1.5 libvraux.so.0
ln -s libvraux.so.0 libvraux.so
# link dynamic-lib to main
g++ -std=c++11 ../test/*.cpp -o main -I ../include -L . -lvraux


NotExce(){

# ***************************
# Static link library model
# ***************************
# compile static lib
g++ -std=c++11 -c ../src/*.cpp
ar -crv libvraux.a *.o
rm *.o
# link static-lib to main
g++ -std=c++11 ../test/*.cpp -o main -I ../src -L . libvraux.a

}
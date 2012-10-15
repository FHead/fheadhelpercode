g++ LargeInteger.cpp -c -o LargeInteger.o
g++ TestInteger.cpp LargeInteger.o -o RunTest
g++ ProgressBar.cpp -c -o ProgressBar.o
g++ LSC.cpp -c -o LSC.o
g++ main.cpp -o LSC LSC.o LargeInteger.o ProgressBar.o

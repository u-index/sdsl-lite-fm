build:
    g++ -O3 -march=native -static-libstdc++ -static lib.cpp -l sdsl -l divsufsort -l divsufsort64 -o libsdslfm.o -c && ar rcs libsdslfm.a libsdslfm.o

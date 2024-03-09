cd .\build\
cmake -G "MinGW Makefiles" -S .. -B . -DCMAKE_C_COMPILER=E:/ENV/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=E:/ENV/mingw64/bin/g++.exe
make
cd ..
.\bin\TheNextWeek.exe


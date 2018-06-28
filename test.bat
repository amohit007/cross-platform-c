cls
mkdir bin
clang src/*.c tests/*.c -I include -o bin/test.exe -Weverything -l shlwapi.lib -l AdvAPI32.lib
"bin/test"

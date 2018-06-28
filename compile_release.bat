cls
clang src/*.c -Weverything -l shlwapi.lib -l AdvAPI32.lib -I include -Ofast -D NDEBUG

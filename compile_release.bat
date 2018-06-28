cls
clang src/*.c -I include -Weverything -l shlwapi.lib -l AdvAPI32.lib -Ofast -D NDEBUG

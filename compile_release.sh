#!/bin/bash

clear
gcc src/*.c -I include -Wall -lpthread -Ofast -D NDEBUG

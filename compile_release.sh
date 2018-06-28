#!/bin/bash

clear
gcc src/*.c -Wall -lpthread -I include -Ofast -D NDEBUG

#MakeFile to build  the Sample US CENSUS Name Data 
# For CSC3004 Software Development

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++11

RM= /bin/rm -f

all: namesdemo

namesdemo: namesdemo.cpp
	$(CC) namesdemo.cpp -o namesdemo

clean:
	rm -f *.o  namesdemo

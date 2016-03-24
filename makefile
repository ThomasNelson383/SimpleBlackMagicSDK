CC = g++
CFLAGS = -g -Wall -I
LDFLAGS=-lm -ldl -lpthread

INCLUDE_SDK = decklinkSDK/
SRC_SDK = $(wildcard decklinkSDK/*.cpp)
OBJ_SDK =  $(SRC_SDK:.cpp=.o)

SRC_SIMPLE_SDK = decklink.cpp
OBJ_SIMPLE_SDK = decklink.o

all: main.o

main.o: OBJ_SDK OBJ_SIMPLE_SDK
	$(CC) $(CFLAGS) $(INCLUDE_SDK) $(OBJ_SDK) $(OBJ_SIMPLE_SDK) main.cpp -o DeckLinkSample $(LDFLAGS)

OBJ_SIMPLE_SDK:
	$(CC) $(CFLAGS) $(INCLUDE_SDK) -c $(SRC_SIMPLE_SDK)

OBJ_SDK:
	$(CC) $(CFLAGS) $(INCLUDE_SDK) -c $(SRC_SDK) -o $(OBJ_SDK)

clean:
	rm DeckLinkSample $(OBJ_SDK) $(OBJ_SIMPLE_SDK)

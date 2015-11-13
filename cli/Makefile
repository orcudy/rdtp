CC=g++ 
CFLAGS=-Wall -Werror
LDFLAGS=
SRC=Header.cpp Socket.cpp UDPServer.cpp Error.cpp  main.cpp
OBJ=$(SRC:.cpp=.o)
EXE=rtcserver

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o $(EXE)

fullclean:
	rm Header.*
	rm Socket.*
	rm UDPServer.*
	rm Server.*
	rm Error.*
	rm main*

sync:
	./sync.sh . ../xcode/rdt/

push:
	./sync.sh ../xcode/rdt/ .
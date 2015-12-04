#RDTP

RDTP is an implementation of the Go-Back-N reliable data transfer protocol over UDP. The repository includes both sender (server) and receiver (client) programs. 

##Building

Build the client and server programs by navigating to the project directory and running the `make` utility. 

This builds both a `client` and `server` executable. From the root directory of the project, the executables can be found in `bin/client` and `bin/server`.

##Running

###Server 

The `server` program can be run with the following options:

`[--port, -p] portno` -- sets the server port number to *portno*

`[--timeout, -t] timeoutInterval -- sets the server timeout interval for data retransmission

`[-window, -w] windowSize` -- sets the server window size for the Go-Back-N reliable  data transfer protocol

`[--verbose, -v]` -- prints protocol information to the console

`[--print-sent, -ps] -- prints all sent data to stdout

`[--print-recv, -pr] -- prints all received data to stdout

`[--print-all, -pa]` -- prints both sent and received data to stdout

# Class Reference

## Socket
Provides all socket related functionality.

#### Constructor
- `Socket(std::string ip, int port, TransportLayer type)`

  *Creates a new socket.*
  - **ip**: IP address (dot decimal notation or URL)
  - **port**: port number
  - **type**: transport layer protocol (UDP or TCP)

#### Instance Methods

The following are used internally to configure sockets, but have been made public for lower level operations.

- `void getAddressInfo()`
- `void getDescriptor()`
- `void bind()`

## Communicator (Abstract Base Class)
Provides an abstract base class that serves as a generic network communicator.

#### Instance Properties
- `Socket socket`
- `int receiveBufferSize`
- `char * receiveBuffer`

#### Pure Virtual Instance Methods
- `virtual int send(char * message) = 0`
- `virtual char * receive() = 0`

## UDPCommunicator
Subclass of `Communicator` which provides implementations for sending and receiving messages over the network using the UDP transport protocol.

#### Constructors
- `void baseConstructor(UDPCommunicator * communicator, std::string ip, int port)`
  - **communicator**: instance which is being initialized
  - **ip**: IP address (dot decimal notation or URL)
  - **port**: port number

- `UDPCommunicator(std::string ip, int port)`

  *Create a client who communicates with host at address \<ip\> on port \<port\>.*
  - **ip**: IP address (dot decimal notation or URL)
  - **port**: port number

- `UDPCommunicator(int port)`

  *Creates a server at host ip listening on port \<port\>*
  - **port**: port number

#### Instance Methods
- `int send(char * message)`
  - **returns**: number of bytes sent
  - **message**: message to be sent across network

- `char * receive()`
  - **returns:** message received

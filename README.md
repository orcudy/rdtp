#RDTP

RDTP is an implementation of the Go-Back-N reliable data transfer protocol over UDP. The repository includes both sender (target/server.cpp) and receiver (target/client.cpp) programs. 

The project contains both a .xcodeproj file and Makefile. This architecture is intended and allows for easy editing/compilation when using the Xcode environment or the command line. 

For all inquiries, please contact Chris Orcutt at orcutt.chris@gmail.com.

###Building

Build the client and server programs by navigating to the project directory and running the `make` utility. 

This builds both a `client` and `server` executable. From the root directory of the project, the executables can be found in `bin/client` and `bin/server`.

###Running

#####Server 

The `server` program can be run with the following options:

`[--port, -p] portno` -- sets the server port number to *portno*

`[--timeout, -t] timeoutInterval` -- sets the server timeout interval for data retransmission to *timeoutInterval*

`[-window, -w] windowSize` -- sets the server window size for the Go-Back-N reliable data transfer protocol to *windowSize*

`[--verbose, -v]` -- prints protocol information to the console

`[--print-sent, -ps]` -- prints all sent data to stdout

`[--print-recv, -pr]` -- prints all received data to stdout

`[--print-all, -pa]` -- prints both sent and received data to stdout

Without any options, running `server` defaults to port 45000 with a window size of 10 and timeout interval of 1 second.

#####Client 

The `client` program can be run with the following options:

`[--filename, -f] filename` -- sets the filename that the client is requesting from the server

`[--ip-address, -ip] ipaddress` -- sets the IP address of the server with which the client wants to communicate to *ipaddress*. (Note: Both dot decimal and URL formats are supported.)

`[--port, -p] portno` -- sets the port number of the server with which the client wants to communicate to *portno*

`[--timeout, -t] timeoutInterval` -- sets the client timeout interval for data syn transmission to *timeoutInterval*

`[-lost, -l] probabilityOfLoss` -- testing option used to simulate packet loss with probability *probabilityOfLoss*

`[-corrupt, -c] probabilityOfCorruption` -- testing option used to simulate packet corruption with probability *probabilityOfCorruption*

`[--verbose, -v]` -- prints protocol information to the console

`[--print-sent, -ps]` -- prints all sent data to stdout

`[--print-recv, -pr]` -- prints all received data to stdout

`[--print-all, -pa]` -- prints both sent and received data to stdout

The `client` program must be given a filename to run successfully. Without any options, the `client` program defaults to connecting to the `localhost` on port 45000 with a timeout interval of 1 second.

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

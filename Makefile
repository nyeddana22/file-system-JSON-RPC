# Makefile for HW1, ecs251, w2022
#

CC = g++ -std=c++17

# CFLAGS = -g
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

CORE_INCS =	Core.h Transaction.h Person.h
CORE_OBJS =	Core.o Transaction.o Person.o

LDFLAGS_SV = -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server
LDFLAGS_CL = -ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client

# rules.
all: 	hw1client hw1server hw1another

#
#

hw1client.h:		ecs251_hw1.json
	jsonrpcstub ecs251_hw1.json --cpp-server=hw1Server --cpp-client=hw1Client

hw1server.h:		ecs251_hw1.json
	jsonrpcstub ecs251_hw1.json --cpp-server=hw1Server --cpp-client=hw1Client

Core.o:			Core.cpp Core.h
	$(CC) -c $(CFLAGS) Core.cpp

Person.o:		Person.cpp Person.h Core.h
	$(CC) -c $(CFLAGS) Person.cpp

Transaction.o:		Transaction.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Transaction.cpp

Shadow_Flight.o:	Shadow_Flight.cpp Shadow_Flight.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Shadow_Flight.cpp

Shadow_Person.o:	Shadow_Person.cpp Shadow_Person.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Shadow_Person.cpp

hw1client.o:		hw1client.cpp Shadow_Flight.h Shadow_Person.h $(CORE_INCS) hw1client.h
	$(CC) -c $(CFLAGS) hw1client.cpp

hw1server.o:		hw1server.cpp $(CORE_INCS) hw1server.h
	$(CC) -c $(CFLAGS) hw1server.cpp

hw1server:		$(CORE_OBJS) hw1server.o
	$(CC) -o hw1server $(CORE_OBJS) hw1server.o Shadow_Flight.o Shadow_Person.o $(LDFLAGS_SV) $(LDFLAGS_CL)

# hw1client --> hw1server --> hw1another

hw1another.o:		hw1another.cpp $(CORE_INCS) hw1server.h
	$(CC) -c $(CFLAGS) hw1another.cpp

hw1another:		$(CORE_OBJS) hw1another.o
	$(CC) -o hw1another $(CORE_OBJS) hw1another.o $(LDFLAGS_SV) $(LDFLAGS_CL)

hw1client:		$(CORE_OBJS) hw1client.o Shadow_Flight.o Shadow_Person.o
	$(CC) -o hw1client $(CORE_OBJS) hw1client.o Shadow_Flight.o Shadow_Person.o $(LDFLAGS_CL)

clean:
	rm -f *.o *~ core hw1client hw1server hw1another hw1client.h hw1server.h


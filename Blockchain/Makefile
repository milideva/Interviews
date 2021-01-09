CXX = g++ 
CXXFLAGS  = -std=c++2a -g
LDFLAGS = -L/usr/local/opt/openssl/lib -lcrypto -lcpprest -ljsoncpp

SRCS := $(shell find . -name "*.c++")
#OBJS := $(subst .c++,.o,$(SRCS))
OBJS := $(patsubst %.c++,%.o,$(SRCS))
DEPENDS := $(patsubst %.c++,%.d,$(SRCS))

# The build target 
TARGET = blockchain
REST_CLIENT = restclient
PROTO_CLIENT = protoclient

all: $(TARGET) $(REST_CLIENT) $(PROTO_CLIENT)

#$(TARGET): $(SRCS)
#	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# all those object files ($^) into that same executable ($@).
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

-include $(DEPENDS)

%.o: %.c++ Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(REST_CLIENT): restClient.cpp
	$(CXX) $(CXXFLAGS) -o $(REST_CLIENT) restClient.cpp $(LDFLAGS)

$(PROTO_CLIENT): protoClient.cpp
	$(CXX) $(CXXFLAGS) -o $(PROTO_CLIENT) protoClient.cpp -ljsoncpp

clean:
	$(RM) -r $(TARGET) $(REST_CLIENT) $(PROTO_CLIENT) $(OBJS) a.out* *.dSYM .depend *.d .#* \#*


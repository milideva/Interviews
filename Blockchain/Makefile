CXX = g++ 
CXXFLAGS  = -std=c++2a -g
LDFLAGS = -L/usr/local/opt/openssl/lib -lcrypto -lssl -lcpprest -ljsoncpp

SRCS := $(shell find . -name "*.c++")
#OBJS := $(subst .c++,.o,$(SRCS))
OBJS := $(patsubst %.c++,%.o,$(SRCS))
DEPENDS := $(patsubst %.c++,%.d,$(SRCS))

# The build target 
TARGET = blockchain
REST_CLIENT = client

all: $(TARGET) $(REST_CLIENT)

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

clean:
	$(RM) -r $(TARGET) $(REST_CLIENT) $(OBJS) a.out* *.dSYM .depend *.d



#ifndef PROTO_COMMON_H
#define PROTO_COMMON_H
#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <json/json.h>

using namespace boost::asio;
using ip::tcp;
using namespace std;

// Discovery server port for protocol exchange
#define SERVER_PORT (1234)

// Max peers to send
#define N_PEERS (5)

// A sample protocol message for Discovery
typedef struct discoveryMessage discoveryStruct;
typedef unsigned short port_t;

struct discoveryMessage {
  int msgType;
  string serviceName;
  ip::address serviceAddr;
  port_t servicePort;
};

extern void asyncProtoServer (void);

#endif

#include "commonProto.h"

// Port on which this peer is offering a particular Service
#define MY_SERVICE_PORT 7777

// Serialize the message
static Json::Value getMessageInJSON (discoveryStruct *disc) {
  Json::Value root;
  if (!disc) return root;
  
  root["msgType"] = disc->msgType;
  root["serviceName"] = disc->serviceName;
  root["serviceAddr"] = disc->serviceAddr.to_string();
  root["servicePort"] = disc->servicePort;

  return root;
}

#include <random>
int getRandom () {

  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(25, 63); // define the range
  return distr(gen);
}

// Create a message and convert it into JSON and then serialize into a string to send over socket
static string createMessageStr (void) {
  
  discoveryStruct discMsg = {0};
  discMsg.msgType = 99;
  discMsg.serviceName = "Hello from Mars";
  discMsg.serviceAddr = ip::address::from_string("22.22.22.22"); // or get from socket.local_endpoint().address();
  discMsg.servicePort = MY_SERVICE_PORT + getRandom();

  Json::Value root = getMessageInJSON(&discMsg);
  Json::StreamWriterBuilder builder;
  string msg = Json::writeString(builder, root);

  return msg;
}

int main() {

  boost::asio::io_service io_service;
  tcp::socket socket(io_service);

  try {
    socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), SERVER_PORT ) );
  } catch (std::exception & e) {
    std::cerr << "Check server : " << e.what() << std::endl;
    return 1;
  }

  string msg = createMessageStr();
  boost::system::error_code error;
  
  boost::asio::write( socket, boost::asio::buffer(msg), error );

  if( !error ) {
    cout << "Client sent:" <<  msg << endl;
  }
  else {
    cout << "send failed: " << error.message() << endl;
  }

  boost::asio::streambuf receive_buffer;
  boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);

  if( error && error != boost::asio::error::eof ) {
    cout << "receive failed: " << error.message() << endl;
  } else {
    const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
    cout << "Client received response from Server:" << data << endl;
  }

  return 0;
}


#include "commonProto.h"
vector <pair<ip::address, port_t>> vPeers;

// Port on which this peer is offering a particular Service
#define MY_SERVICE_PORT (1111)

// Serialize a protocol message into json, a verbose serializer. 
// May want to move to Google protobuf or boost serializer Ar
static Json::Value getMessageInJSON (discoveryStruct *disc) {
  Json::Value root;
  if (!disc) return root;

  root["msgType"] = disc->msgType;
  root["serviceName"] = disc->serviceName;
  root["serviceAddr"] = disc->serviceAddr.to_string();
  root["servicePort"] = disc->servicePort;

  return root;
}

// Create a message and convert it into JSON and then serialize into a string to send over socket
static string createMessageStr (int index) {

  discoveryStruct discMsg = {0};
  discMsg.msgType = 99;
  discMsg.serviceName = "Hello from Earth";

  ip::address peerAddr = vPeers[index].first;
  port_t peerPort = vPeers[index].second;

  discMsg.serviceAddr = peerAddr;
  discMsg.servicePort = peerPort;

  Json::Value root = getMessageInJSON(&discMsg);
  Json::StreamWriterBuilder builder;
  string msg = Json::writeString(builder, root);

  return msg;
}

Json::Value sockInDataToJSON ( char* data, size_t bytes_transferred) {
  Json::Value root {};
  Json::CharReaderBuilder builder {};
  std::string errors {};
  
  auto reader = std::unique_ptr<Json::CharReader>( builder.newCharReader() );
  
  const auto is_parsed = reader->parse( data,
                                        data + bytes_transferred,
                                        &root,
                                        &errors );
  if ( !is_parsed ) {
    std::cerr << "ERROR: Could not parse! " << errors << '\n';
  }
  return root;
}

void deserializeMessage (Json::Value& root) {
  int msgType = root["msgType"].asInt();
  string serviceName = root["serviceName"].asString();
  
  string serviceAddr = root["serviceAddr"].asString();
  ip::address ipServiceAddr = ip::address::from_string(serviceAddr);
  string ipStr = ipServiceAddr.to_string();
  
  unsigned short servicePort = root["servicePort"].asInt();

  if (vPeers.size() > N_PEERS) {
    // Instead of deleting from front, we should keep first few seed nodes
    // Delete the old nodes that come after the seed nodes
    // Keep the latest nodes
    // Also need a check to see if the nodes are alive or not
    // Send a mix of seed nodes and random latest nodes
    // TO DO
    vPeers.erase(vPeers.begin());
  }
  cout << "Added newly discovered peer!" << endl << endl;

  // Ideally maintain a hash table to see that entries in peers are unique
  vPeers.push_back({ipServiceAddr, servicePort});
}

class con_handler : public boost::enable_shared_from_this<con_handler> {
private:
  tcp::socket sock;
  std::string messageToSend; 
  enum { max_length = 1024 };
  char data[max_length];
  ip::address _remoteAddress;
  unsigned short _remotePort;

public:
	
typedef boost::shared_ptr<con_handler> pointer;
  con_handler(boost::asio::io_context& io_context)
    : sock(io_context) {
  }

  static pointer create(boost::asio::io_context& io_context) {
    return pointer(new con_handler(io_context));
  }
  
  tcp::socket& socket() {
    return sock;
  }

  void start() {
    _remoteAddress = sock.remote_endpoint().address(); 
    _remotePort = sock.remote_endpoint().port();
    //cout << "Remote address:" << _remoteAddress.to_string() << " port:" << _remotePort << endl;
    //vPeers.push_back({_remoteAddress, _remotePort});
    sock.async_read_some(
                         boost::asio::buffer(data, max_length),
                         boost::bind(&con_handler::handle_read,
                                     shared_from_this(),
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));
    
    int max = N_PEERS < vPeers.size() ? N_PEERS : vPeers.size();

    for (int i = 0; i < max; i++) {
      messageToSend = createMessageStr(i);
      cout << "Sending Peer#" << i+1 << " Discovery info: " << endl;
      cout << messageToSend << endl;

      sock.async_write_some(
                            boost::asio::buffer(messageToSend, max_length),
                            boost::bind(&con_handler::handle_write, 
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
    }
  }
  
  void handle_read(const boost::system::error_code& err,
                   size_t bytes_transferred) {

    //cout << "read Remote address:" << _remoteAddress.to_string() << " port:" << _remotePort << endl;

    if (!err) {
      //cout << data << endl;
      Json::Value root = sockInDataToJSON(data, bytes_transferred);
      std::cout << endl << "Parsed JSON message from Peer: Deserialzing Discovery Message :" << root << endl << endl;
      deserializeMessage(root);

    } else {
      std::cerr << "err (recv): " << err.message() << std::endl;
      sock.close();
    }

  }

  void handle_write(const boost::system::error_code& err,
      		   size_t bytes_transferred) {
    if (!err) {
      //cout << "Server sent:" << messageToSend << endl;
    } else {
      std::cerr << "err (recv): " << err.message() << std::endl;
      sock.close();
    }
  }
};

class Server {

private:
  tcp::acceptor acceptor_;
  boost::asio::io_context& io_context_;

  void start_accept() {
    // creates a socket
    con_handler::pointer connection = con_handler::create(io_context_);
    
    // initiates an asynchronous accept operation 
    // to wait for a new connection. 
    acceptor_.async_accept(connection->socket(),
                           boost::bind(&Server::handle_accept, this, connection,
                                       boost::asio::placeholders::error));
  }
  
public:
  Server(boost::asio::io_context& io_context): io_context_(io_context),
                                               acceptor_(io_context, tcp::endpoint(tcp::v4(), SERVER_PORT)) { 

    cout << endl << "Starting Proto Server on port:" << SERVER_PORT << endl << endl;
    
    start_accept();
  }

  void handle_accept(con_handler::pointer connection,
                     const boost::system::error_code& err) {
    if (!err) {
      connection->start();
    }

    start_accept();
  }
};

void asyncProtoServer (void) {
  cout << endl << endl << "Launching asyncProtoServer for listening to discovery messages:" << endl;
  try {
    boost::asio::io_context io_context;   
    Server server(io_context);
    io_context.run();
  } catch(std::exception& e)  {
    std::cerr << e.what() << endl;
  }
}




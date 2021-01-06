#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#pragma comment(lib, "cpprest_2_10")
 
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
 
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

#include "blockchain.h"
#include "transaction.h"

#define TRACE(msg)            cout << msg
#define TRACE_ACTION(a, k, v) cout << a << " (" << k << ", " << v << ")\n"
 
map<utility::string_t, utility::string_t> dictionary;
 
void display_json (json::value const & jvalue, utility::string_t const & prefix) {
  cout << prefix << jvalue.serialize() << endl;
}
 
void handle_get (http_request request) {
  TRACE("\nhandle GET\n");
  
  auto answer = json::value::object(); 
  Json::Value ret = getBlockCountToJSON();
  string s = ret.toStyledString();

  answer["getBlockCount"] = json::value::string(s);

  display_json(json::value::null(), "Rx: ");
  display_json(answer, "Sent: ");
  
  request.reply(status_codes::OK, answer);
}
 
void handle_request (http_request request, function<void(json::value const &, json::value &)> action) {
  auto answer = json::value::object();
  
  request
    .extract_json()
    .then([&answer, &action](pplx::task<json::value> task) {
      try {
        auto const & jvalue = task.get();
        display_json(jvalue, "Rx: ");
        
        if (!jvalue.is_null()) {
          action(jvalue, answer);
        } else {
          cout << "POST null jvalue" << endl;
        }
      } catch (http_exception const & e) {
        cout << e.what() << endl;
      }
    })
    .wait();
   
   display_json(answer, "Sent: ");
 
   request.reply(status_codes::OK, answer);
}
 
void handle_post (http_request request) {
  TRACE("\nhandle POST\n");
  
  handle_request(request,
                 [](json::value const & jvalue, json::value & answer) {
                   cout << "POST rx" << jvalue << endl;
                   bool get = false;

                   try {
                     auto arr = jvalue.as_array();
                     string key = arr[0].as_string();
                     get = true;

                     if (key.compare("getBlock") == 0) {
                       cout << "key:" << key << endl; 
                       string indexStr = arr[1].as_string();
                       int index = stoul(indexStr, 0, 10);
                       cout << "index:" << index << endl;
                       
                       if (index < 0) {
                         answer["getBlock"] = json::value::string("<nil> Bad Param");
                       } else {
                         Json::Value ret = getBlockToJSON(index);
                         string s = ret.toStyledString();
                         answer["getBlock"] = json::value::string(s);
                       }
                     } 

                     else if (key.compare("getTransaction") == 0) {
                       string commandStr = "getTransaction";
                       cout << "key:" << key << endl; 
                       string bIndexStr = arr[1].as_string();
                       int bIndex = stoul(bIndexStr, 0, 10);
                     
                       string tIndexStr = arr[2].as_string();
                       int tIndex = stoul(tIndexStr, 0, 10);
                     
                       if (bIndex < 0 || tIndex < 0) {
                         answer[commandStr] = json::value::string("<nil> Bad Param");
                       } else {
                         Json::Value ret = getTransactionToJSON(bIndex, tIndex);
                         string s = ret.toStyledString();
                         answer[commandStr] =  json::value::string(s);
                       }
                     } 
                   } catch (exception const & e) { 
                     cout << e.what() << endl;
                     get = false;
                   }

                   if (get == false) {
                     string commandStr = "setTransaction";
                     string contextStr = jvalue.at("context").as_string();
                     cout << "contextStr:" << contextStr << endl;

                     string fromAddrStr = jvalue.at("fromAddr").as_string();
                     cout << "fromAddrStr:" << fromAddrStr << endl;

                     string rStr = jvalue.at("r").as_string();
                     cout << "rStr:" << rStr << endl;

                     string sStr = jvalue.at("s").as_string();
                     cout << "sStr:" << sStr << endl;
/*
  JSON CPP send sig as boolean as it does not support unsigned char pointer
                     string fromSigStr = jvalue.at("fromSig").as_string();
                     cout << "fromSigStr:" << fromSigStr << endl;

                     int sigLen = jvalue.at("sigLen").as_integer();
                     cout << "sigLen:" << sigLen << endl;
*/
                     int nValue = jvalue.at("nValue").as_integer();
                     cout << "nValue:" << nValue << endl;

                     int nonce = jvalue.at("nonce").as_integer();
                     cout << "nonce:" << nonce << endl;

                     string toAddrStr = jvalue.at("toAddr").as_string();
                     cout << "toAddrStr:" << toAddrStr << endl;

                     string txnHashStr = jvalue.at("txnHash").as_string();
                     cout << "txnHashStr:" << txnHashStr << endl;

                     createTransactionFromJSON(contextStr, fromAddrStr, rStr, sStr, 
                                               nValue, nonce, toAddrStr, txnHashStr);

                     answer[commandStr] = json::value::string(contextStr);
                   }
                   
                 });
}
 
void handle_put (http_request request) {
  TRACE("\nhandle PUT\n");
  
  handle_request(
                 request,
                 [](json::value const & jvalue, json::value & answer) {
                   for (auto const & e : jvalue.as_object()) {
                     if (e.second.is_string()) {
                       auto key = e.first;
                       auto value = e.second.as_string();
                       
                       if (dictionary.find(key) == dictionary.end()) {
                         TRACE_ACTION("added", key, value);
                         answer[key] = json::value::string("<put>");
                       } else {
                         TRACE_ACTION("updated", key, value);
                         answer[key] = json::value::string("<updated>");
                       }
                       
                       dictionary[key] = value;
                     }
                   }
                 });
}
 
void handle_del (http_request request) {
  TRACE("\nhandle DEL\n");
  
  handle_request( request,
                  [](json::value const & jvalue, json::value & answer) {
                    set<utility::string_t> keys;
                    for (auto const & e : jvalue.as_array()) {
                      if (e.is_string()) {
                        auto key = e.as_string();
                        
                        auto pos = dictionary.find(key);
                        if (pos == dictionary.end()) {
                          answer[key] = json::value::string("<failed>");
                        } else {
                          TRACE_ACTION("deleted", pos->first, pos->second);
                          answer[key] = json::value::string("<deleted>");
                          keys.insert(key);
                        }
                      }
                    }
                    
                    for (auto const & key : keys)
                      dictionary.erase(key);
                  });
}
 
#include "restServer.h"
#include "restCommonHeader.h"

void restServer (int id) {
  cout << "Starting restServerStr:" << restServerStr << endl;
  http_listener listener(restServerStr);

   listener.support(methods::GET,  handle_get);
   listener.support(methods::POST, handle_post);
   listener.support(methods::PUT,  handle_put);
   listener.support(methods::DEL,  handle_del);
 
   try {
     listener
       .open()
       .then([&listener]() {TRACE("\nstarting to listen\n"); })
       .wait();
     
     while (true);
   } catch (exception const & e) {
     cout << e.what() << endl;
   }
   
}

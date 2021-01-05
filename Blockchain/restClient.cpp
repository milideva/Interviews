#include <cpprest/http_client.h>
#include <cpprest/json.h>
#pragma comment(lib, "cpprest_2_10")
 
using namespace web;
using namespace web::http;
using namespace web::http::client;
 
#include <iostream>
using namespace std;
 
void display_json(
   json::value const & jvalue, 
   utility::string_t const & prefix)
{
   cout << prefix << jvalue.serialize() << endl;
}
 
pplx::task<http_response> make_task_request(
   http_client & client,
   method mtd,
   json::value const & jvalue)
{
   return (mtd == methods::GET || mtd == methods::HEAD) ?
      client.request(mtd, "/restdemo") :
      client.request(mtd, "/restdemo", jvalue);
}
 
void make_request(
   http_client & client, 
   method mtd, 
   json::value const & jvalue)
{
   make_task_request(client, mtd, jvalue)
      .then([](http_response response)
      {
         if (response.status_code() == status_codes::OK)
         {
            return response.extract_json();
         }
         return pplx::task_from_result(json::value());
      })
      .then([](pplx::task<json::value> previousTask)
      {
         try
         {
            display_json(previousTask.get(), "R: ");
         }
         catch (http_exception const & e)
         {
           cout << "Http exception" << endl;
            cout << e.what() << endl;
         }
      })
      .wait();
}

#include "restCommonHeader.h"
 
int main() {
  
  cout << "client connecting to restServerStr:" << restServerStr << endl;

  http_client client(U(restServerStr));

  auto nullvalue = json::value::null();
  cout << "\nGET\n";
  display_json(nullvalue, "Client sent GET: ");
  make_request(client, methods::GET, nullvalue);
  

  auto getvalue = json::value::array();
  getvalue[0] = json::value::string("getBlock");
  getvalue[1] = json::value::string("0");
  
  cout << "\nPOST getBlock \n";
  display_json(getvalue, "Client Sent POST getBlock: ");
  make_request(client, methods::POST, getvalue);

  getvalue[0] = json::value::string("getTransaction");
  getvalue[1] = json::value::string("1"); // block Index
  getvalue[2] = json::value::string("3"); // transaction Index

  cout << "\nPOST getTransaction\n";
  display_json(getvalue, "Client Sent POST getTransaction:");
  make_request(client, methods::POST, getvalue);
  
  return 0;
}

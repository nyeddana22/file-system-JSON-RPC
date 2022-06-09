

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw1server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// ecs251
#include "Core.h"
#include "Person.h"
#include "Transaction.h"
#include <time.h>

using namespace jsonrpc;
using namespace std;

class Myhw1Server : public hw1Server
{
public:
  Myhw1Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value GetDistance(const std::string& action, const std::string& arguments,
				 const std::string& class_id, const std::string& host_url,
				 const std::string& object_id, const std::string& owner_vsID);

  virtual Json::Value Conflict_of_Interest(const std::string& action, const std::string& arguments,
         const std::string& class_id, const std::string& host_url,
         const std::string& object_id, const std::string& owner_vsID);
  
  virtual Json::Value GetVsID(const std::string& action, const std::string& arguments,
         const std::string& class_id, const std::string& host_url,
         const std::string& object_id, const std::string& owner_vsID);

  virtual Json::Value OperatorEqEq(const std::string& aPerson_class_id, const std::string& aPerson_host_url, const std::string& aPerson_object_id, 
         const std::string& aPerson_owner_vsID, const std::string& action, const std::string& arguments,
         const std::string& class_id, const std::string& host_url,
         const std::string& object_id, const std::string& owner_vsID);

  virtual Json::Value getName(const std::string& action, const std::string& arguments,
         const std::string& class_id, const std::string& host_url,
         const std::string& object_id, const std::string& owner_vsID);
};

Myhw1Server::Myhw1Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw1Server(connector, type)
{
  std::cout << "Myhw1Server Object created" << std::endl;
}

Person *person1;
Person *person2;
Person *person3;
Flight *f3;

// member function
Json::Value
Myhw1Server::GetDistance
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  double d;
  if ((class_id != "Flight") || ((object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000003")
	d = f3->getDistance();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"distance\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}

Json::Value
Myhw1Server::Conflict_of_Interest
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  double d;
  if ((class_id != "Flight") ||  (object_id != "00000003"))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
  strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
  strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000003")
  d = f3->Conflict_of_Interest();
  //     else
  // d = f3->Conflict_of_Interest();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"COI\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}

Json::Value
Myhw1Server::GetVsID
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  std::string d;
  if ((class_id != "Person") || (object_id != "00000007"))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Person")
  strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
  strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000007")
  d = person3->getVsID();
  //     else if (object_id == "00000006")
  // d = p2->getVsID();
  //     else if (object_id == "00000007")
  // d = sp3->getVsID();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"VS_ID\": " + d + "}");
    }
      Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}

Json::Value
Myhw1Server::getName
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  std::string d;
  if ((class_id != "Person") || (object_id != "00000007"))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Person")
  strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
  strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000007")
  d = person3->getName();
  //     else if (object_id == "00000006")
  // d = p2->getVsID();
  //     else if (object_id == "00000007")
  // d = sp3->getVsID();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"get_name\": \"" + d + "\"}");
      cout<<"Value of d: "<<d<<"JSON: "<<strJson<<endl;
    }
      Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}

Json::Value
Myhw1Server::OperatorEqEq
(const std::string& aPerson_class_id, const std::string& aPerson_host_url, const std::string& aPerson_object_id, 
 const std::string& aPerson_owner_vsID, const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;
  bool d;
  if ((class_id != "Person") || ((object_id != "00000005") && (object_id != "00000006") && (object_id != "00000007")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Person")
  strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
  strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if ((object_id == "00000005") && (aPerson_object_id == "00000006")) d = (*person1 == *person2);
      else if ((object_id == "00000005") && (aPerson_object_id == "00000007")) d = (*person1 == *person3);
      else if ((object_id == "00000005") && (aPerson_object_id == "00000005")) d = (*person1 == *person1);
      else if ((object_id == "00000006") && (aPerson_object_id == "00000005")) d = (*person2 == *person1);
      else if ((object_id == "00000006") && (aPerson_object_id == "00000007")) d = (*person2 == *person3);
      else if ((object_id == "00000006") && (aPerson_object_id == "00000006")) d = (*person2 == *person2);
      else if ((object_id == "00000007") && (aPerson_object_id == "00000005")) d = (*person3 == *person1);
      else if ((object_id == "00000007") && (aPerson_object_id == "00000006")) d = (*person3 == *person2);
      else if ((object_id == "00000007") && (aPerson_object_id == "00000007")) d = (*person3 == *person3);

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"OpEq\": " + to_string(d) + "}");
    }

      Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}
// another

int main() {

  Airline United;
  GPS_DD gps_Davis {38.5, -121.7};
  GPS_DD gps_NYC {40.7, -73.95};
  GPS_DD gps_Sydney {-33.87, 151.213};
  IP_Address IP_Davis {12345678};
  IP_Address IP_Sydney {12345678};
  IP_Address IP_NYC {12375678};

  Person p1 {"Lion King", "123456789123456789"};
  Person p2 {"Lion Queen", "223456789123456789"};

  Flight flight_three {"http://169.237.6.102", "1234567890", "Flight", "00000003",
      TR_TYPE_FLIGHT, "desc", p1, gps_Davis, IP_Davis, time(NULL),
      p1, United, "9999999999", gps_NYC, gps_Sydney};

  Person person_one {"http://127.0.0.1:8384", "1234567890", "Person", "00000005", "Lion King", "123456789123456789"};
  Person person_two {"http://localhost:8384", "1234567890", "Person", "00000006", "Lion Queen", "223456789123456789"};
  Person person_three {"http://localhost:8385", "1234567890", "Person", "00000007","Lion Child", "323456789123456789"};

  person1 = (&person_one);
  person2 = (&person_two);
  person3 = (&person_three);
  f3 = (&flight_three);

  HttpServer httpserver(8385);
  Myhw1Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the another" << endl;
  getchar();

  s.StopListening();
  return 0;
}


#ifndef _SHADOW_PERSON_H_
#define _SHADOW_PERSON_H_

#include "Transaction.h"

class Shadow_Person: public Person
{
 private:
 public:
  Shadow_Person(std::string, std::string, std::string, std::string);
  virtual std::string getVsID();
  virtual std::string getName();
  virtual bool operator== (Person& aPerson);
};

#endif // _SHADOW_PERSON_H_

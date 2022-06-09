
// ecs251 first program

#include <iostream>
#include "Shadow_Flight.h"
#include "Shadow_Person.h"

using namespace std;

int
main()
{

  cout<<"\n\n~~~~~~    getDistance() Function Implementation   ~~~~~~\n\n\n";

  Shadow_Flight sf3 { "http://localhost:8384", "1234567890", "Flight", "00000003" };
  std::cout << std::to_string(((Flight&) sf3).getDistance()) << std::endl;

  Shadow_Flight sf2 { "http://localhost:8384", "1234567890", "Flight", "00000002" };
  std::cout << std::to_string(sf2.getDistance()) << std::endl;

  Shadow_Flight sf1 { "http://localhost:8384", "1234567890", "Flight", "00000001" };
  std::cout << std::to_string(sf1.getDistance()) << std::endl;

  cout<<"\n\n~~~~~~    Conflict_of_Interest() Function Implementation   ~~~~~~\n\n\n";
  
  if (sf1.Conflict_of_Interest()) printf("sf1 coi\n");
  if (sf2.Conflict_of_Interest()) printf("sf2 coi\n");
  if (sf3.Conflict_of_Interest()) printf("sf3 coi\n");

  cout<<"\n\n~~~~~~    getVsID() Function Implementation   ~~~~~~\n\n\n";

  Shadow_Person sp1 { "http://127.0.0.1:8384", "1234567890", "Person", "00000005" };
  std::cout << ((Person&) sp1).getVsID() << std::endl;
  // std::cout << sp1.getVsID() << std::endl;
  // std::cout << ((Person&) sp1).getName() << std::endl;

  Shadow_Person sp2 { "http://localhost:8384", "1234567890", "Person", "00000006" };
  std::cout << ((Person&) sp2).getVsID() << std::endl;
  // std::cout << ((Person&) sp2).getName() << std::endl;

  Shadow_Person sp3 { "http://localhost:8384", "1234567890", "Person", "00000007" };
  std::cout << ((Person&) sp3).getVsID() << std::endl;
  // std::cout << ((Person&) sp2).getName() << std::endl;

  cout<<"\n\n~~~~~~    OperatorEqEq() Function Implementation   ~~~~~~\n\n\n";

  if (sp1 == sp2) printf("They are equal\n");
  if (sp2 == sp3) printf("They are equal\n");
  if (sp1 == sp1) printf("They are equal\n");

  // Shadow_Person sp_another { "http://localhost:8385", "1234567890", "Person", "00005555" };
  // std::cout << ((Person&) sp_another).getVsID() << std::endl;

  // Person, Shadow_Person
  // Person *p1_ptr = (Person *) (&sp1);

  // Person *p1_ptr = (Person *) ((Shadow_Person *) &sp1);
  // void *gen_ptr_1 = (void *) (&sp1);
  // void *gen_ptr_2 = (void *) ((Person *) (&sp1));

  return 0;
}

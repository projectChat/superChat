#include <iostream>
#include <SuperChat.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
   long long int id1, id2;
   char user1[8] = "jason";
   char user2[8] = "jacob";
   char room1[25] = "team3";
   char message1[144] = "message show";

   //test room
   test_room(room1);
   if(strcmp(room1, get_room()) == 0)
   {
	cout << "room test succeed\n";
   }
   else
   {
	cout << "room test failed\n";
   }

   //test username
   test_user(user1);
   if(strcmp(user1, get_user()) == 0)
   {
	cout << "username test succeed\n";
   }
   else
   {
	cout << "username test failed\n";
   }

   id1 = get_uuid();

   test_user(user2);
   id2 = get_uuid();

   //test uuid
   if(id1 == id2)
   {
	cout << "uuid test failed\n";
   }
   else
   {
	cout << "uuid test succeed\n";
   }

   //test message
   test_message(message1);
   if(strcmp(message1, get_message()) == 0)
   {
	cout << "message test succeed\n";
   }
   else
   {
	cout << "message test failed\n";
   }

   return 0;
}



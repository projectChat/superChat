#include <signal.h>
#include <assert.h>
#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <pthread.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <SuperChat.h>
#include "DDSEntityManager.h"
#include "ccpp_SuperChat.h"

// This code is derived from the PrismTech HelloWorld examples


using namespace DDS;
using namespace SuperChat;
using namespace std;

// these classes abstract out the sending and recieving of topics
// perhaps with some cleverness, generics could be used to eliminate
// some of the code 

typedef std::vector<chatroom> chatroom_list_t;

class chatroom_data
{
  private:
  DDSEntityManager em;
  chatroomDataWriter_var Writer;
  chatroomDataReader_var Reader;
  public:
  void send ( chatroom messageInstance )
  {
     ReturnCode_t status = Writer->write(messageInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( chatroom_list_t* chatroomList )
  {
     // if any data is available, it returns a list
     assert ( chatroomList );
     chatroomSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       chatroomList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  chatroom_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    chatroomTypeSupport_var T = new chatroomTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = chatroomDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = chatroomDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~chatroom_data ()
  {
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};

typedef std::vector<message> message_list_t;

class message_data
{
  private:
  DDSEntityManager em;
  messageDataWriter_var Writer;
  messageDataReader_var Reader;
  public:
  void send ( message messageInstance )
  {
     ReturnCode_t status = Writer->write(messageInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( message_list_t* messageList )
  {
     // if any data is available, it returns a list
     assert ( messageList );
     messageSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       messageList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  message_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    messageTypeSupport_var T = new messageTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = messageDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = messageDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~message_data ()
  {
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};

typedef std::vector<user> user_list_t;

class user_data
{
  private:
  DDSEntityManager em;
  userDataWriter_var Writer;
  userDataReader_var Reader;
  public:
  void send ( user userInstance )
  {
     ReturnCode_t status = Writer->write(userInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( user_list_t* userList )
  {
     // if any data is available, it returns a list
     assert ( userList );
     userSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       userList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  user_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    userTypeSupport_var T = new userTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = userDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = userDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~user_data ()
  {
std::cout << "deconstructor" << '\n';
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};
///////////////////////////////////////////////////////////////////////////////
bool exit_flag = false;

void ctrlc ( int )
{
   exit_flag = true;
}
///////////////////////////////////////////////////////////////////////////////

chatroom_data chatRoom ( (char*) "chatroom" );
user_data User ( (char*) "user" );
message_data Message ( (char*) "msg" );
message_list_t  message_List;
chatroom_list_t  room_List;
user_list_t  user_List;
int sig;
char str_user[8];
int open_window2 = 0;//use to check if it's the first time to open window or not
int open_window3 = 0;
int show_msg1 = 1; //show message for window 2
int show_msg2 = 22;

void window1(long long int &);
void window2(long long int);
void window3(long long int);
void *show_message(void *ptr);
void *get_message(void *t);
void *show_message1(void *ptr);
void *get_message1(void *t);

//these functions use for unit test
void test_room(char roomName[25])
char *get_room()
void test_user(char nick[8]);
char *get_user();
void test_message(char chat[144]);
char *get_message();
long long int get_uuid();

int main()
{ 
   // set up ctrl-c handler
   signal ( SIGINT, ctrlc );  
   
   //create UUID for user tp pass over window 1 and 2
   long long int myUUID;
   //get username from window1
   window1(myUUID);  

   //use to switch from window 2 to window 3 and vice versa
   while(1)
   {
      sig = 0;
      if(sig == 0)
      {
        window2(myUUID);    
      }

      if(sig == 1)
      {
         window3(myUUID);
      }
   }
   //end window
   endwin();
   return 0;
}

//this function use to get username
void window1(long long int &myUUID)
{
  user user_info;
  user_info.chatroom_idx = 1;
  
  WINDOW *my_wins[3];
  PANEL  *my_panels[3];
  int lines = 25, cols = 110, y = 2, x = 4, i;

  initscr();
  cbreak();
  echo();
  start_color();

  //Initialize all the colors 
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

  // Create windows for the panels 
  //              (lines, cols, y, x);
  my_wins[0] = newwin(25, 110, y, x);
  my_wins[1] = newwin(3, 20, 14, 49);
  my_wins[2] = newwin(25, 110, y, x);

   
  // * Create borders around the windows so that you can see the effect
   //* of panels
   
  for(i = 0; i < 2; ++i)
    box(my_wins[i], 0, 0);

  // Attach a panel to each window  
  my_panels[0] = new_panel(my_wins[0]);   
  my_panels[1] = new_panel(my_wins[1]);   
  //my_panels[2] = new_panel(my_wins[2]);   

  // Update the stacking order. 2nd panel will be on top
  update_panels();

  // Show it on the screen
  doupdate();

  // turn on color
  
  attron(COLOR_PAIR(4));
  attron(A_BOLD);
  mvprintw(5, 55, "SuperChat");
  attroff(A_BOLD);
  attroff(COLOR_PAIR(4)); // turn off color
  
  attron(COLOR_PAIR(2));
  mvprintw(13, 55, "Username");
  attroff(COLOR_PAIR(2));

  //unique uuid will be created by boost uuid
  boost::uuids::uuid uuid = boost::uuids::random_generator()();
  memcpy ( &myUUID, &uuid, sizeof (myUUID) );
  // Enter username here at this location
  
  user_info.uuid = myUUID;
  //get input from user
  mvgetstr(15,50, str_user);
  strncpy(user_info.nick, str_user, sizeof(user_info.nick));
  User.send(user_info);
} 

void window2(long long int myUUID)
{ 
  //int lines = 25, cols = 110, y = 1, x = 4, i;
  int i;
  char str_msg[144];
  
  if(open_window2 == 0)
  {
    WINDOW *my_wins[4];
    PANEL  *my_panels[4];
    initscr();
    cbreak();
    echo();
    start_color(); // type this first in order to use color;

    // Initialize all the colors
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    // Create windows for the panels
    //              (lines, cols, y, x);
  
    my_wins[0] = newwin(20, 70, 0 ,0); // public chat window
    my_wins[1] = newwin(3, 48, 16, 1); // enter text window
    my_wins[2] = newwin(9, 19.5, 1, 50); // chat room window
    my_wins[3] = newwin(9, 19.5, 10, 50); // user window
  

     
    // Create borders around the windows so that you can see the effect
    //  of panels
     
    for(i = 0; i < 4; ++i) 
    {
      wattron(my_wins[i],COLOR_PAIR(1)); //turn on window border color = yellow
      box(my_wins[i], 0, 0);
      wattroff(my_wins[i],COLOR_PAIR(1)); // turn off color
    }

    // Attach a panel to each window 
  
    my_panels[0] = new_panel(my_wins[0]); // chat window
    my_panels[1] = new_panel(my_wins[1]); // enter text window
    my_panels[2] = new_panel(my_wins[2]); // chat room window
    my_panels[3] = new_panel(my_wins[3]); // user window

    // Update the stacking order. 2nd panel will be on top
    update_panels();

    // Show it on the screen
    doupdate();

    mvprintw(2, 55, "Chat Room"); // print text "Chat Room" at this location
    mvprintw(11, 57, "Users"); // print text "Users" at this location

    // Enter puclic chat text here at this location inside panel[2]
    mvprintw(17, 2, "Msg>");

    //create chatroom
    chatroom chatroom_info;
    chatroom_info.chatroom_idx = 1;
    strcpy(chatroom_info.chatroom_name, "Room1");
    chatRoom.send(chatroom_info);
    chatRoom.recv ( &room_List ); 
    mvprintw(4, 52, chatroom_info.chatroom_name);

    open_window2++;
  }
  
  mvprintw(2, 55, "Chat Room"); // print text "Chat Room" at this location
  mvprintw(11, 57, "Users"); // print text "Users" at this location

  // Enter puclic chat text here at this location inside panel[2]
  mvprintw(17, 2, "Msg>");

  //use to pthread: 1 for getting message and another for showing message
  pthread_t thread1, thread2;

  //pthead to print out chat message
  if(pthread_create(&thread1, NULL, show_message, NULL))
  {
    perror("Error creating thread1: ");
    exit(EXIT_FAILURE);
  }
  
  //pthead to send message to database
  long long int t = myUUID;
  if(pthread_create(&thread2, NULL, get_message,(void *) t))
  {
    perror("Error creating thread2: ");
    exit(EXIT_FAILURE);
  }
  
  //join message
  if(pthread_join(thread1, NULL))
  {
    perror("Problem with pthread_join: ");
  }
  
  if(pthread_join(thread2, NULL))
  {
    perror("Problem with pthread_join: ");
  }
  //refresh();
  //getch();
  //endwin();
  
}

void window3(long long int myUUID)
{ 
  int i;
  char str_msg[144];
  
  if(open_window3 == 0)
  {
    WINDOW *my_wins[4];
    PANEL  *my_panels[4];
    initscr();
    cbreak();
    echo();
    start_color(); // type this first in order to use color;

    // Initialize all the colors
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    // Create windows for the panels
    //              (lines, cols, y, x);
  
    my_wins[0] = newwin(18, 70, 21 ,0); // public chat window
    my_wins[1] = newwin(3, 48, 35, 1); // enter text window
    my_wins[2] = newwin(7, 19.5, 22, 50); // chat room window
    my_wins[3] = newwin(9, 19.5, 29, 50); // user window
  

     
    // Create borders around the windows so that you can see the effect
    //  of panels
     
    for(i = 0; i < 4; ++i) {
      wattron(my_wins[i],COLOR_PAIR(1)); //turn on window border color = yellow
      box(my_wins[i], 0, 0);
      wattroff(my_wins[i],COLOR_PAIR(1)); // turn off color
    }

    // Attach a panel to each window 
  
    my_panels[0] = new_panel(my_wins[0]); // chat window
    my_panels[1] = new_panel(my_wins[1]); // enter text window
    my_panels[2] = new_panel(my_wins[2]); // chat room window
    my_panels[3] = new_panel(my_wins[3]); // user window

    // Update the stacking order. 2nd panel will be on top
    update_panels();

    // Show it on the screen
    doupdate();
    
    mvprintw(23, 55, "Chat Room"); // print text "Chat Room" at this location
    mvprintw(30, 57, "Users"); // print text "Users" at this location

    // Enter puclic chat text here at this location inside panel[2]
    mvprintw(36, 2, "Msg>");
    
    //create chatroom
    chatroom chatroom_info;
    chatroom_info.chatroom_idx = 2;
    strcpy(chatroom_info.chatroom_name, "Room2");
    chatRoom.send(chatroom_info);
    chatRoom.recv ( &room_List ); 
    mvprintw(25, 52, chatroom_info.chatroom_name);

    //create user
    user user_info;
    user_info.chatroom_idx = 2;
    user_info.uuid = myUUID;
    strncpy(user_info.nick, str_user, sizeof(user_info.nick));
    User.send(user_info);

    open_window3++;
  }
  
  mvprintw(23, 55, "Chat Room"); // print text "Chat Room" at this location
  mvprintw(30, 57, "Users"); // print text "Users" at this location

  // Enter puclic chat text here at this location inside panel[2]
  mvprintw(36, 2, "Msg>");
    
  //use to pthread: 1 for getting message and another for showing message
  pthread_t thread3, thread4;
  //pthead to print out chat message
  if(pthread_create(&thread3, NULL, show_message1, NULL))
  {
    perror("Error creating thread3: ");
    exit(EXIT_FAILURE);
  }
  
  //pthead to send message to database
  long long int t = myUUID;
  if(pthread_create(&thread4, NULL, get_message1,(void *) t))
  {
    perror("Error creating thread4: ");
    exit(EXIT_FAILURE);
  }
  
  if(pthread_join(thread3, NULL))
  {
    perror("Problem with pthread_join: ");
  }
  
  if(pthread_join(thread4, NULL))
  {
    perror("Problem with pthread_join: ");
  }
  //refresh();
  //getch();
  //endwin();
  
}

void *get_message(void *t)
{
  char str_msg[144];

  //run forever until user want to exit
  while(1)
  {     
    //get message from user
    mvgetstr(17,6, str_msg);

    //use to switch to another room
    if(strcmp(str_msg, "/q") == 0 )
    {
       sig = 1;
       //clear out the entered message to prepare for new one
       mvprintw(17,6, "                                         ");
       //move cursor to position of message input
       mvprintw(36,6, "");
       break;
    }

    //use to change name of room and store info of new one
    if(strncmp(str_msg, "/room:", 6) == 0)
    {
      chatroom chatroom_info;
      chatroom_info.chatroom_idx = 1;
      //get new name after colon, position 6
      strncpy(chatroom_info.chatroom_name, str_msg + 6, sizeof(chatroom_info.chatroom_name));
      chatRoom.send(chatroom_info);
      //clear out the message at message input
      mvprintw(17,6, "                                         ");
      continue;  
    }

    //use to change username adn store new one
    if(strncmp(str_msg, "/name:", 6) == 0)
    {
       user user_info;
       user_info.chatroom_idx = 1;
       //the new username have the same uuid
       user_info.uuid = (unsigned long) t; 
       //get new name after colon, position 6
       strncpy(user_info.nick, str_msg + 6, sizeof(user_info.nick)); 
       User.send(user_info);
       //clear out the message at message input
       mvprintw(17,6, "                                         ");
       continue; 
    }

    //use to store new message
    message message_info; 
    message_info.cksum = 0;
    message_info.uuid = (unsigned long) t; 
    message_info.chatroom_idx = 1;    
    strncpy(message_info.message, str_msg, sizeof(message_info.message));
    mvprintw(17,6, "                                         ");
    
    Message.send(message_info);
  }
}

void *get_message1(void *t)
{
  char str_msg[144];

  //run forever until user want to exit
  while(1)
  {     
    //get message from user
    mvgetstr(36,6, str_msg);

    //use to switch to another room
    if(strcmp(str_msg, "/q") == 0 )
    {
       sig = 0;
       //clear out the entered message to prepare for new one
       mvprintw(36,6, "                                         ");
       //move cursor to position of message input
       mvprintw(17,6, "");
       break;
    }

    //use to change name of room and store info of new one
    if(strncmp(str_msg, "/room:", 6) == 0)
    {
       chatroom chatroom_info;
       chatroom_info.chatroom_idx = 2;
       //get new name after colon, position 6
       strncpy(chatroom_info.chatroom_name, str_msg + 6, sizeof(chatroom_info.chatroom_name));
       chatRoom.send(chatroom_info);
       //clear out the message at message input
       mvprintw(36,6, "                                         ");
       
       continue;  
    }

    //use to change username adn store new one
    if(strncmp(str_msg, "/name:", 6) == 0)
    {
       user user_info;
       user_info.chatroom_idx = 2;
       //the new username have the same uuid
       user_info.uuid = (unsigned long) t; 
       //get new name after colon, position 6
       strncpy(user_info.nick, str_msg + 6, sizeof(user_info.nick)); 
       User.send(user_info);
       //clear out the message at message input
       mvprintw(36,6, "                                         ");
       
       continue; 
    }

    //use to store new message
    message message_info; 
    message_info.cksum = 0;
    message_info.uuid = (unsigned long) t; 
    message_info.chatroom_idx = 2;    
    strncpy(message_info.message, str_msg, sizeof(message_info.message));
    mvprintw(36,6, "                                         ");
    
    Message.send(message_info);
    
  }
}

void *show_message(void *ptr)
{
  //these use to compare previous vector size of message, user, room and current size
  //to check there is a new one added or not
  //if yes, it will show the new one 
  int count_message = 0;
  int count_user = 0;
  int count_room = 0;
  
  //use these variable to run if full of message in room
  int second_run = 0;
  //check if there are same username or not
  int duplicate_user;

  //run forever until user want to exit
  while(1)
  {
      sleep(0.1);
      //receive message, user and room information from domain
      Message.recv ( &message_List );
      User.recv (&user_List);
      chatRoom.recv(&room_List);
    
    //check to switch to another room
    if(sig == 1)
    {
       break;
    }

    //clear out line when chat message is full
    if(show_msg1 == 15)
    {
      show_msg1 = 1;
      int new_show_msg;
      //clear out all line
      for(new_show_msg = 1; new_show_msg < 16; new_show_msg++)
      {
        mvprintw(new_show_msg,2, "                           ");
      }       
          second_run ++;
    }
    
    //check to see there is new room name added or not
    if(count_room != room_List.size())
    {
       //clear out old name of room
       mvprintw(4, 52, "          ");
       //check to find a right room
       for(unsigned int i = room_List.size(); i > 0; i--)
       {
          if(room_List[i-1].chatroom_idx == 1)
          {
            mvprintw(4, 52, "%s", room_List[i-1].chatroom_name);
            break;
          }
       }
       //move cursor to input position
       mvprintw(17,6, "");
    }

    //check to see there is new username or not
    if(count_user != user_List.size())
    {
      //the position to show name
      int show_user = 13;

      //begin at the top of vector of username
      for(int i = user_List.size()-1; i >= 0 ; i--)
      {
         //check for changed name
         duplicate_user = 0;
         for(int j = i + 1; j < user_List.size(); j++ )
         {
            if(user_List[i].uuid == user_List[j].uuid && user_List[i].chatroom_idx == 1 && user_List[j].chatroom_idx == 1)
            {
               //go out if duplicate user uuid
               duplicate_user = 1;
               break;
            }
         }

         //show the new name
         if(duplicate_user == 0 && user_List[i].chatroom_idx == 1)
         {
            mvprintw(show_user, 51,"%s", user_List[i].nick);
            show_user++;
         }
      }
      
      mvprintw(17,6, "");
    }

    //use to check if there is new message in the database
    if(count_message != message_List.size())
    {
        unsigned int i= message_List.size() - 1;
        
        //check for uuid to show right message for right user
        for(unsigned int j = 0; j < user_List.size(); j++)
        {
          if(user_List[j].uuid == message_List[i].uuid && message_List[i].chatroom_idx == 1 && user_List[j].chatroom_idx == 1)
          {
             mvprintw(show_msg1, 2,"%s: %s", user_List[j].nick, message_List[i].message);
             mvprintw(17,6, "");
          }
        }
        show_msg1++;
      
    }
    //get current size of message, user, room
    count_room = room_List.size();
    count_message = message_List.size();
    count_user = user_List.size();
  }
}

void *show_message1(void *ptr)
{
  //these use to compare previous vector size of message, user, room and current size
  //to check there is a new one added or not
  //if yes, it will show the new one 
  int count_message = 0;
  int count_user = 0;
  int count_room = 0;
  
  //use these variable to run if full of message in room
  int second_run = 0;
  //check if there are same username or not
  int duplicate_user;

  //run forever until user want to exit
  while(1)
  {
      sleep(0.1);
      //receive message, user and room information from domain
      Message.recv ( &message_List );
      User.recv (&user_List);
      chatRoom.recv(&room_List);

      //check to switch to another room
      if(sig == 0)
      {
         break;
      }

      //clear out line when chat message is a lot
      if(show_msg2 == 34)
      {
        show_msg2 = 22;
        int new_show_msg;
        //clear out all line
        for(new_show_msg = 22; new_show_msg < 35; new_show_msg++)
        {
          mvprintw(new_show_msg,2, "                           ");
        }       
        second_run ++;
      }
      
      //check to see there is new room name added or not
      if(count_room != room_List.size())
      {
         //clear out old name of room
         mvprintw(25, 52, "          ");
         //check to find a right room
         for(unsigned int i = room_List.size(); i > 0; i--)
         {
            if(room_List[i-1].chatroom_idx == 2)
            {
               mvprintw(25, 52, "%s", room_List[i-1].chatroom_name);
               break;
            }
         }
         //move cursor to input position
         mvprintw(36,6, "");
      }

      //check to see there is new username or not
      if(count_user != user_List.size())
      {
        //the position to show name
        int show_user = 32;

        //begin at the top of vector of username
        for(int i = user_List.size()-1; i >= 0 ; i--)
        {
           //check for changed name
           duplicate_user = 0;
           for(int j = i + 1; j < user_List.size(); j++ )
           {
              if(user_List[i].uuid == user_List[j].uuid && user_List[i].chatroom_idx == 2 && user_List[j].chatroom_idx == 2)
              {
                 //go out if duplicate user uuid
                 duplicate_user = 1;
                 break;
              }
           }

           //show the new name
           if(duplicate_user == 0 && user_List[i].chatroom_idx == 2)
           {
              mvprintw(show_user, 51,"%s", user_List[i].nick);
              show_user++;
           }
        }
        
        mvprintw(36,6, "");
      }

      //use to check if there is new message in the database
      if(count_message != message_List.size())
      {
          unsigned int i= message_List.size() - 1;
        
          //check for uuid to show right message for right user
          for(unsigned int j = 0; j < user_List.size(); j++)
          {
            if(user_List[j].uuid == message_List[i].uuid && message_List[i].chatroom_idx == 2 && user_List[j].chatroom_idx == 2)
            {
               mvprintw(show_msg2, 2,"%s: %s", user_List[j].nick, message_List[i].message);
               mvprintw(36,6, "");
            }
          }
          show_msg2++;
        
      }
      //get current size of message, user, room
      count_room = room_List.size();
      count_message = message_List.size();
      count_user = user_List.size();
  }
}

//unit test for room
void test_room(char roomName[25])
{
   chatroom chatroom_info;
   chatroom_info.chatroom_idx = 1;
   strncpy(chatroom_info.chatroom_name, roomName, sizeof(chatroom_info.chatroom_name));
   chatRoom.send(chatroom_info);  
}

char *get_room()
{
   char roomName[25];
   chatRoom.recv ( &room_List );
   int i = room_List.size() - 1;
   strcpy(roomName, room_List[i].chatroom_name);
   return roomName;
}
  
//unit test for user
void test_user(char nick[8])
{
   user user_info;
   user_info.chatroom_idx = 1;
   user_info.uuid = 1;
   strncpy(user_info.nick, nick, sizeof(user_info.nick));
   User.send(user_info);
}

char *get_user()
{
   char user[8];
   User.recv (&user_List);
   int i = user_List.size()-1;
   strcpy(user, user_List[i].nick);
   return user;
}

long long int get_uuid()
{
   long long int myUUID;
   User.recv (&user_List);
   int i = user_List.size()-1;
   myUUID = user_List[i].uuid;
   return myUUID;
}

//unit test for message
void test_message(char chat[144])
{
   message message_info;  
   message_info.cksum = 0;
   message_info.uuid = 11; 
   message_info.chatroom_idx = 1;   
   strncpy(message_info.message, chat, sizeof(message_info.message));
   Message.send(message_info);
}

char *get_message()
{
   char chat[144];
   Message.recv ( &message_List );
   int i = message_List.size() - 1;
   strcpy(chat, message_List[i].message);
   return chat;
}
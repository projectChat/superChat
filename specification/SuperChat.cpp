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
//#include <boost/uuid/uuid.hpp>
//#include <boost/uuid/uuid_generators.hpp>
//#include <boost/uuid/uuid_io.hpp>

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


void window1(unsigned int &);
void window2(unsigned int, chatroom &);
void *show_message(void *ptr);
void *get_message(void *t);

int main()
{	
   // set up ctrl-c handler
   signal ( SIGINT, ctrlc );	
   //create chatroom
   chatroom chatroom_info;
   chatroom_info.chatroom_idx = 1;
   strcpy(chatroom_info.chatroom_name, "Thach");
   chatRoom.send(chatroom_info);

   //create new user
   
   unsigned int uuid;
   window1(uuid);
   	
   
   window2(uuid, chatroom_info);
	
   endwin();
   return 0;
}

void window1(unsigned int &uuid)
{
	user user_info;
	//user_info.uuid = rand()/100 + 1;
	user_info.chatroom_idx = 1;
 	uuid = user_info.uuid;
	
	WINDOW *my_wins[3];
	PANEL  *my_panels[3];
	int lines = 25, cols = 110, y = 2, x = 4, i;
	char str_user[8];

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
-
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


	// Enter username here at this location
	//mvprintw(15,55 ,"Enter the text here:");
	char *ptr;
	char value_id[5];
	mvgetstr(10,50, value_id);
	user_info.uuid = strtol(value_id, &ptr, 10);
	uuid = user_info.uuid;
	mvgetstr(15,50, str_user);
	strncpy(user_info.nick, str_user, sizeof(user_info.nick));
	User.send(user_info);
}

message_list_t  message_List;
chatroom_list_t  room_List;
user_list_t  user_List;	

void window2(unsigned int uuid, chatroom &chatroom_info)
{	
	WINDOW *my_wins[4];
	PANEL  *my_panels[4];
	//int lines = 25, cols = 110, y = 1, x = 4, i;
	int i;
	char str_msg[144];
	

	initscr();
	cbreak();
	echo();
	start_color(); // type this first in order to use color;

	// Initialize all the colors
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);

	// Create windows for the panels
	//              (lines, cols, y, x);
	//my_wins[0] = newwin(34, 109, y, x); // layout window
	my_wins[0] = newwin(20, 70, 0 ,0); // public chat window
	my_wins[1] = newwin(3, 48, 16, 1); // enter text window
	my_wins[2] = newwin(9, 19.5, 1, 50); // chat room window
	my_wins[3] = newwin(9, 19.5, 10, 50); // user window
	

	 
	// Create borders around the windows so that you can see the effect
	//  of panels
	 
	for(i = 0; i < 4; ++i) {
		wattron(my_wins[i],COLOR_PAIR(1)); //turn on window border color = yellow
		box(my_wins[i], 0, 0);
		wattroff(my_wins[i],COLOR_PAIR(1)); // turn off color
	}

	// Attach a panel to each window 

	//my_panels[0] = new_panel(my_wins[0]); // layout window
	
	my_panels[0] = new_panel(my_wins[0]); // chat window
	my_panels[1] = new_panel(my_wins[1]); // enter text window
	my_panels[2] = new_panel(my_wins[2]); // chat room window
	my_panels[3] = new_panel(my_wins[3]); // user window

	// Update the stacking order. 2nd panel will be on top
	update_panels();
-
	// Show it on the screen
	doupdate();

	
	mvprintw(2, 55, "Chat Room"); // print text "Chat Room" at this location
	mvprintw(11, 57, "Users"); // print text "Users" at this location

	// Enter puclic chat text here at this location inside panel[2]
	mvprintw(17, 2, "Msg>");
	//mvgetstr(39,6, str);
	//int show_msg = 1;//new msg will be show under previous msg
	//int second_run = 0;
	
	chatRoom.recv ( &room_List );
	
	
	pthread_t thread1, thread2;
	//pthead to print out chat message
	if(pthread_create(&thread1, NULL, show_message, NULL))
	{
	  perror("Error creating thread1: ");
	  exit(EXIT_FAILURE);
	}
	
	//pthead to send message to database
	unsigned long t = uuid;
	if(pthread_create(&thread2, NULL, get_message,(void *) t))
	{
	  perror("Error creating thread2: ");
	  exit(EXIT_FAILURE);
	}
	
	if(pthread_join(thread1, NULL))
	{
	  perror("Problem with pthread_join: ");
	}
	
	if(pthread_join(thread2, NULL))
	{
	  perror("Problem with pthread_join: ");
	}
	refresh();
	getch();
	endwin();
	
}

void *get_message(void *t)
{
  char str_msg[144];
  while(1)
  {   	
	mvgetstr(17,6, str_msg);
	message message_info;	
	message_info.cksum = 0;
	message_info.uuid = (unsigned long) t; 
	message_info.chatroom_idx = 1;		
	strncpy(message_info.message, str_msg, sizeof(message_info.message));
	mvprintw(17,6, "                                         ");
	
	Message.send(message_info);
  }
}

void *show_message(void *ptr)
{
  int count = 0;
  int count_user = 0;
  int show_msg = 1;
  int second_run = 0;
  while(1)
  {
    	sleep(0.1);
    	Message.recv ( &message_List );
    	User.recv (&user_List);
	

	//clear out line when chat message is a lot
	if(show_msg == 15)
	{
		show_msg = 1;
		int new_show_msg;
		for(new_show_msg = 1; new_show_msg < 16; new_show_msg++)
		{
		  mvprintw(new_show_msg,2, "                           ");
		}			  
	    	second_run ++;
	}

	if(count_user != user_List.size())
	{
	  int show_user = 13;
	  for(unsigned int j = 0; j < user_List.size(); j++)
	  {
	    if(strcmp(user_List[j].nick, user_List[j+1].nick) != 0)
	    {
		mvprintw(show_user, 51,"%s, %d", user_List[j].nick, user_List[j].uuid);
	    	show_user++;
	    }
	    
	  }
	  mvprintw(17,6, "");
	}
	//use to check if there is new message in the database
	//if(count != message_List.size())
	if(count != message_List.size())
	{
	  unsigned int i= message_List.size() - 1;
	  //for(unsigned int i= 0; i < message_List.size(); i++)
	  //{
	    for(unsigned int j = 0; j < user_List.size(); j++)
	    {
		if(user_List[j].uuid == message_List[i].uuid)
		{
		   mvprintw(show_msg, 2,"%s: %s", user_List[j].nick, message_List[i].message);
		   mvprintw(17,6, "");
		}
	    }
	    show_msg++;
	  //}
	}
	count = message_List.size();
	count_user = user_List.size();
  }
}




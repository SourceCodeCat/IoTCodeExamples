#include <iostream>
#include <string>
#include <iostream>
#include <unistd.h>

extern "C" 
{
   void initBindRfcomm();
   void startRfcomm();
   void stopRfcomm();
}
int main()
{

  int waitingForCommands = 1;
  std::string command="";
  initBindRfcomm();
  startRfcomm();
  while(waitingForCommands == 1)
  {
      std::cin>>command;
      if(command == "exit")
      {	 
         stopRfcomm();
         waitingForCommands = 0;
      }
        
  }
  std::cout<<"\nWaiting for threads to end...\n";
  sleep(2);
  return 0;
}

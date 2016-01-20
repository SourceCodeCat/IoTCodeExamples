#include "Freeboard.h"


Freeboard * fb;

int main()
{
	//WDIRECTION_NAME=SOUTH&WDIRECTION=180
	map<string,string> values;
        values["WDIRECTION_NAME"]="EAST";
        values["WDIRECTION"]="90"; 
	fb = new Freeboard();	
	fb->sendValues("https://dweet.io/dweet/for/WZPN1",values);
	return 0;
}

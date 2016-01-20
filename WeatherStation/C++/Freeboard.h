#ifndef __freeboard_h__
#define __freeboard_h__

#include <iostream>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include <map>

using namespace std;


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}
class Freeboard
{

  CURL *curl;
  CURLcode res;
  public:
    Freeboard()
    {
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl)
	{
	   cout<<"Freeboard init, seems good...\n"; 
	}
	else
	{
	   cout<<"Something went wrong with Freeboard init...\n";
	}
    }
    void sendValues(string url, map<string,string> values)
    {
	if(curl) 
	{
           string v = "";
	   curl_easy_setopt(curl, CURLOPT_URL, "https://dweet.io/dweet/for/WZPN1");//"https://dweet.io/dweet/for/my-thing-name"
           
	   for( map<string,string>::iterator val=values.begin(); val!=values.end(); ++val)
   	   {
                if(val == values.begin())
		{
		    v+=(*val).first +"="+(*val).second;
		}
		else
		{
		    v+="&"+(*val).first +"="+(*val).second;
		}
   	   }
	   curl_easy_setopt(curl, CURLOPT_POSTFIELDS, v.c_str());//"WDIRECTION_NAME=SOUTH&WDIRECTION=180"
 
           res = curl_easy_perform(curl);
           if(res != CURLE_OK)
               fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
 
  	}
        else
	{
	   cout<<"Can't send the values, remember ther was a problem when initing libcurl??  \n";
	}	
    }
    ~Freeboard()
    {
	curl_easy_cleanup(curl);
	curl_global_cleanup();
    };
  private:
};
#endif

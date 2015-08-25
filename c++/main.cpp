#include <stdio.h>
#include <curl/curl.h>
#include "mraa.hpp"
#include <map>
#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;




int read() {
    static int i = 0;
    return ++i;
}

string int_to_string(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

//################ FIWARE VARIABLES ################

string FIWARE_APIKEY = "lzSnQpEsC0lZVOVXaqZK";
string FIWARE_DEVICE = "myEdison";
string FIWARE_SERVER = "test.ttcloud.net";
string FIWARE_PORT = "8082";

int main()
{




	// check that we are running on Galileo or Edison
	mraa_platform_t platform = mraa_get_platform_type();
	if ((platform != MRAA_INTEL_GALILEO_GEN1) &&
			(platform != MRAA_INTEL_GALILEO_GEN2) &&
			(platform != MRAA_INTEL_EDISON_FAB_C)) {
		std::cerr << "Unsupported platform, exiting" << std::endl;
		return MRAA_ERROR_INVALID_PLATFORM;
	}

	// create an analog input object from MRAA using pin A0
	mraa::Aio* a0_pin = new mraa::Aio(0);
	mraa::Aio* a1_pin = new mraa::Aio(1);

	if (a0_pin == NULL || a1_pin == NULL) {
		std::cerr << "Can't create mraa::Aio object, exiting" << std::endl;
		return MRAA_ERROR_UNSPECIFIED;
	}

	// loop forever printing the input value every second
	for (;;) {
		typedef map <string, string> Table;
		Table measures;
		int lum = a0_pin->read();
		measures["l"]=int_to_string(lum);
		int touch = a1_pin->read();
		string pulse = "false";
		    if(touch>100){
		      pulse = "true";
		    }
		measures["p"]=pulse;

		string body = "";
		for (Table::const_iterator it = measures.begin(); it != measures.end(); ++it) {

		if (body != "") {
			 body += "#";
		}
		body += it->first + "|" + it->second;
		}

		CURL *curl;
		CURLcode res;


		string url="";
		url="http://"+FIWARE_SERVER+":"+FIWARE_PORT+"/iot/d?i="+FIWARE_DEVICE+"&k="+FIWARE_APIKEY;

		char bodyChar[body.length()];
		strcpy(bodyChar, body.c_str());

		char urlChar[url.length()];
		strcpy(urlChar, url.c_str());





		curl = curl_easy_init();
		if(curl) {
		cout << "Sending -> " << body << endl;

		curl_easy_setopt(curl, CURLOPT_URL, urlChar);
		struct curl_slist *headers=NULL;
		headers = curl_slist_append(headers, "Content-Type:");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyChar);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
		      fprintf(stderr, "curl_easy_perform() failed: %s\n",
		              curl_easy_strerror(res));

		    /* always cleanup */
		    curl_easy_cleanup(curl);
		  }
		  curl_global_cleanup();


		sleep(1);


	}

	return MRAA_SUCCESS;
}

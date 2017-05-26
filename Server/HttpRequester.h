//
// Created by erick on 26/05/17.
//

#ifndef GENETICGLADIATORSIMULATOR_HTTPREQUESTER_H
#define GENETICGLADIATORSIMULATOR_HTTPREQUESTER_H


#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

string data;
bool flag = true;

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up){
	
	for (int c = 0; c < size*nmemb; c++){
		data.push_back(buf[c]);
	}
	return size*nmemb;
}

void get(string url) {
	
	CURL *curl;
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	
	curl_easy_perform(curl);
	
	//cout << data;
	
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

string getIndividuo(){
	
	if(flag){
		get( "http://192.168.100.8:8080/gengladiator/poblacion/2" );
		flag = !flag;
	}
	else{
		get( "http://192.168.100.8:8080/gengladiator/poblacion/new" );
	}
	
	return data;
	
}

#endif //GENETICGLADIATORSIMULATOR_HTTPREQUESTER_H

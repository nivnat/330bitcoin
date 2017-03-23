//
// Created by Ari Trachtenberg on 3/15/17.
//

#include "myBloom.h"
#include <cstring>
#include <iostream>
#include <string>
long hashX(string key,long len)
{
	int sum=0;
	for(int i=0;i<key.length();i++)
	{
		sum+=key[i];
	}
	return sum%max;
}

long hashY(string key, long len)
{
	int seed=0;
	for(int i=0;i<key.length();i++)
	{
		seed=1331*seed+key[i];
	}
	return seed*len;
}
long hashZ(const char* key,long len)
{
	long int h=37;
	while(*key)
	{
		 h = (h * 54059) ^ (key[0] * 79693);
    	 s++;
	}
	return h%86969;
}
//unsigned long hash4()


myBloom::myBloom(int mm) : Bloom(mm) 
{ 
	filter = new char[length]; memset(filter, '_', length);
}

myBloom::myBloom(std::string newFilter) : myBloom(newFilter.length()) 
{ 
	strncpy(filter,newFilter.c_str(),length); 
}

void myBloom::insert(std::string item) 
{ 
	int hashe1=hashX(item,this->length); //only x
	switch(filter[hashe1])
	{
		case '0':
		filter[hashe1]='X'; //IF FILTER HAS NOTHING PUT X
		break;
		//IF X LEAVE IT
		case 'Y':
		filter[hashe1]='A';
		break;

		case 'Z':
		filter[hashe1]='C';
		break;

		case 'B':
		filter[hashe1]='E';
		break;

		default:
		break;

	}

	int hashe2=hashY(item,this->length); //to check y
	switch(filter[hashe2])
	{
		case '0':
		filter[hashe2]='Y';
		break;

		case 'X':
		filter[hashe2]='A';
		break;

		case 'Z':
		filter[hashe2]='B';
		break;

		case 'B':
		filter[hashe2]='E';
		break;

		default:
		break;

	}

	int hashe3=hashZ(item,this->length);
	switch(filter[hashe3])
	{
		case '0':
		filter[hashe3]='Z';
		break;

		case 'X':
		filter[hashe3]='C';
		break;

		case 'Y':
		filter[hashe3]='B';
		break;

		case 'A':
		filter[hashe3]='E';
		break;

		default:
		break;
	}
	//filter[item[0]%length] = 'X'; 
}

bool myBloom::exists(std::string item) 
{

	int hashe1=hashX(item,this->length);
	int hashe2=hashY(item,this->length);
	int hashe3=hashZ(item,this->length);

	//X
	if(filter[hashe1]=='0' || filter[hashe1]=='Y' ||filter[hashe1]='Z' || filter[hashe1]=='B' )
		return false;

	if(filter[hashe2]=='0' || filter[hashe2]=='X' ||filter[hashe2]='Z' || filter[hashe2]=='C' )
		return false;

	if(filter[hashe3]=='0' || filter[hashe3]=='X' ||filter[hashe3]='Y' || filter[hashe3]=='A' )
		return false;

	return true;
    //return filter[item[0]%length]=='X';
}
//i added a comment
//for a branch

std::string myBloom::output() 
{ 
	return std::string(filter, length); 
}

myBloom::~myBloom() { delete[] filter; }

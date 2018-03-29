#include<iostream>
#include <stdio.h>
#include<fstream>
using namespace std;

string key[32]={"auto","diuble","int","struct","break","else","long","switch","case","enum","register","typedef","char","extern","return","union","const","float","short","unsigned","continue","for","signed","void","default","goto","sizeof","volatile","do","if","static","while"	};

void check(string temp){
	for(int i=0;i<32;i++){
		if(temp==key[i]){cout<<temp<<" is a keyword\n";return;}
	}
	 cout<<temp<<" is a identifier\n";
}


int main(){
	int count =0;
	ifstream file;
	file.open("input.c",ios::in);
	if(!file.is_open()){
		cout<<"file opening failed\n";
		exit(-1);
	}

	char ch,chp=' ' ;
	int f=0,s=0; //f will be 1 whenever I have to check for keyword or identifier
	string temp="";
	file.get(ch);
	while(!file.eof()){
		if(chp=='\n')goto x;
		if(chp==' '){
			//start saving new toke
			s=1;
			temp="";
		}
      	if(!isalnum(ch) && chp!=' '){
        		if(ch =='\"'){
          		file.get(ch);
          		while(ch!='\"'){
            		file.get(ch);
          		}
        	}

          //if(ch!='\n'&&chp!='\n')cout<<"character is  "<<chp<<"\t"<<ch<<endl;
          //else if(ch=='\n')cout<<"character is  "<<chp<<"\t"<<"$"<<endl;
          //else cout<<"character is  "<<"$"<<"\t"<<ch<<endl;
          if(isalnum(chp)&&ch==' '){
          	//cout<<"here i will call check function\n";
          	check(temp);
          }
          else if(isalnum(chp)&&ch=='('){cout<<temp<<"  is a function name\n";temp="";}
          else {cout<<temp<<" is a special character\n";temp="";}
         count++;
      	}
      	temp+=ch;
      	x:
      	chp = ch;
      	file.get(ch);
      	if(ch==' '&&chp==' '){
        chp=ch;
        file.get(ch);
      }
  	}
  file.close();
  printf("Number of tokens = %d\n",count);
}

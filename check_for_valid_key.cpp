#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <fstream>
using namespace std;


int main(){
	//taking file input 
	ifstream input_file;
	input_file.open("input_keywords.txt",ios::in);
	if(!input_file.is_open()){
		cout<<"opening file failed\n";
		exit(-1);
	}
	

	//reading from file
	char c;bool newline=false;
	x:
	//c='\0';
	if(!input_file.eof())
    	input_file.get(c);
    else
    	return 0;
    if(newline==true){
    	input_file.get(c);
    	while(c!='\n'){
    		input_file.get(c);
    	}
    	newline=false;
    }
    if(input_file.eof()){
    	input_file.close();
    	return 0;
    }
    if(c=='\n')goto x;
    if(c=='f'){
    	input_file.get(c);
    	if(c=='o'){
    		input_file.get(c);
    		if(c=='r'){
    			cout<<"valid\n";
    			goto x;
    		}
    		else{
    			cout<<"invalid keyword\n";
    			newline=true;
    		}	
    	}
    	else{
    		cout<<"invalid keyword\n";
    		newline=true;
    		goto x;
    	}
	}
	else if(c=='i'){
		input_file.get(c);
		if(c=='f'){
			cout<<"valid\n";
			goto x;
		}
		else{
    		cout<<"invalid keyword\n";
    		newline=true;
    	}

	}
	else if(c=='e'){
		input_file.get(c);
    	if(c=='l'){
    		input_file.get(c);
    		if(c=='s'){
    			input_file.get(c);
    			if(c=='e'){
    				cout<<"valid\n";
    				goto x;
    			}
    			else{
    			cout<<"invalid keyword\n";
    			newline=true;
    			}
    		}
    		else{
    			cout<<"invalid keyword\n";
    			newline=true;
    		}
    	}
    	else{
    		cout<<"invalid keyword\n";
    		newline=true;
    	}
	}
	else if(c=='w'){
		input_file.get(c);
    	if(c=='h'){
    		input_file.get(c);
    		if(c=='i'){
    			input_file.get(c);
    			if(c=='l'){
    				input_file.get(c);
    				if(c=='e'){
    					cout<<"valid\n";
    					goto x;
    				}
    				else{
    					cout<<"invalid keyword\n";
    					newline=true;
    				}
    			}
    			else{
    				cout<<"invalid keyword\n";
    				newline=true;
    			}
    		}
    		else{
    			cout<<"invalid keyword\n";
    			newline=true;
    		}
    	}
    	else{
    		cout<<"invalid keyword\n";
    		newline=true;
    	}		
	}
	else{
		cout<<"invalid keyword\n";
		newline=true;
	}
	goto x;

	//closing file
	input_file.close();
	return 0;
}
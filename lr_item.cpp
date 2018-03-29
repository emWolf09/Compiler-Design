#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
#include "lr_help.h"
using namespace std;


	

int main(){

	ifstream file;
	file.open("input_lr.txt",ios::in);

	if(!file.is_open()){
		cout<<"file opening failed\n";
		exit(-1);
	}

	string s;
	getline(file,s);
	get_start_symbol(s[0]);
	get_input(s);
	
	//getting first
	while(getline(file,s))
		get_input(s);

	cout<<"\n Given Grammar is : \n";
	print_input();
	//check_correct_input();
	get_terminal();
	print_terminals();

	init_lr_zero();

	

	file.close();
	return 0;

}
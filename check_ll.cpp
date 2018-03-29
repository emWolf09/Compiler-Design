#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
#include "grammar_help.h"
using namespace std;




int main(){

	ifstream file;
	file.open("input_grammer.txt",ios::in);

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
		
	cout<<"All core code is in grammar.h help file\nIf there is infinte recursive call in grammar for computing follow It should give segmentation fault\n\n";
	cout<<"NOTE:: @ is used for epsilon\nread_successfull from file\n\nGiven grammar is :-\n\n";
	print_input();
	get_first();
	cout<<"\nfirst calculated and is:-\n\n";
	print_first();

	//compute follow
	get_follow();
	cout<<"\nfollow calculated and is:-\n\n";
	print_follow();

	get_terminal();
	print_terminals();
	get_ptable();
	fill_ptable();
	cout<<"\n\n";
	print_ptable();
	
	file.close();
	return 0;

}
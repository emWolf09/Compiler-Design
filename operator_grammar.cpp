#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
#include "operator_grammar_help.h"
using namespace std;




int main(){

	ifstream file;
	file.open("input_operator_grammar.txt",ios::in);

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
	check_correct_input();
	get_terminal();
	print_terminals();

	//creating operator precedece table
	cout<<"\n\ntable operator\n\n";
	get_precedence_table();
	cout<<"Enter the string to be matched\n";
	cin>>s;
	process_input(s);


	file.close();
	return 0;

}
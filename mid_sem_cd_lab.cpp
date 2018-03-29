/*
MAHESH NAGARWAL
2015KUCP1043

MIDSEM ANSWER

*/

#include<iostream>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;

//map<int,char> state
map<int,char> state; 
// {
// 	{0,'A'},
// 	{1,'B'},
// 	{2,'C'},
// 	{3,'D'},
// 	{4,'E'},
// 	{5,'F'},
// 	{6,'G'},
// 	{7,'H'},
// 	{8,'I'},
// 	{9,'J'},
// 	{10,'K'},
// 	{11,'L'}

// };


std::vector<int> f;
void init_final(){
	f.resize(1);
f[0] = 0;
// f[1] = 1;
// f[2] = 2;
// f[3] = 3;
// f[4] = 4;
// f[5] = 8;
}

vector<vector<int> > trans;

void init_state(){
	int i=0;
	int c = 'A';
	while(i<12&&c<='L'){
		// pair<int,char>p;
		// p.first = i;
		// p.second=c;
		state.insert(make_pair(i,c));
		c++;
		i++;
	}
}


void init_tran(){
	// for(int i=0;i<12;i++){
	// 	trans[i].resize(1);
	// }
	trans.resize(12);
	for(int i=0;i<12;i++){
		trans[i].resize(2);
	}
	trans[0][0] = 4;
	trans[0][1] = 1;

	trans[1][0] = 5;
	trans[1][1] = 2;

	trans[2][0] = 6;
	trans[2][1] = 3;

	trans[3][0] = 7;
	trans[3][1] = 0;

	trans[4][0] = 8;
	trans[4][1] = 5;

	trans[5][0] = 9;
	trans[5][1] = 6;

	trans[6][0] = 10;
	trans[6][1] = 7;

	trans[7][0] = 11;
	trans[7][1] = 4;

	trans[8][0] = 0;
	trans[8][1] = 9;

	trans[9][0] = 1;
	trans[9][1] = 10;

	trans[10][0] = 2;
	trans[10][1] = 11;

	trans[11][0] = 3;
	trans[11][1] = 8;

	
	
		

	
}


//f=(vector){0,1,2,3,4,8};
void string_proc(string s){
	int t=0;
	int st = 0;
	cout<<"state sequence : \t";
	for(int i=0;i<s.length();i++){
		char c = s[i];
		if(c=='a')t=0;
		else if(c=='b')t=1;
		else {cout<<"\nmust contain only a and b :: invalid string \n";exit(-1);}

		char current = state[st];
		cout<<current<<"\t";

		st = trans[st][t];

	}
	char current = state[st];
	cout<<current<<"\n";
	int i=0;
	for(i=0;i<6;i++){
		if(st==f[i]){
			cout<<"string valid";
			break;
		}
		
	}
	if(i==6)cout<<"STRING INVALID\n";

	
}


void print_tran(){
	cout<<"\ta\tb"<<endl;
	for(int i=0;i<12;i++){
		cout<<state[i]<<"\t";
		cout<<state[trans[i][0]]<<"\t"<<state[trans[i][1]]<<endl;
	}
}

int main(){
	init_state();
	init_tran();
	cout<<"transition table is :\n";
	print_tran();
	cout<<endl;
	init_final();

	
	string s;
	cout<<"Enter the string for dfa : ";
	cin>>s;
	if(s.length()==0){
		cout<<"valid string\n";
		exit(-1);
	}
	else if(s.length()<3 ){
		cout<<"invalid string\n";
		exit(-1);
	}

	
	//cout<<state[8]<<endl;
	


	string_proc(s);
	return 0;
}
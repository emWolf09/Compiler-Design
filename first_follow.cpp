/*
for epsilon I am using  @

Name - Mahesh Nagarwal
ID - 2015KUCP1043
Assignement - from given grammar get first and follow
*/


#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

map<char ,vector<string> > ip;
//map for firsr
map<char,vector<char>> _first;

map<char,vector<char>> follow;


void print_first(){
	map<char ,vector<char>> ::iterator it = _first.begin();
	while(it!=_first.end()){
		cout<<it->first<<" =\t";
		int n=it->second.size();
		for(int i=0;i<n;i++){
			cout<<it->second[i]<<", ";
		}
		cout<<endl;
		it++;
	}
}

bool is_terminal(char c){
	//if(c>='a'&&c<='z')return true;
	//else if(c<'A'&&c>'Z')return true;
	 if(c>='A'&&c<='Z')return false;
	else return true;
}






void print_input(){

		//printing the map
	 map<char ,std::vector<string>> ::iterator it = ip.begin();
	while(it!=ip.end()){
		char n_t = it->first;
		cout<<n_t<<"->";
		int n = it->second.size();
		for(int i=0;i<n;i++){
			if(i==n-1)cout<<it->second[i];
			else
			cout<<it->second[i]<<"|";
		}
		cout<<endl;
		it++;
	}
}
void get_input(string s){
	char n_t = s[0];
	string right_part;
	if(s.length()>3)
	right_part = s.substr(3,s.length()-1);
	//check if gor n_t nonterminal already production 
	map<char ,std::vector<string>> ::iterator it = ip.begin();
	while(it!=ip.end()){
		if(it->first==n_t)break;
		else it++;
	}
	if(it==ip.end()){
		//insert new nt for new production
		pair<char,vector<string>> x ;
		x.first = n_t;
		(x.second).push_back(right_part);
		ip.insert(x);
	}
	else{
		it->second.push_back(right_part);
	}


}


void calc_first(char n_t){
	bool bad_luck = false;
	map<char ,vector<string> >:: iterator it2 = ip.find(n_t);
	int n = it2->second.size();
	pair<char,vector<char>> x;
	x.first = n_t;
	for(int i=0;i<n;i++){
		char chr = it2->second[i][0];
		if(is_terminal(chr)){
			//push that terminal into _first vector and move to the next production for the same nonteminal
			x.second.push_back(chr);
		}
		else if(chr=='@'){
			//push episolan and move to the next production
			x.second.push_back(chr);

		}
		else if(!is_terminal(chr)){
			string str = it2->second[i];
			for(int j=0;j<str.length();j++){
				if(is_terminal(str[j])){
					x.second.push_back(str[j]);
					break;
				}
				if(_first.find(str[j])==_first.end() ){
					//first we have to compute first of y1
					//cout<<"\nrecursicve call for"<<str[j]<<endl;
					calc_first(str[j]);
				}
				//copy all the terminals from first(y1) except epsilon
				std::vector<char> v = (_first.find(str[j]))->second;
				int size_v = v.size();
				for(int k=0;k<size_v;k++){
					if(v[k]=='@'){
						bad_luck = true;
					}
					else if(find(x.second.begin(), x.second.end(), v[k]) == x.second.end())
					x.second.push_back(v[k]);
				}

				if((j==str.length()-1)&&bad_luck==true){
					x.second.push_back('@');
					break;
				}

				//check if y1 is epsilon or not
				if(bad_luck == false){
					bad_luck = false;
					break;
				}


			}


		}
	}
	_first.insert(x);	
}
void get_first(){

	map<char ,vector<string> >:: iterator it = ip.begin();
	//cout<<"in get_first\n";
	while(it!=ip.end()){
		//check if already first is calcuated or not
		if(_first.find(it->first)==_first.end()){
			//cout<<"\n first calculated for "<<(it->first)<<endl;
			calc_first(it->first);
			
		}


		it++;
	}
	
}

void print_follow(){
	map<char ,vector<char>> ::iterator it = follow.begin();
	while(it!=follow.end()){
		cout<<it->first<<" =\t";
		int n=it->second.size();
		for(int i=0;i<n;i++){
			if(i==n-1)cout<<it->second[i];
			else
			cout<<it->second[i]<<", ";
		}
		cout<<endl;
		it++;
	}
}

void calc_follow(char n_t){
	bool bad_luck = false;
	pair<char,vector<char>> x;
	x.first = n_t;
	if(n_t=='S')
		x.second.push_back('$');

	map<char ,vector<string> >:: iterator it2 = ip.begin();
	
	while(it2!=ip.end()){
		//chr to store current LHS nonterminal
		char chr = it2->first;
		//cout<<chr<<endl;
		int n = it2->second.size();
		//cout<<"i am called\n";
		for(int i=0;i<n;i++){
			map<char,vector<char>>::iterator it3 ;
			//for each string
			string s = it2->second[i];
			if(s=="@")continue;
			int l = s.length();
			int j = 0;
			for(j=0;j<l;j++){
				if(s[j]==n_t){
					break;
				}
			}
			//cout<<n_t<<"and string is "<<s<<" jai ram = "<<j<<endl;
			if(j<l-1){
				
				for(int k = j+1;k<l;k++){
					//cout<<"callerd for "<<n_t<<"and calling "<<s[k]<<endl;
					if(!is_terminal(s[k])){
							it3 = _first.find(s[k]);
							int size_first = it3->second.size();
							for(int p = 0;p<size_first;p++){
								char temp =it3->second[p] ;
								if(temp=='@')
									bad_luck = true;
								else
									x.second.push_back(temp);
							}
							if(bad_luck==false){
								break;	
							}
							if(k==l-1&&bad_luck==true)goto label;
								
					}

					else if(is_terminal(s[k])){
						//cout<<s[k]<<endl;
						x.second.push_back(s[k]);break;
					}
							
							
				}
					
			}
			else if(j==l-1){
				if(n_t==chr)continue;
				label:

				//n_t is at last of string
				//first count follow of chr and push this into n_t follow 
				
				map<char,vector<char>>:: iterator it4 = follow.find(chr);
				//if(chr=='S')follow.insert(x);
				if(chr!='S'&&it4==follow.end()){
					calc_follow(chr);

				}

				//copy its follow into n_t follow
				it3 = follow.find(chr);
				if(it3!=follow.end()){
					int size_first = it3->second.size();
							for(int p = 0;p<size_first;p++){
								char temp =it3->second[p]; 
								x.second.push_back(temp);
							}
					
				}
			}
		} 


		it2++;
	}
	if(follow.find(x.first)==follow.end())
	follow.insert(x);


	
}

void get_follow(){
	//cout<<"\n follow calculated for S"<<endl;
	calc_follow('S');
	map<char ,vector<string> >:: iterator it = ip.begin();
	while(it!=ip.end()){
		if(follow.find(it->first)==follow.end()){
	//		cout<<"\n follow calculated for "<<(it->first)<<endl;
			calc_follow(it->first);
		}
		it++;
	}

}

	

int main(){

	ifstream file;
	file.open("input_grammer.txt",ios::in);

	if(!file.is_open()){
		cout<<"file opening failed\n";
		exit(-1);
	}

	string s;
	
	
	//getting first
	while(getline(file,s))
		get_input(s);
		
	cout<<"If there is infinte recursive call in grammar for computing follow It should give segmentation fault\n\n";
	cout<<"NOTE:: @ is used for epsilon\nread_successfull from file\n\nGiven grammar is :-\n\n";
	print_input();
	get_first();
	cout<<"\nfirst calculated and is:-\n\n";
	print_first();

	//compute follow
	get_follow();
	cout<<"\nfollow calculated and is:-\n\n";
	print_follow();
	file.close();
	return 0;

}
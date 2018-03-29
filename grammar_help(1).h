
#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
#include<stack>
#include<iomanip>
using namespace std;

char start_symbol;

map<char ,vector<string> > ip;
//map for firsr
map<char,vector<char>> _first;

map<char,vector<char>> follow;

map<char, int> terminal;
map<char,int> nonterminals;
map<int, char> reverse_terminal;
map<int,char> reverse_nonterminals;

int n;
int t;

/*-------------------*/
vector<vector<string>> p_table;
/*--------data for parse tree----------------------------*/
stack<char>stk;

/*-------------------------------------------------------*/
bool is_terminal(char c){
	//if(c>='a'&&c<='z')return true;
	//else if(c<'A'&&c>'Z')return true;
	 if(c>='A'&&c<='Z')return false;
	else return true;
}


void stack_show()
{
    stack <char> g = stk;
    while (!g.empty())
    {
        cout<<g.top();
        g.pop();
    }
    cout <<setw(8);
}

void init_stack(){
	stk.push('$');
	stk.push(start_symbol);
}
void check_string(string s){
	init_stack();
	char current = 0;
	//cout<<endl;
	//cout<<"stack top to left\t\tinputstring\t\tproduction\t\t\n";
	while(stk.top()!='$'&&current<s.length()&&!stk.empty()){
		char row = stk.top();
		//cout<<"top of stack is"<<row;
		int row_index = nonterminals[row];
		int colom_index  = terminal[s[current]];
		string p = p_table[row_index][colom_index];
		//cout<<p<<"is the production\n";exit(-1);
		if(p=="-"){
			//we dont have production
			cout<<"given input string is not valid as there is no production for "<<row<<" and "<<s[current]<<endl;
			exit(-1);
		}
		else if(p=="@"){
			stack_show();
			//show remaining string
			for(int j=current;j<s.length();j++){
				cout<<s[j];
			}
			cout<<setw(15);
			cout<<row<<"->"<<p<<setw(15)<<"\n\n";
			
			
			stk.pop();
			stack_show();
			//show remaining string
			for(int j=current;j<s.length();j++){
				cout<<s[j];
			}
			cout<<setw(15);
			cout<<row<<"->"<<p<<setw(15)<<"\n\n";
			
			continue;
		}
		else{
			//we have production
			
			stack_show();
			//show remaining string
			for(int j=current;j<s.length();j++){
				cout<<s[j];
			}
			cout<<setw(15);
			cout<<row<<"->"<<p<<setw(15)<<"\n\n";
			//first pop one element from stack then push this production into push
			stk.pop();
			for(int i=p.length()-1;i>=0;i--){
				stk.push(p[i]);
			}
			char top = stk.top();
			if(!is_terminal(current)){
				cout<<"invalid input\n";
				exit(-1);
			}
			if(s[current]== top&&(current!=s.length()-1)){
				//remove from both stack and input string
				stack_show();
				//show remaining string
				for(int j=current;j<s.length();j++){
					cout<<s[j];
				}
				cout<<setw(15);
				cout<<row<<"->"<<p<<setw(15)<<"\n\n";
				current++;
				stk.pop();
				continue;

			}
			else if(s[current]== top&&(current==s.length()-1)){
				break;
			}
			else if(s[current]!= top&&(current==s.length()-1)){
				continue;
			}

		}
	}

	cout<<"string parsed using table successfully\n";

}

void get_start_symbol(char chr){
	start_symbol = chr;
}




void print_ptable(){


	//print table
	for(int i=0;i<n+1;i++){
		
		for(int j=0;j<t+1;j++){
			if(i==0&&j==0)cout<<"-\t";
			else if(i==0&&j>0){
				char c = reverse_terminal[j-1];
				cout<<c<<"\t";

			}
			else if(i>0&&j==0){
				char c = reverse_nonterminals[i-1];
				cout<<c<<"\t";				
			}
			else{ 
				//p_table[i-1][j-1] = "@";
				cout<<p_table[i-1][j-1]<<"\t"; 
			}

			
		}
		cout<<endl;
	}

}

void fill_ptable(){
	bool bad_luck = false,flag = false,flag_ll = false;
	int colom_index = 0;
	map<char,vector<string>>::iterator it = ip.begin();
	while(it!=ip.end()){
		char row = it->first;
		int row_index = nonterminals[row];
		int n = it->second.size();
		for(int i=0;i<n;i++){
			string s = it->second[i];
			if(s=="@"){
				//follow of LLHS will be for pushing this production
				// bad_luck = true;
				// goto label;
				continue;
				//work is remaining here
			}
			for(int j=0;j<s.length();j++){
				if(is_terminal(s[j])){
					//good this should be first only
					colom_index = terminal[s[j]];
					if(p_table[row_index][colom_index]=="-"||p_table[row_index][colom_index]==s)
						p_table[row_index][colom_index] = s;
					else{
						flag_ll = true;
						cout<<"multiple entries in "<<row_index<<"\t and "<<colom_index<<endl;
						//exit(-1);
					}
					break;
				}
				else if(!is_terminal(s[j])){
					std::vector<char> v = _first[s[j]];
					int k;
					for(k=0;k<v.size();k++){
						if(v[k]!='@'){
							colom_index = terminal[v[k]];
							if(p_table[row_index][colom_index]=="-"||p_table[row_index][colom_index]==s)
								p_table[row_index][colom_index] = s;
							else{
								flag_ll = true;
								cout<<"multiple entries in "<<row_index<<"\t and "<<colom_index<<endl;
								//exit(-1);
							}
						}
						else{
							flag = true;
						}
					}
					if(flag==true&&(k==v.size()-1)){
						bad_luck = true;
					}
					if(flag == true){
						flag = false;
						continue;
					}
					else{
						break;
					}



				}
			}
			if(find (_first[row].begin(), _first[row].end(), '@')!=_first[row].end()){
				bad_luck =true;
				s = "@";
			}

			if(bad_luck==true){
				s="@";
				//copy LHS FOLLOW ALSO
				label:
				std::vector<char> w = follow[row];
				for(int k=0;k<w.size();k++){
					colom_index = terminal[w[k]];
					if(p_table[row_index][colom_index]=="-"||p_table[row_index][colom_index]==s)
						{p_table[row_index][colom_index] = s;
							//cout<<"in follow s is"<<s<<endl;
						}
					else{
						flag_ll = true;
						cout<<"multiple entries in "<<row_index<<"\t and "<<colom_index<<endl;
						cout<<"already present is "<<p_table[row_index][colom_index]<<" so cant insert "<<s<<endl;
						//exit(-1);
					}
				}

			}
		}

		it++;
	}

	if(flag_ll==true){
		cout<<"\n\n:::::::::::::::::Not LL1 grammar ::::::::::::\n\n";
	}
	else
		cout<<"\n\n:::::::::::::::::YES LL1 grammar ::::::::::::\n\n";		
}

void get_ptable(){
	p_table.resize(n);
	for(int i=0;i<n;i++){
		p_table[i].resize(t);
	}
	//print table
	for(int i=0;i<n+1;i++){
		
		for(int j=0;j<t+1;j++){
			if(i==0&&j==0)cout<<"-\t";
			else if(i==0&&j>0){
				char c = reverse_terminal[j-1];
				cout<<c<<"\t";

			}
			else if(i>0&&j==0){
				char c = reverse_nonterminals[i-1];
				cout<<c<<"\t";				
			}
			else{ 
				p_table[i-1][j-1] = "-";
				cout<<p_table[i-1][j-1]<<"\t"; 
			}

			
		}
		cout<<endl;
	}
}



void print_terminals(){
	map<int ,char> ::iterator it = reverse_terminal.begin();
	//map<char ,int> ::iterator it1 = nonterminals.begin();
	cout<<t<<"terminals in the grammarr aree =\n";
	while(it!=reverse_terminal.end()){
		cout<<it->first<<" =\t"<<it->second<<endl;
		it++;
	}	
	it = reverse_nonterminals.begin();
	cout<<n<<"non-teminal in the grammar are = \n";
	while(it!=reverse_nonterminals.end()){
		cout<<it->first<<" =\t"<<it->second<<endl;
		it++;
	}
}

	
//function to get all the nonterminals
void get_terminal(){
	int i1=0,j1=0;
	map<char,vector<string>>::iterator it = ip.begin();
	while(it!=ip.end()){

		char n_t = it->first;
		if(nonterminals.find(n_t)==nonterminals.end()){
			nonterminals.insert(make_pair(n_t,i1));
			reverse_nonterminals.insert(make_pair(i1,n_t));
			i1++;
		}
		std::vector<string> v = it->second;
		int n = v.size();
		for(int i=0;i<n;i++){
			string s = v[i];
			if(s=="@")continue;
			for(int j=0;j<s.length();j++){
				if(is_terminal(s[j])){
					if(terminal.find(s[j])==terminal.end()){
						char temp =(char)s[j]; 
						terminal.insert(make_pair(temp,j1));
						reverse_terminal.insert(make_pair(j1,temp));
						j1++;
					}
				}
			}
		}


		it++;
	}
	terminal.insert(make_pair('$',j1));
	reverse_terminal.insert(make_pair(j1,'$'));
	n = nonterminals.size();
	t = terminal.size();
}



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
			if(find(x.second.begin(), x.second.end(), chr) == x.second.end())
			x.second.push_back(chr);
		}
		else if(chr=='@'){
			//push episolan and move to the next production
			if(find(x.second.begin(), x.second.end(), chr) == x.second.end())
			x.second.push_back(chr);

		}
		else if(!is_terminal(chr)){
			string str = it2->second[i];
			for(int j=0;j<str.length();j++){
				if(is_terminal(str[j])){
					if(find(x.second.begin(), x.second.end(), str[j]) == x.second.end())
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
					if(find(x.second.begin(), x.second.end(), '@') == x.second.end())
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
	bool bad_luck = false,flag=false;
	pair<char,vector<char>> x;
	x.first = n_t;
	if(n_t==start_symbol)
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
				flag = false;
				if(s[j]==n_t){
					break;
				}
			}
			//for checking further in same production for same non terminal
			
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
									if(find(x.second.begin(), x.second.end(), temp) == x.second.end())
									x.second.push_back(temp);
							}
							if(bad_luck==false){
								break;	
							}
							if(k==l-1&&bad_luck==true)goto label;
								
					}

					else if(is_terminal(s[k])){
						//cout<<s[k]<<endl;
						if(find(x.second.begin(), x.second.end(), s[k]) == x.second.end())
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
								if(find(x.second.begin(), x.second.end(), temp) == x.second.end()) 
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



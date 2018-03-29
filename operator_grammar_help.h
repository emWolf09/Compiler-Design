
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


map<char, int> terminal;
map<char,int> nonterminals;
map<int, char> reverse_terminal;
map<int,char> reverse_nonterminals;
map<char,int> operator_table= {
	{'i',10},
	{'^',6},
	{'+',5},
	{'-',5},
	{'*',8},
	{'/',9},
	{'$',2}
};
std::vector<char> opt  {'+','-','*','/','^','$','%'};
int n;
int t;

/*-------------------*/
//vector<vector<string>> p_table;
/*--------data for parse tree----------------------------*/
stack<char>stk;
stack<char>stk2;
/*-------------------------------------------------------*/
std::vector<std::vector<int>> p_table;

/*-------------------------------------------------------*/


bool is_terminal(char c){
	//if(c>='a'&&c<='z')return true;
	//else if(c<'A'&&c>'Z')return true;
	 if(c>='A'&&c<='Z')return false;
	else return true;
}

int get_precedence(char c1,char c2){
	if(operator_table.find(c1)==operator_table.end()||operator_table.find(c2)==operator_table.end()){
		cout<<"no entry in operator_table for "<<c1<<" or "<<c2<<endl;
		exit(-1);
	}
	if(operator_table[c1]>operator_table[c2])return 1;
	else if(operator_table[c1]==operator_table[c2])return 0;
	else return -1;
}

void get_precedence_table(){
	p_table.resize(t);
	for(int i=0;i<t;i++)p_table[i].resize(t);

	//filling table
	for(int i=0;i<t+1;i++){
		
		for(int j=0;j<t+1;j++){
			if(i==0&&j==0)cout<<"\t";
			else if(i==0&&j>0){
				char c = reverse_terminal[j-1];
				cout<<c<<"\t";

			}
			else if(i>0&&j==0){
				char c = reverse_terminal[i-1];
				cout<<c<<"\t";				
			}
			else{ 
				char c2 = reverse_terminal[j-1];
				char c1 = reverse_terminal[i-1];
				p_table[i-1][j-1] = get_precedence(c1,c2);
				cout<<p_table[i-1][j-1]<<"\t"; 
			}

			
		}
		cout<<endl;
	}
}
char find_in_ip(string exp){
	map<char,std::vector<string>>::iterator it = ip.begin();
	char lhs;
	while(it!=ip.end()){
		lhs = it->first;
		int n = it->second.size();
		for(int i=0;i<n;i++){
			if(exp == it->second[i])
				return lhs;
		}
		it++;
	}
	cout<<"\tlhs not found for"<<exp<<endl;
	exit(-1);
}
bool is_operator(char ch ){
	// if(ch!='i')return true;
	// else return false;
	std::vector<char>::iterator it;
	it = std::find (opt.begin(), opt.end(), ch);
    if (it != opt.end())
    {
       return true;
    }
    else
        return false;
}


void process_input(string s){
	if(s[s.length()-1]!='$')s+='$';
	//init_stack();
	stk.push('$');
	int c=0;
	cout<<"string  stack \toperation\treduced by\n";
	while(!stk.empty()&&c<s.length()){
		char chr1 = s[c];
		char chr2 = stk.top();
		cout<<chr1<<"        "<<chr2<<"    \t";
		int p = get_precedence(chr1,chr2);
		//if(chr1=='$'&&stk.top()!='$'){
		//	cout<<"string is not valid\n";
		//	exit(0);
		//}
		 if(chr1=='$'&&stk.top()=='$'){
			cout<<"termination condition\n";
			break;
		}
		else if(p==-1){
			//pop
			cout<<chr2<<"poped\t";
			stk.pop();
			if(is_operator(chr2)){
				//perform reduction
				char x1 = stk2.top();
				stk2.pop();
				char x2 = stk2.top();
				stk2.pop();
				string exp = "";
				exp += x1;
				exp+=chr2;
				exp+=x2;
				char lhs = find_in_ip(exp);
				stk2.push(lhs);
				cout<<"\t"<<lhs<<"->";
				//exp = lhs+"->"+exp;
				cout<<""<<exp<<"\n";
				
			}
			else{
				string exp = "";
				exp +=chr2;
				char x1 = find_in_ip(exp);
				stk2.push(x1);
				cout<<"\t"<<x1<<"->";
				//exp = x1+"->"+exp;
				cout<<""<<exp<<endl; 
			}
		}
		
		else if(p==0||p==1){
			//push chr1
			cout<<chr1<<"pushed\n";
			stk.push(chr1);
			c++;
		}

	}
	if(stk2.top()==start_symbol)
		cout<<"string process successfull\n";
	else if(stk2.top()!=start_symbol)
		cout<<"string process failed\n";

}

/*
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
	
	//stk.push(start_symbol);
}
*/
void get_start_symbol(char chr){
	start_symbol = chr;
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







void check_correct_input(){
	map<char ,std::vector<string>> ::iterator it = ip.begin();
	while(it!=ip.end()){
		char n_t = it->first;
		//cout<<n_t<<"->";
		int n = it->second.size();
		for(int i=0;i<n;i++){
			string s = it->second[i];
			for(int i=0;i<s.length();i++){
				if(!is_terminal(s[i])&&!is_terminal(s[i+1])){
					cout<<"two nonterminals together is not allowed in operator grammar\n";
					exit(-1);
				}
				else if(s[i]=='@'){
					cout<<"@ is not allowed in operator grammar\n";
					exit(-1);	
				}
			}
			
		}
		//cout<<endl;
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








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

bool is_terminal(char c){
	//if(c>='a'&&c<='z')return true;
	//else if(c<'A'&&c>'Z')return true;
	 if(c>='A'&&c<='Z')return false;
	else return true;
}


/*-------------------------------------------------------*/
  

class production{
	public:
		string s;
		int dot;
};

class item{
	public:
	int item_no;
	production parent;
	map<char,vector<production>> production_list;

	
		item(int no,production p){
			item_no = no;
			parent = p; 
		}



};

vector<item> items;

void print_item(item i){
	//cout<<"yipee\n";
	cout<<"\nprinting item no "<<i.item_no<<endl;
	map<char,vector<production>>::iterator it = i.production_list.begin();
	while(it!=i.production_list.end()){
		cout<<it->first<<":\t";
		int n= it->second.size();
		for(int i1=0;i1<n;i1++){
			cout<<it->second[i1].s<<"\t";
			if(i1==n-1)cout<<endl;
		}
		it++;
	}

}

bool find_in_queue(queue <char>Q1,char tt){
	while(!Q1.empty()){
		if(Q1.front()==tt)return true;
		Q1.pop();
	}
	return false;


}

item make_item(char lhs1,production parent_production,int n){
	//Queue for closer property
	queue <char>Q;
	bool flag=false;// no need
	//creating item
	item temp_item(n,parent_production);
	int k = parent_production.dot;
	char x = parent_production.s[k];

	//inserting parent production in list
	vector <production>p_parent;
	p_parent.push_back(parent_production);
	temp_item.production_list.insert(make_pair(lhs1,p_parent));
	//cheking for closer property
	if(!is_terminal(x))
		Q.push(x);
	while(!Q.empty()){
		//vector of productions of x symbol
		vector<production> vector_production_for_item;
		x = Q.front();
		//insert that production of x from list and having dot zero
		map<char,std::vector<string>>::iterator it = ip.find(x);
		int size_of_vector_string = it->second.size();
		production temp_p;

		for(int i=0;i<size_of_vector_string;i++){
			temp_p.s = it->second[i];
			temp_p.dot = 0;
			vector_production_for_item.push_back(temp_p);
			char tt = it->second[i][0];
			if(!is_terminal(tt)&&!find_in_queue(Q,tt))Q.push(tt); 
		}

		temp_item.production_list.insert(make_pair(x,vector_production_for_item));
		Q.pop();

	}

	//items.push_back(temp_item);
	//print_item(temp_item);

	return temp_item; 

}

void make_further(item i){

	map<char,vector<production>>::iterator it = i.production_list.begin();
	while(it!=i.production_list.end()){
		cout<<it->first<<":\t";
		int n= it->second.size();
		for(int i1=0;i1<n;i1++){
			// cout<<it->second[i1].s<<"\t";
			// if(i1==n-1)cout<<endl;
			
		}
		it++;
	}

}

void init_lr_zero(){
	char lhs = ip.find('X')->first;
	vector<production> vector_production;
	production start_production;
	start_production.s = ip.find('X')->second[0];
	start_production.dot = 0;
	vector_production.push_back(start_production);

	item i_zero = make_item('X',start_production,0);
	items.push_back(i_zero);
	print_item(i_zero);
	make_further(i_zero); 
}



/*----------------------------------------------------------*/

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







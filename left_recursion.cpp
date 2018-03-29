#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;



void check_recursion(string s)
{
	char nt,temp='x';
	bool flag=false;
	nt=s[0];
	//cout<<"non terminal is :"<<nt<<endl; 
	string line = s.substr(3,s.length()-1);
	vector <string> tokens;
	vector<string>z;
	stringstream check1(line);
	string intermediate;
     
    // Tokenizing w.r.t. space '->'
    while(getline(check1, intermediate, '|'))
    {
        tokens.push_back(intermediate);
    }

    //for(int i = 0; i < tokens.size(); i++)
      //  cout << tokens[i] << '\n';


    //checking for recursion
    
    for(int i=0;i<tokens.size();i++){
    	if(tokens[i][0]==nt){
    		flag = true;
    		break;
    	}

	}
	temp='^';
	if(flag==false){cout<<"no left recursion\n";return;}
	//removing left recursion
	if(flag==true){
		for(int i=0;i<tokens.size();i++){
			if(tokens[i][0]!=nt){
				tokens[i]+=nt;
				tokens[i]+=temp;
				//cout<<tokens[i]<<"\t";
			}
			else if(tokens[i][0]==nt){
				tokens[i]+=nt;
				tokens[i]+=temp;
				z.push_back(tokens[i]);
				tokens.erase(tokens.begin()+i);
				i--;
			}

		}
		//printing production
		cout<<nt<<"->";
		if(tokens.size()==0)cout<<endl;
     	for(int i = 0; i <tokens.size(); i++)
         	{	
         		if(i<tokens.size()-1)
         			cout << tokens[i] <<"|";
         		else
         			cout << tokens[i] <<endl;
         	}

        //printing z production
        cout<<nt<<"^->";
        for(int i=0;i<z.size();i++){
        	if(i<z.size()-1){

         			cout << z[i].substr(1,z[i].length()-1) <<"|";
         	}
         	else{
         		cout << z[i].substr(1,z[i].length()-1) <<"|";
         		cout<<"e"<<endl<<endl;
         	}	
         	
        }


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
	while(getline(file,s)){
		cout<<s<<endl;
		check_recursion(s);
	}

	file.close();
	return 0;

}
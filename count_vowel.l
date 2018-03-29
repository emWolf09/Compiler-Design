%{
	int count1=0,count2=0;
%}
%%
[aeiouAEIOU] {count1++;}
[a-zA-Z] { count2++;}
\n {return ;}
%%
int main(){
	printf("enter a string :\t");
	yylex();
	printf("count is %d  %d\n",count1,count2);
}
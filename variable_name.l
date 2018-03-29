%%
for |
if |
return |
else |
while |
void |
char |
int |
float |
goto |
double |
long |
unsigned |
auto |
struct |
break |
continue |
switch |
case |
enum |
register |
static |
typedef |
extern |
union |
const |
sort |
default |
sizeof |
volatile |
do |
signed { printf("%s is a keyword\n",yytext);}
[a-zA-Z_][a-zA-Z_0-9]* {printf("%s is a valid variable\n",yytext);}
[0-9][a-zA-Z_0-9]* {printf("%s is not a valid variable\n",yytext);}

%%
int main(){
	printf("enter a string having reserve word or variable :\t");
	yylex();
}
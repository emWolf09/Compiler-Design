#include<stdio.h>
#include<stdlib.h>

int main(void){
  int i,len=0,tmp,j;
  printf("Enter the integer : " );
  scanf("%d",&i );
  tmp = i;
  while(tmp > 0)
  {
      tmp = tmp / 10;
      len++;
  }
  char* p = (char*)malloc(len);
  for(j=0;j<len;j++)
  {
      tmp = i%10;
      i=i/10;
      p[len-j-1] = tmp +48 ;
  }
  printf("String : %s\n",p);
}

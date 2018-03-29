#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int alphanum(char);
int main(void){

  FILE *fp;
  char ch,chp = ' ';
  int count = 0;
  fp = fopen("prog.c", "r");
  if (fp == NULL)
  {
      printf("Cannot open file \n");
      exit(0);
  }
  ch = fgetc(fp);
  while (ch != EOF)
  {
      if(!isalnum(ch) && chp!=' ' && ch!= '\n')
      {
        if(ch =='\"'){
        ch = (char)fgetc(fp);
          while(ch!='\"'){
            ch = fgetc(fp);
          }
      }
      count++;
    }
      chp = ch;
      ch  = fgetc(fp);
  }
  fclose(fp);
  printf("Number of tokens = %d\n",count);
}

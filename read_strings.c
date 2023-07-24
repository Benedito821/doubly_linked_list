#include <stdio.h>
#include <stdlib.h>
#include "read_strings.h"
#include <string.h>
#define INITIAL_VAL 0
#define STRING_END(string,pos) (string+pos-1)

char* read_strings()
{
    int pos = INITIAL_VAL;
    char *string=NULL,ch=INITIAL_VAL;
    setbuf(stdin,NULL);
    do
    {
        ch=getchar();
        string=realloc(string,pos+1);
        *(string+pos)=ch;
        pos++;
    }
    while(ch!='\n');
    *(STRING_END(string,pos))='\0';
    return string;
}

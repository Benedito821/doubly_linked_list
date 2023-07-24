#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_END(command,pos) ( *(command+pos-1) )
#define ONLY_ONE_ELEMENT_IN_STRING(command) ( strlen(command)==1 )
#define CONVERT_COMMAND_TO_INT(command) ( *(command)-48 )
int read_command(void)
{
    int pos=0;
    char *command=NULL;
    register char ch=0;
    do
    {
        ch=getchar();
        command=realloc(command,pos+1);
        *(command+pos)=ch;
        pos++;
    }
    while(ch!='\n');
    STRING_END(command,pos)='\0';
    if(ONLY_ONE_ELEMENT_IN_STRING(command))
        return CONVERT_COMMAND_TO_INT(command);
    return -1;
}

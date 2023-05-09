#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char termos[20][250];
int slot_vazio = 0;

void removeVirgula(char str[])
{
	int i =8, j=0;
	while(str[i] != '>')
	{
		if(str[i] == ',')
		{
			i++;
			slot_vazio++;
			j=0;
			continue;
		}
		termos[slot_vazio][j] = str[i];
		i++;
		j++;
	}
}

int main()
{
	char frase[256] = "<termos:Steven,Ana>";
	removeVirgula(frase);
	
	printf("%s\n", termos[0]);
	printf("%s\n", termos[1]);
	
	return 0;
}

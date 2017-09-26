#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_PASSWORD_LEN	32

int main()
{
	char password[MAX_PASSWORD_LEN];
	char *c;

	while(fgets(password, MAX_PASSWORD_LEN, stdin) != NULL)
	{
		// remove \n and \r at the end of lines
		c = password + strlen(password) - 1;
		while(isspace(*c)) {
			*c = 0;
			c--;
		}
		printf("%s\n", password);
	}

	return 0;
}

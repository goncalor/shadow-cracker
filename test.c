#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <crypt.h>

#define MAX_PASSWORD_LEN    64

int main()
{
	char password[MAX_PASSWORD_LEN];
	char *encr_pass;
	char *c;

	while(fgets(password, MAX_PASSWORD_LEN, stdin) != NULL)
	{
		// remove \n and \r at the end of lines
		c = password + strlen(password) - 1;
		while(isspace(*c)) {
			*c = 0;
			c--;
		}

		encr_pass = crypt(password, "$1$abcdefg/");
		printf("%s, %s\n", password, encr_pass);
	}
	free(encr_pass);

	return 0;
}

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
	char *encr_pass = NULL;
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
		// check return value
		printf("%s, %s\n", password, encr_pass);
		// the returned string is of the form $id$salt$hash
		if(strcmp(encr_pass + strlen("$1$abcdefg/") + 1, "suq287zk65PfH155HSD.R0") == 0)
		{
			printf("Found a password for %s: %s\n", encr_pass, password);
			exit(0);
		}
	}

	if(encr_pass != NULL)
		free(encr_pass);

	return 0;
}

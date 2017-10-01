#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <crypt.h>

#define MAX_PASSWORD_LEN    64

int main(int argc, char **argv)
{
	char password[MAX_PASSWORD_LEN];
	char *encr_pass = NULL;
	char *c;

	if(argc < 2) {
		printf("Usage: %s <$id$salt$hash>", argv[0]);
		exit(1);
	}

	int ret;
	int id;
	char salt[64], hash[128];
	// TODO: fix this horrible buffer overflow
	ret = sscanf(argv[1], "$%d$%[^$]$%s", &id, salt, hash);
	printf("%d", ret);
	if(ret<3) {
		puts("Bad argument");
		exit(1);
	}
	if(id != 1 && id != 5 && id != 6) {
		puts("Unknown hash");
		exit(1);
	}
	char id_and_salt[64];
	// don't trust this length. what if ID 2a becomes valid?
	int id_and_salt_len = 1+1+1+strlen(salt);
	strncpy(id_and_salt, argv[1], id_and_salt_len);
	id_and_salt[id_and_salt_len] = 0; // add terminating null byte
	// puts(id_and_salt);


	while(fgets(password, MAX_PASSWORD_LEN, stdin) != NULL)
	{
		// remove \n and \r at the end of lines
		c = password + strlen(password) - 1;
		while(isspace(*c)) {
			*c = 0;
			c--;
		}

		encr_pass = crypt(password, id_and_salt);
		// FIXME: check return value
		// printf("%s, %s\n", password, encr_pass);
		// the returned string is of the form $id$salt$hash
		if(strcmp(encr_pass + id_and_salt_len + 1, hash) == 0)
		{
			printf("Found a password for %s: %s\n", encr_pass, password);
			exit(0);
		}
	}

	if(encr_pass != NULL)
		free(encr_pass);

	return 0;
}

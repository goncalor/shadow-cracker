#include <stdio.h>

#define MAX_PASSWORD_LEN	32

int main()
{
	char password[MAX_PASSWORD_LEN];

	while(fgets(password, MAX_PASSWORD_LEN, stdin) != NULL)
	{
		sscanf(password, "%s", password);
		printf("%s\n", password);
	}

	return 0;
}

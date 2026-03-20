#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void)
{
	char *cmd1[] = {"/bin/ls", NULL};
	char *cmd2[] = {"/bin/cat", NULL};
	char **cmds[] = {cmd1, cmd2, NULL};

	int ret = picoshell(cmds);

	printf("Retorno do picoshell: %d\n", ret);
	return(0);
}
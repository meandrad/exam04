#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const *argv, char type)
{
	int fd[2];
	int pid;

	if(!file || !argv || (type != 'r' && type != 'w') || pipe(fd))
		return(-1);
	if((pid = fork()) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return(-1);
	}
	if(!pid)
	{
		if(dup2(fd[type == 'r'], type == 'r') == -1)
			exit(1);
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	close(fd[type == 'r']);
	return(fd[type != 'r']);
}
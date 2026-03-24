#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i = 0, fd[2], pid, tmp_fd  = -1;

	while(cmds[i])
	{
		if(cmds[i + 1] && pipe(fd))
		{
			if(tmp_fd != -1)
			{
				close(tmp_fd);
				return(1);
			}
		}
		if((pid = fork()) == -1)
		{
			if(tmp_fd != -1) close(tmp_fd);
			if(cmds[i + 1]) {close(fd[0]); close(fd[1]);}
			return(1);
		}
		if(pid == 0)
		{
			if(tmp_fd != -1 && dup2(tmp_fd, 0) == -1) exit(1);
			if(cmds[i + 1] && dup2(fd[1], 1) == -1) exit(1);
			if(tmp_fd != -1) close(tmp_fd);
			if(cmds[i + 1]) {close(fd[0]); close(fd[1]);}
			execvp(*cmds[i], cmds[i]);
			exit(1);
		}
		if(tmp_fd != -1) close(tmp_fd);
		if(cmds[i + 1]) {close(fd[1]); tmp_fd = fd[0];}
		i++;
	}
	while(wait(NULL) != -1)
	return(0);
}
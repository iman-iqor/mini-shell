#include "../includes/minishell.h"

#include "../includes/minishell.h"

void	handle_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


	
int do_heredoc(char *delimiter)
{
	int pipefd[2];
	pid_t pid;
	int status;
	char *line;
	if(pipe(pipefd) == -1)
		return -1;
	pid = fork();
	if(pid == -1)
		return -1;
	
	if(pid == 0)
	{
		handle_heredoc_signals();//i dont have this yet i need to create it and understand it
		close(pipefd[0]);
		while(1)
		{
			line = readline(">");
			if(!line || !ft_strcmp(line,delimiter))
			{
				free(line);
				break;
			}
			write(pipefd[1],line,ft_strlen(line));
			write(pipefd[1],"\n",1);
		}
		close(pipefd[1]);
		waitpid(pid,&status,0);//why did we gave it status as argument and it could hold garbage data
		restore_signals();//i dont have i need to create and understand it as will
		return(pipefd[0]);
	}
}

int heredoc(t_list *list)
{
	int fd;
	fd = -1;//because -1 means that is this fd is not valid 

	while(list->input_file)
	{
		if(list->input_file->flag == 1)
		{
			if(fd != -1)
				close(fd);//because -1 is an invalid file descriptor and But for the next heredoc (if multiple are present), you first close the previous pipe read end (fd) before overwriting it with the next heredoc’s read end.If you don’t close the previous fd, you'll leak a file descriptor.
			fd = do_heredoc(list->input_file->file_name);//i will send to do_heredoc a delimiter
			if(fd == -1)
				return -1;//if do_heredoc failed in piping or something else
		}
		//i think i need an else statement here if there is no flag ==0 i ll open the the normal input file to get the fd
		list->input_file=list->input_file->next;//to loop all over the  files 
	} 
	list->fd=fd;//i will update the fd value in the list because i ll need after to dup it so the execve will use it
}

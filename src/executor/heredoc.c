#include "../includes/minishell.h"

void sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        // write(1, "\n", 1);
		printf("signal\n");
        exit(130);
    }
}

void handle_heredoc_signals(void)
{
    signal(SIGINT, sigint_handler);  // Use our custom handler
    signal(SIGQUIT, SIG_IGN);
}



int do_heredoc(char *delimiter)
{
    int pipefd[2];
	
    pid_t pid;
    int status;
    char *line;

    if (pipe(pipefd) == -1)
        return (-1);
    
    pid = fork();
    if (pid == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }
    
    if (pid == 0)
    {
        handle_heredoc_signals();
        close(pipefd[0]);
        while (1)
        {
            line = readline(">");
            if (!line)  // Handle EOF (Ctrl+D)
            {
                close(pipefd[1]);
                exit(0);
            }
            
            if (!ft_strcmp(line, delimiter))
            {
                free(line);
                close(pipefd[1]);
                exit(0);  // Exit immediately when delimiter is found
            }
            
            write(pipefd[1], line, ft_strlen(line));
            write(pipefd[1], "\n", 1);
            free(line);
        }
    }
    
    // Parent process
    close(pipefd[1]);  // Close write end in parent
	// printf("uihiuhd\n");
    waitpid(pid, &status, 0);
	// printf("jiuh %d\n",status);

    
    

    // return -1;
    return (pipefd[0]);
}

int heredoc(t_list *list)
{
    int fd;
    t_file *tmp;
    
    if (!list || !list->input_file)
        return (0);
    
    fd = -1;
    tmp = list->input_file;
    
    while (tmp)
    {
        // Close previous file descriptor before opening a new one
        if (fd != -1)
        {
            close(fd);
            fd = -1;
        }

        if (tmp->flag == 1)  // heredoc
        {
            fd = do_heredoc(tmp->file_name);
            if (fd == -1)
            {
                ft_putstr("heredoc failed\n");
                return (-1);
            }
        }
        else  // regular input file
        {
            fd = open(tmp->file_name, O_RDONLY);
            if (fd == -1)
            {
                perror(tmp->file_name);
                return (-1);
            }
        }
        
        tmp = tmp->next;
    }
    
    list->fd = fd;  // Store the final file descriptor in the list
    return (0);
}

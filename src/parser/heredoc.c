// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include "minishell.h"

// #define HEREDOC_PROMPT "> "

// // Returns 0 on success, sets *heredoc_fd to read end of pipe
// int handle_heredoc(const char *delimiter, int *heredoc_fd)
// {
//     int pipefd[2];
//     char *line;

//     if (!delimiter || pipe(pipefd) == -1)
//         return ERROR_GENERIC;

//     while (1)
//     {
//         line = readline(HEREDOC_PROMPT);
//         if (!line)  // Ctrl+D
//         {
//             write(2, "warning: heredoc delimited by end-of-file\n", 43);
//             break;
//         }

//         if (strcmp(line, delimiter) == 0)
//         {
//             free(line);
//             break;
//         }

//         write(pipefd[1], line, strlen(line));
//         write(pipefd[1], "\n", 1);
//         free(line);
//     }

//     close(pipefd[1]);        // close write end
//     *heredoc_fd = pipefd[0]; // return read end
//     return 0;
// }


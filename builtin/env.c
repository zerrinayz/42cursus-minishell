
#include "../minishell.h"

void env(t_program *program, t_lexer ***parser_input)
{
    t_list *current;
    int i;
    i = 0;

    while (parser_input[0][i] != NULL && ft_strncmp(parser_input[0][i]->cmd, "env", ft_strlen("env")) == 0 && parser_input[0][i]->cmd[3] == '\0')

        i++;
    if (parser_input[0][i] == NULL)
    {
        current = program->envp_list;
        while (current != NULL)
        {
            printf("%s=%s\n", (char *)current->key, (char *)current->content);
            current = current->next;
        }
    }
    else
        printf("env: %s No such file or directory\n", parser_input[0][i]->cmd);
}
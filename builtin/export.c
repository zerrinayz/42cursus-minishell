
#include "../minishell.h"

static void export_env(t_program *program)
{
    t_list *list;
    list = program->envp_list;
    while (list != NULL)
    {

        printf("declara -x %s=%s\n", (char *)list->key, (char *)list->content);
        list = list->next;
    }
}

void export(t_program *program, t_lexer ***parser_input)
{
    if (parser_input[0][1] == NULL)
    {
        export_env(program);
    }
}

#include "../minishell.h"

//  echo "$HOME"'$HOME''"$HOME"' birden fazla dolarlı ise dolar olarak ----dolar
// setle . tırnak temizlerken birden fazla varsa içini tek tek temizle(execde)

//
int count_dolar(char *parser_input)
{
    int i = 0;
    int count = 0;

    while (parser_input[i])
    {
        if (parser_input[i] == '$')
            count;
        i++;
    }
    return(count);
}

void dolar_handler(t_program *program)
{
    int i = 0;
    int j = 0;

    while (program->parser_input[i])
    {
        j = 0;
        while (program->parser_input[i][j])
        {
            if (program->parser_input[i][j]->key == 5 && count_dolar(program->parser_input[i][j]) > 1)
            {
            }
            j++;
        }
        i++;
    }
}
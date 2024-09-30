#include "minishell.h"

void dolar_free(char *env_str, char *after_dolar)
{
	if (env_str[0] != '\0')
		free(env_str);
	if (after_dolar)
		free(after_dolar);
}
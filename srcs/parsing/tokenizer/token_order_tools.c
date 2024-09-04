
#include "minishell.h"

void	filename_error(char *name, char *message, t_shell *gear_5, int flag)
{

	if (!message)
		return ;
	if (flag == 1)
	{
		error(name);
		error(": ");
		error(message);
		error("\n");
		gear_5->exit_status = 1;
	}
	else if (flag == 2)
	{
		error(message);
		error("\n");
		gear_5->exit_status = 2;
	}
}
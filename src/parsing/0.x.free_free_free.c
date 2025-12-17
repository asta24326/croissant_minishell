/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.x.free_free_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:02:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 16:14:30 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* main data storage */
typedef struct	s_shell
{
	char	*prompt;		//program run time
	int		pipe_count;		//always set to NULL per default and at end of execution
	int		**pipes;		//always set to NULL per default and at end of execution
	char	**env;			//program run time
	t_cmd	*cmd;			//always set to NULL per default and at end of execution
	int		exit_status;	//program run time
	pid_t	shell_pid;		//program run time
}	t_shell;


/* to be freed at end of program runtime */

// 0.2.
// HISTORY		void rl_clear_history(void)
// PROMPT		free(char *prompt)

// 1.1.
// MINISHELL		free(t_shell minishell)



/* to be freed at end of pipeline execution */

// 2.1.
// CMD-STR-ARR		free(arr) - from ft_split
// LINKED LIST		free_stack

// 2.2.
// ARGS-ARRAY		free_stack

// 3.1. && 3.2.
// STRINGS (for args array)	freed with 2.2. free stack



// -----------------------------------------------------
// adjust to cmd_list
// void	free_stack(t_stack **stack)
// {
// 	t_node	*tmp;

// 	if (!stack || !*stack)
// 		return ;
// 	while (*stack)
// 	{
// 		tmp = (*stack)->next;
// 		free(*stack);
// 		*stack = tmp;
// 	}
// 	*stack = NULL;
// }

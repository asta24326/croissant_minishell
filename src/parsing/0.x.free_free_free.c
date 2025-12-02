/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.x.free_free_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:02:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/02 13:46:20 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* to be freed at end of program runtime */

// 0.2.
// HISTORY		void rl_clear_history(void)
// PROMPT		free(prompt)

// adjust to cmd_list
void	free_stack(t_stack **stack)
{
	t_node	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

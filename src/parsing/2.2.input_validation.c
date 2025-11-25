/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.2.input_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:15:50 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/25 19:57:26 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRUCTURE FOR INPUT VALIDATION */

START OF STRING

(0) whitespaces
	- always and at any time loop through whitespaces
	- none of them is to be passed to execution

(1) check for built-in commands (except for echo)
	- cd >> pass: cmd + string after cmd (should be path), cut off eveything after
	- pwd, export, unset, env, exit >> pass: cmd, cut off everything after
	END

(2) syntax check pipes
	- if not valid: END
	- pass count of cmds in struct t_shell

_______
SPLIT STRING INTO ARRAY OF STRINGS (DELIMITER = PIPE)
FOR EACH SUBSTRING:

(3) extract redirections
	- syntax check redirs
		- if not valid: END
	- fill and pass: struct t_redirs

(4) check if cmd is valid according to definition in 2.0
	>> if not valid: END
	- if valid:
		- if "echo" >> pass: cmd + flag + array of arguments (redirs are not arg of "echo"!)

(5) flags?

(6) env arg?

(7) arguments belonging to command?

(8) quotes? >> needs to be checked WAY earlier

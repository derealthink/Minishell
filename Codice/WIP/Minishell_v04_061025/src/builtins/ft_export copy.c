/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/14 16:50:03 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int handle_assignment_export(t_minishell *shell, char *arg, char *equals_sign);
static int handle_simple_export(t_minishell *shell, char *arg);
static int ft_print_export_list(t_minishell *shell);
static char *ft_strndup(const char *s, size_t n);

int ft_export(t_minishell *shell, char **args)
{
    int i;
    char *equals_sign;

    if (!shell)
        return (1);
    shell->last_exit_status = 0;

    // 1. HANDLE NO ARGUMENTS (Export display)
    if (!args[1])
    {
        // ASSUMPTION: You have a function to print the env list
        return (ft_print_export_list(shell)); 
    }

    // 2. ITERATE OVER ARGUMENTS
    i = 1;
    while (args[i])
    {
        // Find the FIRST '=' sign to correctly distinguish 'NAME' vs 'NAME=VALUE'
        equals_sign = ft_strchr(args[i], '=');

        if (equals_sign) // Case: NAME=VALUE or NAME=
        {
            // You need a specific function to handle assignment parsing
            if (handle_assignment_export(shell, args[i], equals_sign) != 0)
            {
                // handle error (like MALLOC failure)
                return (shell->last_exit_status);
            }
        }
        else // Case: ONLY NAME (Marking for export/Creation)
        {
            if (handle_simple_export(shell, args[i]) != 0)
            {
                // handle error (like MALLOC failure)
                return (shell->last_exit_status);
            }
        }
        i++;
    }
    return (shell->last_exit_status);
}

// Handles args like "VAR=value" or "VAR="
static int	handle_assignment_export(t_minishell *shell, char *arg, char *equals_sign)
{
    // Calculate name_len to isolate the name part
    size_t  name_len = equals_sign - arg;
    char    *name;
    char    *value;
    int     ret;

    // Use strndup or similar to safely extract the name
    // IMPORTANT: Assuming you have ft_strndup, or use MALLOC + strncpy + '\0'
    name = ft_strndup(arg, name_len); 
    if (!name) return (-1); // MALLOC failure

    // Value starts immediately after the '=' sign
    value = equals_sign + 1;

    // Check identifier validity on the extracted name
    if (ft_is_valid_name(name) == 0)
    {
        // You MUST free the allocated name here
        print_quoted_error("export", name, "not a valid identifier");
        free(name); 
        shell->last_exit_status = 1;
        return (1); // 1 = identifier error
    }

    // Update the environment list (or create if it doesn't exist)
    ret = update_env_var(shell, name, value); 
    free(name); // Always free the temporary name buffer

    return (ret);
}

// Handles args like "VAR"
static int handle_simple_export(t_minishell *shell, char *arg)
{
    // Check identifier validity directly on the argument
    if (ft_is_valid_name(arg) == 0)
    {
        print_quoted_error("export", arg, "not a valid identifier");
        shell->last_exit_status = 1;
        return (1);
    }
    
    // For 'export NAME', if the variable doesn't exist, it should be CREATED 
    // with a NULL/empty value, ready to be exported.
    // Use your existing logic, but ensure it handles the NULL value case correctly:

    // Update/create the variable with a NULL value (no change to value)
    return (update_env_var(shell, arg, NULL)); 
}

// Prints the exported variables as 'declare -x NAME="value"'
static int ft_print_export_list(t_minishell *shell)
{
    t_new_envp *current;
    
    // Assuming your env list is sorted for standard compliance (optional)
    // sort_env_list(shell->env_list); 

    current = shell->env_list->head;
    while (current)
    {
        // Only print if the variable is marked as 'exported' (if you have a flag)
        // Since Minishell often treats all vars as exported, we skip the check
        
        // Print: declare -x NAME="value"
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(current->name, STDOUT_FILENO);
        
        if (current->value && current->value[0] != '\0')
        {
            // Print: ="value" (note the quotes)
            ft_putstr_fd("=\"", STDOUT_FILENO);
            ft_putstr_fd(current->value, STDOUT_FILENO);
            ft_putstr_fd("\"", STDOUT_FILENO);
        }
        // If value is NULL or empty, it prints: declare -x NAME
        
        ft_putstr_fd("\n", STDOUT_FILENO);
        
        current = current->next;
    }
    return (0);
}

#include <stdlib.h> // For malloc
#include <string.h> // For size_t (though you likely have your own)

/*
 * Duplicates a string, but copies at most 'n' characters.
 * Always null-terminates the resulting string.
 */
static char *ft_strndup(const char *s, size_t n)
{
    size_t  len;
    char    *dup;
    size_t  i;

    if (!s)
        return (NULL);

    // 1. Calculate the actual length to copy (min(n, length of s))
    len = 0;
    while (s[len] != '\0' && len < n)
        len++;

    // 2. Allocate space for the string plus the null terminator
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);

    // 3. Copy the characters
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }

    // 4. Null-terminate the new string
    dup[len] = '\0';

    return (dup);
}

static int	print_env_sort(t_minishell *shell)
{
	char	**sort_envp;

	sort_envp = env_list_array(shell->env_list);
//	printf("SORT_ENVP!\n\n");
//	ft_env(shell, sort_envp);
	array_clear(sort_envp);
	return (shell->last_exit_status = 0);
}

/*
static int	invalid_identifier(t_minishell *shell, char **new_var)
{
	print_quoted_error("export", new_var[0], "not a valid identifier");
	array_clear(new_var);
	shell->last_exit_status = 1;
	return (1);
}

static int	print_env_sort(t_minishell *shell)
{
	char	**sort_envp;

	sort_envp = env_list_array(shell->env_list);
	printf("SORT_ENVP!\n\n");
	ft_env(shell, sort_envp);
	array_clear(sort_envp);
	return (shell->last_exit_status = 0);
}

static void	print_list(t_minishell *shell)
{
	t_new_envp	*current;

	current = shell->env_list->head;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}*/

// https://docs.vultr.com/how-to-set-environment-variables-in-bash-on-linux

/*
int ft_export(t_minishell *shell, char **args)
{
	t_new_envp	*current;
	t_new_envp	*new;
	char		**new_var;
	int			found;
	int			i;

	if (!shell || !args)
		return (shell->last_exit_status = 1);
	i = 1;
	while (args[i])
	{
		new_var = ft_split(args[i], '=');
		if (ft_is_valid_name(new_var[0]) ==  0)
		{
			print_quoted_error("export", new_var[0], "not a valid identifier");
			array_clear(new_var);
			shell->last_exit_status = 1;
			i++;
			continue ;
		}
		current = shell->env_list->head;
		found = 0;
		while (current)
		{
			if (ft_strcmp(new_var[0], current->name) == 0 )
			{
				free(current->value);
				if (new_var[1])
					current->value = strdup(new_var[1]);
				else
					current->value = strdup("");
				found = 1;
				break ;
			}
			current = current->next;
		}
		if (found == 0 && new_var[1] != NULL)
		{
			new = new_env_node(new_var);
			if (!new)
				return (shell->last_exit_status = -1);
			list_add_back(&shell->env_list->head, new);
			shell->env_list->len_envp++;
		}
		array_clear(new_var);
		i++;
	}
	if (shell->last_exit_status != 1)
		shell->last_exit_status = 0;
	return (shell->last_exit_status);
}


int	ft_export(t_minishell *shell, char **args)
{
	char		**new_var;
	int			i;

	if (!shell || !args)
		return (shell->last_exit_status = 1);
	shell->last_exit_status = 0;
	i = 1;
	if (!args[1])
		return (print_env_sort(shell));
	while (args[i])
	{
		new_var = ft_split(args[i], '=');
		if (ft_is_valid_name(new_var[0]) == 0)
		{
			invalid_identifier(shell, new_var);
			i++;
			continue ;
		}
		if (update_env_var(shell, new_var[0], new_var[1]) == -1)
		{
			array_clear(new_var);
			return (shell->last_exit_status = -1);
		}
		array_clear(new_var);
		i++;
	}
print_list(shell);
	return (shell->last_exit_status);
}
*/
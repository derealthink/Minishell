#ifndef PARSING_H
#define	PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef	enum e_state
{
	STATE_NORMAL,
	STATE_SQUOTES,
	STATE_DQUOTES
}	t_state;

typedef	struct s_token
{
	char	*value;
	struct	s_token	*next;
}	t_token;

typedef	struct l_table
{
	t_token	*head;
	t_token	*tail;
}	t_table;


char	**ft_split(char *str, char del);
int		is_space(char c);
t_token	*new_token(char *value);
t_table *init_list(void);
int		is_quotes(char c);


#endif
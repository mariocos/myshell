#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>
# include <stdarg.h>

/*-------------------*/
/*     structs       */
/*-------------------*/
typedef struct s_mini
{
	char	*input;
	struct s_token	*token;
	struct s_env	*env;
	struct s_env	*export;
}		t_mini;

typedef struct s_token
{
	int		token_type;
	char	*token;
	int		index;
	struct s_token *previous;
	struct s_token *next;
}			t_token;

typedef struct s_env
{
	char	*var;
	char	*var_name;
	char	*var_value;
	bool	exported;
	struct s_env	*next;
}	t_env;

typedef enum e_t_types
{
	RED_IN = 1,
	RED_OUT,
	RED_APP,
	HERE_DOC,
	PIPE,
	CMD,
	ARG,
	WORD,

}		t_e_types;

/*----------*/
/*  quotes  */
/*----------*/
bool	in_quote(const char *input, int index);
/*-------------------------------------------*/

/*----------*/
/*  split   */
/*----------*/
int		count_words(char const *s);
int		wordlen(char *s);
char	**special_split(char const *s);
/*-----------------------------------*/


/*----------*/
/*   is     */
/*----------*/
int	ft_isspace(char c);
int	ft_isalpha(char c);
int	ft_isoperator(char *str, int index);
int	ft_isdigit(char c);
/*-------------------*/


/*----------*/
/*  libft   */
/*----------*/
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*--------------------------------------------------------------*/

/* malloc */
void	*safe_malloc(size_t size);
/*------------------------------*/

/*---------------*/
/*   tokenizer   */
/*---------------*/
t_token	*init_token(char *str);
t_token	*input_split_to_token(char **words);
int	get_token_type(char *str);
int	count_strs(char **words);//might change file
void	token_add_back(t_token *start, t_token *add);
/*-------------------------------------------------*/

/*---------------*/
/*  re tokenizer */
/*---------------*/
t_token	*re_tokenize(t_token *start);
bool	needs_retoken(char *str);
t_token	*token_separate(t_token *token);
t_token	*token_reasign(t_token *t);
t_token	*extract_operator(t_token *t);
t_token	*extract_word(t_token *token);
/*----------------------------------------*/

/*--------*/
/*  free  */
/*--------*/
void	free_token(t_token *t);
void	free_token_list(t_token *start);
void	free_var(t_env *var);
void	free_env_list(t_env *start);
/*---------------------------*/

/*-----------*/
/*   parse   */
/*-----------*/
bool	first_parse(t_token *start);
bool	parse_quotes(const char *input);
/*---------------------*/


/*---------*/
/*  envp   */
/*---------*/
t_env	*get_env(char **envp);
void	var_add_back(t_env *start, t_env *add);
t_env	*init_var(char *str);
/*-------------------------------------------*/


/*-------------*/
/*   variables */
/*-------------*/
int	advance_var(char *str, int i);
void	var_replace(t_token *t, char *var_value);
t_token	*expand_vars(t_token *start);

/*---------------------------------*/

/*------------------*/
/*    print utils   */
/*------------------*/
void	print_token(t_token *token);
void	print_double_array(char **words);
void	print_token_list(t_token *start);
void	print_envp(t_env *env);
/* to be removed ----------------------*/


/*------------------*/
/*      export	    */
/*------------------*/
int		export(char *str, t_env *start, bool call);
void	chk_not_exported(t_env *start);
//void	chk_export_var(char *str, t_env *start);

#endif
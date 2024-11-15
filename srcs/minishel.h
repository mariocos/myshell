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
#include <readline/readline.h>
#include <readline/history.h>

/*-------------------*/
/*     structs       */
/*-------------------*/
typedef struct s_mini
{
	char	*input;
	struct s_token	*token;
	struct s_env	*env;
	struct s_env	*export;
	struct s_pipex	*pipex_list;

}		t_mini;

typedef struct s_pipex
{
	char	**red_out;
	char	**red_in;
	char	*path;
	char	**cmd;
	struct s_pipex	*next;
	struct s_pipex *previous;
}			t_pipex;

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

typedef enum e_rev_op
{
	OP_OUT = -1,
	OP_IN = -2,
	OP_PIPE = -3,
	OP_VAR = -4,
}		t_rev_op;

typedef struct	s_history
{
	int				index;
	char			*input;
	struct s_hisory *next;
	struct s_hisory *previous;
}		t_history;

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
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dst, const char *src, char	*ret);
char	*ft_strjoin(char const *s1, char const *s2);
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
void	free_double_array(char **words);
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
bool	needs_expand(t_token *t);
int	var_name_len(char *str, int i);
int	expanded_len(t_token *t, char *var_value);
char	*get_var_name(t_token *t);
char	*get_var_value(t_env *env, char *var_name);
void	do_expand(t_token *t);

void	expand_var(t_token *t, char *var);
void	expand_vars_loop(t_token *start);
/*---------------------------------*/

/*------------------*/
/*    print utils   */
/*------------------*/
void	print_token(t_token *token);
void	print_double_array(char **words);
void	print_token_list(t_token *start);
void	print_envp(t_env *env);
void	print_pipex_list(t_pipex *start);

/* to be removed ----------------------*/

/*----------*/
/*   mini   */
/*----------*/
t_mini	*mini_call(void);
void	mini_init(char **env);
/*-----------------------*/

/*-----------*/
/*   tilde   */
/*-----------*/
void	expand_tilde(t_token *t);
void	tilde_loop(t_token *t);
/*-----------------------------*/

/*-------------*/
/*   input     */
/*-------------*/
void	input_handle(void);
/*-----------------------*/

/*------------------*/
/*  token_to_pipex  */
/*------------------*/
int	ft_find_pipes(t_token *t);
void	tokens_to_pipex(t_token *t);
int	array_word_counter(char	**words);
char	**add_to_double_char_array(char **words, char *word);
void	free_double_char_array(char **words);
void	populate_pipex(t_token *t, t_pipex *start);
char	**add_handler(char **words, char *word, char *prefix);

/*-----------------------------------*/







/*-------------*/
/* errores     */
/*-------------*/
void	syntax_error(void);
/*-------------------------*/




#endif
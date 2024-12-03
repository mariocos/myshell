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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>

/*-------------------*/
/*     structs       */
/*-------------------*/
typedef struct s_mini
{
	char			*input;
	struct s_token	*token;
	struct s_env	*env;
	struct s_env	*export;
	struct s_pipex	*pipex_list;
	int				exit_status;

}		t_mini;

typedef struct s_pipex
{
	int		pid;//TODO:var not yet in init!
	int		pipe[2];
	int		has_doc;//maybe bool
	int		doc_pipe[2];
	int		out_fd;
	int		in_fd;
	bool	last_child;
	char	*path;
	char	**red_out;
	char	**red_in;
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


/*------------*/
/*    gnl     */
/*------------*/
int		ft_linelen(char *str);
void	ft_buffer_shift_left(char *Buffer, int move_size);
char	*ft_special_join(char *str, char *Buffer);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#endif
/*-----------------------------------------------------------*/

/*----------*/
/*  quotes  */
/*----------*/
int		advance_quotes(char *str, int i);
bool	in_quote(const char *input, int index);
int		remove_quote_len(char *str);
bool	in_squote(const char *input, int index);

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
int		ft_isspace(char c);
int		ft_isalpha(char c);
int		ft_isoperator(char *str, int index);
int		ft_isdigit(char c);
int		ft_isquote(char c);
bool	is_builtin(t_pipex *p);
/*-------------------*/


/*----------*/
/*  libft   */
/*----------*/
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strcat(char *dst, const char *src, char	*ret);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_itoa(int n);
/*--------------------------------------------------------------*/


/* malloc */
void	*safe_malloc(size_t size);
/*------------------------------*/

/*---------------*/
/*   tokenizer   */
/*---------------*/
t_token	*init_token(char *str);
t_token	*input_split_to_token(char **words);
int		get_token_type(char *str);
int		count_strs(char **words);//might change file
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
void	free_double_char_array(char **words);
void	free_pipex_list(t_pipex *p);
void	clean_all(void);
void	clean_comand(void);
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
t_env	*init_minimal_env(void);
/*-------------------------------------------*/


/*-------------*/
/*   variables */
/*-------------*/
bool	needs_expand(t_token *t);
int		var_name_len(char *str, int i);
int		expanded_len(t_token *t, char *var_value);
char	*get_var_name(t_token *t);
char	*get_var_value(t_env *env, char *var_name);
void	do_expand(t_token *t);
void	expand_var(t_token *t, char *var);
void	expand_vars_loop(t_token *start);
char	*get_special_var(char *var_name);
int	is_special_expand(char *var_name);
void	unhide_expand(char *str);
void	hide_expand(char *str);
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
int	input_handle(void);
/*-----------------------*/

/*------------------*/
/*  token_to_pipex  */
/*------------------*/
int		ft_find_pipes(t_token *t);
void	tokens_to_pipex(t_token *t);
int		array_word_counter(char	**words);
char	**add_to_double_char_array(char **words, char *word);
void	free_double_char_array(char **words);
void	populate_pipex(t_token *t, t_pipex *start);
char	**add_handler(char **words, char *word, char *prefix);
void	remove_pipex_quotes(t_pipex *p);


//Command execution
char	*path_search(char *command, t_env *env);
char	*ft_strjointwist(char *path, char *cmd);
void	ft_free(char **argv);
char	**ft_split(char const *s, char c);
char	**env_to_double_chr_ptr(t_env	*env);
void	exec_if_builtin(t_pipex *process);
void	do_input_redir(t_pipex *p);
void	do_out_redir(t_pipex *p);
void	exec_if_builtin(t_pipex *process);
bool	is_builtin(t_pipex *p);
/*-----------------------------------*/


/*------------------*/
/*     signals	    */
/*------------------*/
void	handle_sigint(int sig);
void	setup_signal_handlers(void);
/*-------------------------*/



/*-------------*/
/* errores     */
/*-------------*/
void	syntax_error(void);
/*-------------------------*/




/*------------------*/
/*     builtins	    */
/*------------------*/
int		export(char *str, t_env *start, bool explicit_call);
void	unset(char *str, t_env **env);
void	env(t_env *env);
void	pwd(void);
void	cd(const char *new_dir, t_env *env);
void	echo(char **cmd);
void	exit_builtin(char *nbr);
/*-----------------------*/

/*------------------*/
/*     pipex	    */
/*------------------*/
void	close_fds(int *fds);
void	spawn_child(t_pipex *p);
void	process_handler(t_pipex *p);
void	child_process_new(t_pipex	*p);
void	ft_waitpid(int pid);
/*-----------------------*/

/*------------------*/
/*     redir	    */
/*------------------*/
void	do_input_redir(t_pipex *p);
void	do_out_redir(t_pipex *p);
void	prep_input_redir(t_pipex *p);
/*----------------------------------*/




/*----------------------*/
/*   unused functions   */
/*----------------------*/
// void	chk_env_var(char *str, t_env *start);
// void	chk_not_exported(t_env *start);
// void	echo(char *str, bool n_flag);
/*-----------------------*/

#endif

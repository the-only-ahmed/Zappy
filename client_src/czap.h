/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   czap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 13:02:47 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 09:14:07 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CZAP_H
# define CZAP_H

# include <stdio.h>
# include <libft.h>
# include <dirent.h>
# include <arpa/inet.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <sys/select.h>
# define BUF_SIZE 4096
# define FD_FREE 0
# define FD_SERV 1
# define FD_CLIENT 2

typedef struct		s_move
{
	int				dir;
	int				middle;
	int				ret;
	int				lat;
	int				avant;
	char			*request;
}					t_move;

typedef struct		s_usr
{
	int				sock;
	char			*name;
	char			*chan;
	struct s_usr	*next;
}					t_usr;

typedef struct		s_fd
{
	char			*name;
	int				bol;
	char			*chan_name;
	int				type;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
}					t_fd;

typedef struct		s_chan
{
	char			*name;
	t_usr			*usr;
	struct s_chan	*next;
}					t_chan;

typedef struct		s_env
{
	int				bol;
	int				tmp;
	char			buffer[4096];
	int				ptr_one;
	int				ptr_end;
	t_chan			*channel;
	t_usr			*usr;
	t_fd			*fds;
	int				port;
	int				maxfd;
	int				max;
	int				r;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_env;

typedef	struct		s_client
{
	char			*port;
	char			*host;
	char			*name;
}					t_client;

typedef struct		s_li
{
	char			*action;
	struct s_l		*sl;
}					t_li;

typedef struct		s_act
{
	char			*action;
	char			*reponse;
	struct s_act	*next;
}					t_act;

typedef struct		s_cond
{
	int				player;
	int				linemate;
	int				sibur;
	int				mendiane;
	int				phiras;
	int				deraumere;
	int				thystame;
}					t_cond;

typedef struct		s_inv
{
	int				nourriture;
	int				linemate;
	int				sibur;
	int				mendiane;
	int				phiras;
	int				deraumere;
	int				thystame;
}					t_inv;

typedef struct		s_play
{
	t_act			*temp;
	char			*searching;
	int				elevation_now;
	int				master;
	int				nb_req;
	t_act			*action;
	t_cond			condition[10];
	t_inv			inventaire;
	t_li			*to_do;
	int				request;
	int				curr;
	int				forking;
	int				elev;
	int				lvl;
	int				hungry;
	t_client		client;
	char			*coord;
	t_act			*ret_action;
	int				auth;
	int				move;
	int				wait;
	int				elev_n;
	int				ask;
}					t_play;

int					client_init(char *a, char *b);
void				check_fd(t_env *e, int sock);
void				ft_read2(t_env *e, int s);
void				init_fd(t_env *e, int sock);
void				ft_write2(t_env *e, int s);
void				pathfind(int t, t_play *p, int s);
void				ft_parse(char *buf, int s, t_play *p, t_env *e);
void				init_client(int s, t_env *e, t_client client);
t_act				*add_act(char *name, t_act *l);
t_act				*list_suppr(t_act *l);
t_play				init_play(int s, t_client c);
void				exec_list(t_play *p, int s);
void				exec_cmd_l(t_play *p, int s, char *cmd);
t_act				*add_first(char *c, t_act *l);
void				drop_res(t_play *p, char *buf, int s);
void				verif_up(int s, t_play *p);
void				deplacement_to(int i, int s, t_play *p, char *cmd);
t_act				*add_end_list(t_act *t, t_act *a);
void				give_pos(t_play *p, int s);
void				end_alg(t_play *p);
int					count_liste(t_act *l);
void				print_list(t_act *l);
void				parse_client(char **a, int ac, t_client *client);
void				ft_loop(int s, t_env *e, t_play p);
void				check_fd2(t_env *e, int s, t_play *p);
t_cond				init_cond3(int lvl, t_cond c);
t_cond				init_cond2(int lvl, t_cond c);
void				print_list(t_act *l);
int					count_list_act(t_act *l);
int					count_tab(char **tab);
void				find_mid(int i, t_move *m);
void				maj_inv(t_play *p, char *b);
void				recup_inv(int s, t_play *p);
void				drop_action(int s, t_play *p, char *b);
int					verif_list2(char *buf, int s, t_play *p);
int					verif_list3(char *buf, int s, t_play *p, t_env *e);
int					verif_list4(char *buf, int s, t_play *p);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:23:23 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/10 21:29:15 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env // Estrutura principal do programa
{
	t_param			*param;
	t_gc			*gc;	//
	t_philosopher	**philo; //Array que vai segurar cada filósofo
}	t_env;

typedef struct s_param
{
	size_t			nb_philo;		//Quantiade de filósofs
	size_t			time_die;		//tempo para morte de cada um
	size_t			time_eat;		//tempo de refeição
	size_t			time_sleep;		//tempo de dormir
	size_t			nb_to_eat;		//quantidade de refeições feitas (isso não deveria ser individual?)
	size_t			start_time;		//tempo de inicio
	sem_t			*sem_forks;		//array com todos os garfos que no caso do bonus são semafóros
	sem_t			*sem_state_end;	//? possívelmente o "mutex" de lock
	sem_t			*sem_printf;	//? possívelmente o "mutex" de write
	sem_t			*sem_print_died; //? aparentemente a mesma coisa porem para escrever filósofos 
	volatile int	state_end;	//? possívelmente uma variáve que vai servir como binario 0 == alive | 1 == dead
}	t_param;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list; // sei lá que é isso, uma lista linkada de algo que eu não sei

typedef struct s_gc
{
	t_list	*head; // head da lista linkada
}	t_gc; // ? ??? sei lá


typedef struct s_philosopher
{
	pid_t			pid;	//como cada filósof tem que ser um processo e não uma thread precisamos que seu id seja um pid
	size_t			id;		//Id normal de cade filósofo
	size_t			time_last_meal; //Padrão, tempo da última refeição
	size_t			count_to_eat; //quantas refeições foram feitas
	struct s_param	*param;		//ponteiro para estrutura principal com as informações gerais
	
	pthread_t		monitor_processus; //uma thread que vai ser o monitor do filósofo
	//provavelmente uma thread responsável por ficar monitorando o processo
}	t_philosopher;
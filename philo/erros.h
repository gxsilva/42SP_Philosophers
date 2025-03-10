/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:12:02 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/06 15:54:29 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROS_H
# define ERROS_H

/*Input erros* | cod -1 */
# define PHI_OUT_RANGE "Philosopher count out of range (1-200)"
# define INVALID_INPUT "Invalid input"
# define INVALID_FORMAT "Invalid format input"
# define INPUT_NUMBER "Number of invalid arguments, min 4 | max 5"

/*Memory erros | cod -2*/
# define FAILED_MALLOC "Memory Allocation error"

/*Functions erros | cod -3*/
# define FAILED_GET_TIME "An unexpected error occurred gettimeofday"

/*Thread Erros | cod -4*/
# define TH_CREATE "An unexpected error when creating a thread"
# define TH_JOIN "An unexpected error when join a thread"

#endif
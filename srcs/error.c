/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:29:37 by jbettini          #+#    #+#             */
/*   Updated: 2024/04/18 23:47:18 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

int    invalidNumOfArg(void) {
    ft_putstr("Invalid number of argument\n");
    return ERROR;
}
int     dataEnoughError(void) {
    ft_putstr("Data not enough to launch the simulation\n");
    return ERROR;
}

int    fatalError(void) {
    ft_putstr("Fatal Error\n");
    return ERROR;
}

int    badInputFile(char *badLine) {
    ft_putstr("Input file has a bad syntax : ");
    ft_putendl(badLine);
    return ERROR;
}

int    badInstruction(char *badLine) {
    ft_putstr("Instruction doesn't exist or already set : ");
    ft_putendl(badLine);
    return ERROR;
}

int    badRoomSettings(char *badLine) {
    ft_putstr("Bad room settings : ");
    ft_putendl(badLine);
    return ERROR;
}

int    badLinkSettings(char *badLine) {
    ft_putstr("Bad link settings : ");
    ft_putendl(badLine);
    return ERROR;
}

int     linkAlreadyExists(char *badLine) {
    ft_putstr("Link already exists : ");
    ft_putendl(badLine);
    return ERROR;
}

void    handleErrorWithoutStr(int (*fun)(void)) {
    ft_putstr(TXT_RED);
    fun();
    exit(1);
}

void    handleErrorWithStr(char *line, int (*fun)(char *)) {
    ft_putstr(TXT_RED);
    fun(line);
    safeFree(line);
    exit(1);
}
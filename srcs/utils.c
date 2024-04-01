/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:07:42 by jbettini          #+#    #+#             */
/*   Updated: 2024/03/24 08:04:34 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemIn.h"

char *ft_strdup_except(char *src, char exclude)
{
    size_t i;
    size_t j;
    char *str;

    i = 0;
    j = 0;
    while (src[i])
    {
        if (src[i] != exclude)
            j++;
        i++;
    }
    str = malloc(j + 1);
    if (!str)
        return (NULL);
    i = 0;
    j = 0;
    while (src[i])
    {
        if (src[i] != exclude)
        {
            str[j] = src[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
	free(src);
    return (str);
}

int numOfOccurences(const char *str, char c)
{
    int count = 0;
    int i = 0;

    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return count;
}

bool    onlyDigitStr(char *str){
    for (int i = 0; str[i]; i++){
        if (!(ft_isdigit(str[i])))
            return false;
    }
    return true;
}

bool    isComment(char *str){
    if (str[0] == '#' && str[1] != '#')
        return true;
    return false;
}

bool    isStart(char *str) {
    if (ft_strcmp(str, "##start") == 0)
        return true;
    return false;
}

bool    isEnd(char *str){
    if (str[0] == '#' && str[1] == '#' && ft_strlen(str) == 5 && ft_strequ((str + 2), "end"))
        return true;
    return false;
}

bool    isRoom(char *str) {
    if (numOfOccurences(str, ' ') == 2)
        return true;
    return false;
}


bool    isLink(char *str) {
    if (numOfOccurences(str, '-') == 1)
        return true;
    return false;
}

bool    isInstruction(char *str){
    if (str[0] == '#' && str[1] == '#')
        return true;
    return false;
}

bool isNullOrEmpty(char *str) {
    if (ft_strlen(str) == 0 || (ft_strlen(str) == 1 && str[0] == '\0') || str == NULL)
        return true;
    return false;
}

bool nameExist(char *str, t_list *allName) {
    while (allName){
        if (ft_strequ(str, allName->content))
            return true;
        allName = allName->next;
    }
    return false;
}

bool nameIsValid(char *str, t_list *allName){
    for (int i = 0; str[i]; i++){
        if (str[i] == '-' || !ft_isprint(str[i]))
            return false;
    }
    if (nameExist(str, allName))
        return false;
    return true;
}

bool posIsValid(t_room *r, t_list *allRooms){
    while (allRooms) {
        t_room *tmp = allRooms->content;
        if (tmp->posX == r->posX && tmp->posY == r->posY)
            return false;
        allRooms = allRooms->next;
    }
    return true;
}

t_room  *getRoomWithName(char *str, t_list **rooms) {
    t_list *tmp = *rooms;
    while (tmp) {
        t_room *rtmp = tmp->content;
        if (ft_strequ(rtmp->name, str))
            return (rtmp);
        tmp = tmp->next;
    }
    return NULL;
}

bool    lstStrEqu(t_list *lst, char *str) {
    while (lst)
    {
        if (ft_strequ(lst->content, str))
            return true;
        lst = lst->next;
    }
    return false;
}

t_room *Cast(t_list *roomNode) {
    return roomNode->content;
}
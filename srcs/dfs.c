// #include <lemIn.h>

// void enqueueBack(t_room *prevRoom, t_list **queue) {
//     t_list  *neigh = prevRoom->neigh;
//     t_room  *roomTmp = NULL;
//     while (neigh) {
//         roomTmp = (t_room *)neigh->content;
//         if (roomTmp->isSeen == NOT_SEEN && roomTmp->isInqueue == false) {
//             roomTmp->isInqueue = true;
//             ft_lstadd_back(queue, ft_lstnew_prev(roomTmp, *queue));
//         }
//         neigh = neigh->next;
//     }
// }

// void enqueueFront(t_room *prevRoom, t_list **queue) {
//     t_list  *neigh = prevRoom->neigh;
//     t_room  *roomTmp = NULL;
//     while (neigh) {
//         roomTmp = (t_room *)neigh->content;
//         if (roomTmp->isSeen == NOT_SEEN && roomTmp->isInqueue == false) {
//             roomTmp->isInqueue = true;
//             ft_lstadd_front(queue, ft_lstnew_prev(roomTmp, *queue));
//         }
//         neigh = neigh->next;
//     }
// }

// t_list *custom_pop(t_list **list, t_list **poped) {
//     if (*list == NULL)
//         return;

//     t_list *first = *list;
//     *list = first->next;
//     first->next = NULL;
//     ft_lstadd_back(poped, first);
//     return first;
// }

// t_paths    *getEmptyPaths(void){
//     t_paths *ret = malloc(sizeof(t_paths));
//     ret->roomList = NULL;
//     ret->multiNode = NULL;
//     ret->next = NULL;
//     ret->prev = NULL;
//     ret->unique = true;
//     return ret;
// }




// bool    dfs(t_simulation *s) {
//     bool    ret = false;
//     t_list  *prev = NULL;
//     t_list  *queue = NULL;
//     t_list  *poped = NULL;
//     t_room  *currentRoom = NULL;

//     s->graph->startRoom->isSeen = true;
//     enqueue_back(s->graph->startRoom, queue);
//     while (ft_lstsize(queue) > 0) {
//         currentRoom = (t_room *)queue->content;
//         currentRoom->isSeen = SEEN;
//         prev = custom_pop(queue, poped);
//         if (currentRoom->isEnd == true) {
//             ret = true;
//             // need to implment create path/ backtracking fun 

//         }
//         enqueue_front(currentRoom, queue);
//     }
//     return  ret;
// }
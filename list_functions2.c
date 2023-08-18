#include "new_types.h"
#include <stddef.h>
#include <stdlib.h>
/**
* delete_first_node - delete node at index 0
* @head: pointer to the pointer of node
* Return: 1(succeeded) , -1(failed)
*/
int delete_first_node(info_cmd **head)
{
info_cmd  *temp;

if (head == NULL)
return (-1);
if (*head == NULL)
return (-1);
temp = *head;
*head = (*head)->next;
free(temp);
return (1);
}

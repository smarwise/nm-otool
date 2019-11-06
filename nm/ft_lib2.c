#include "../includes/nm.h"

int     ft_arraylen(t_symbol64 *sym)
{
    int len;

    len = 0;
    while (sym->next)
    {
        sym = sym->next;
        len++;
    }
    return (len);
}

char **sort_output(char **array)
{
    char *temp;
    int i;
    int n;

    i = 0;
    n = 0;
    while (array[n])
    {
        if (array[n + 1])
        {
            if (strcmp(array[n], array[n + 1]) > 0)
            {
                temp = array[n];
                array[n] = array[n + 1];
                array[n + 1] = temp;
                sort_output(array);
            }
        }
        else
            return (array);
        n++;
    }
    return (array);
}
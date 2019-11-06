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

int     check_if_exists(char *str, char **array, int i)
{
    int n;

    n = 0;
    while (n != i)
    {
        if (ft_strcmp(str, array[n]) == 0)
            return (1);
        n++;
    }
    return (0);
}

char        **remove_dupes(char **arr)
{
    int i, j = 1, k = 1;
    int n_items;

    n_items = arraylen(arr);
    i = 0;
    while (i < n_items)
    {
        j = i + 1;
        k = j;
        while (j < n_items)
        {
            if (strcmp(arr[i], arr[j])) 
            {
                arr[k] = arr[j];
                k++;
            }
            j++;
        }
        n_items -= j - k;
        i++;
    }
    return arr;
}
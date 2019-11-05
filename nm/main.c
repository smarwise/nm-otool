#include "../includes/nm.h"

int          main(int argc, char **argv)
{
    int n;

    n = 1;
    (void)argv;
    if (argc < 2)
        ft_putendl("Error: Put binary to process");
    else
    {
        while (n < argc)
        {
            ft_putstr("oh yeah!");
            n++;
        }
    }
    return (EXIT_SUCCESS);
}
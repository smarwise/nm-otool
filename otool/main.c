#include "../includes/otool.h"

int          main(int argc, char **argv)
{;
    int n;

    n = 1;
    (void)argv;
    if (argc < 2)
        ft_putendl("Error: Missing args");
    else
    {
        while (n < argc)
        {
            ft_putendl("no");
            n++;
        }
    }
    return (EXIT_SUCCESS);
}


#include "libft.h"

void	waitinput(char *s1)
{
	char	c;

	write(1, s1, strlen(s1));
	read(0, &c, 1);
}

int	test_remove()
{
	return (0);
}

void	ft_putendl(char *str)
{
	write(1, "A\n", 2);
}

void	test()
{
	t_list	lst;
	int 	array[8192 * 8];
	char *str = "hello";

	lst = list_new();

	waitinput("adding");
	list_add(&lst, array, sizeof(array));
	list_add(&lst, str, strlen(str) + 1);

	printf("%s\n", list_get(&lst, (t_cmp_func)strcmp, "hello"));

	list_delete(&lst, free);
}

int	main()
{
	test();
	waitinput("ended");
	return (0);
}

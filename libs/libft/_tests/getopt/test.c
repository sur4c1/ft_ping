#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>    /* for getopt_long; POSIX standard getopt is in unistd.h */
#include "../../libft.h"

#ifdef FT
#define f(argc, argv, optstring, longopst, longindex) ft_getopt_long(argc, argv, optstring, longopts, longindex)
#define optind ft_optind
#define optopt ft_optopt
#define optarg ft_optarg
#define opterr ft_opterr
#else
#define f(argc, argv, optstring, longopst, longindex) getopt_long(argc, argv, optstring, longopts, longindex)
#define FT -1
#define t_option struct option
#endif

void print(int argc, char**argv)
{
		int i = 0;
		printf("[ ");
		while (++i < argc)
				printf("%s ", argv[i]);
		printf("]\n");
}

int	test(int argc, char**argv)
{
	static int i = 0;
	int ret;
	int longindex = 0;
	t_option longopts[] =
	{
		{"abc", no_argument, 0, 'a'},
		{"def", required_argument, 0, 'd'},
		{"ambiguous", no_argument, 0, 'A'},
		{"ambigueux", no_argument, 0, 'B'},
		{0, 0, 0, 0}
	};

	ret = f(argc, argv, "abc:d:012?", longopts, &longindex);
	printf("\n CALL %d\n", i++);
	printf("ret=%d", ret);
	if (ft_isprint(ret))
		printf(" (%c)", ret);
	else if (ret == -1)
		printf(" (EOF)");
	else
		printf(" (.)");
	printf("\n");
	printf("optind=%d\n", optind);
	printf("optopt=%d", optopt);
	if (ft_isprint(optopt))
		printf(" (%c)", optopt);
	else
		printf(" (.)");
	printf("\n");
	printf("optarg=%s\n", optarg);
	printf("longindex=%d\n", longindex);
	print(argc, argv);
	return ret;
}


int main (int argc, char **argv) {
	printf("FT = %d\n", FT);
	print(argc, argv);
	opterr = 0;
	while (test(argc, argv) != -1)
		;
	print(argc, argv);
	exit (0);
}

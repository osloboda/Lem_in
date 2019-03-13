/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:05:04 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:07:54 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <time.h>

void		printways(t_var *var)
{
	t_li	*www;
	t_li	*ww;

	www = var->ways;
	if (www)
		ft_printf("\n");
	while (www)
	{
		ww = www->way;
		if (ww)
			ft_printf(BBLUE("[%s]"), ww->content->name);
		ww = ww->next;
		while (ww)
		{
			ft_printf(BBLUE(" -> [%s]"), ww->content->name);
			ww = ww->next;
		}
		www = www->next;
		ft_printf("\n");
	}
}

void		parse_f(char **argv, t_var *var, int argc, float g)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--paths"))
			printways(var);
		if (!ft_strcmp(argv[i], "--time"))
			ft_printf(GREEN("\nLem-in takes %f seconds\n"), g / 1000000.0);
		if (!ft_strcmp(argv[i], "--lines"))
		{
			if (var->req > 1)
				ft_printf(BBLUE("\nlines required: %i"), var->req);
			ft_printf("\n");
			if (var->req >= var->lines || var->req < 2)
				ft_printf(GREEN("Result: %i\n"), var->lines);
			else
				ft_printf(RED("Result: %i\n"), var->lines);
		}
		else if (!ft_strcmp(argv[i], "--leaks") && ft_printf("\n"))
			system("leaks -q lem-in");
		i++;
	}
}

void		init(t_var **var, t_map **map)
{
	(*var) = malloc(sizeof(t_var));
	(*var)->start = NULL;
	(*var)->end = NULL;
	(*var)->ways = NULL;
	(*var)->pinned = NULL;
	(*var)->locked = NULL;
	(*var)->req = -1;
	(*map) = NULL;
}

int			stat(char *line, t_bist *lins, int argc, char **argv)
{
	t_var	*var;
	t_map	*map;
	clock_t start;
	clock_t stop;

	start = clock();
	init(&var, &map);
	while (get_next_line(0, &line) && line && *line == '#' &&
	ft_strcmp(line, "##start") && ft_strcmp(line, "##end"))
		ftlstadd(&lins, ftlstnew(line, sizeof(t_bist)));
	if (line && *line != '0' && is_digit(line) &&
	(var->ants = ft_atoi(line)) > 0)
	{
		ftlstadd(&lins, ftlstnew(line, sizeof(t_bist)));
		if (dopmain(&var, &map, &lins))
			return (0);
		else if (argc > 1 && (stop = clock()))
			parse_f(argv, var, argc, stop - start);
	}
	else
		return (error(line, var, map, lins));
	freelst(var, map);
	return (0);
}

int			main(int argc, char **argv)
{
	t_bist	*lines;

	lines = ftlstnew((ft_strdup("")), sizeof(t_bist));
	if (argc >= 2 && !ft_strcmp(argv[1], "--help"))
		ft_printf(RED("Usage: ./lem_in [--lines,"
				"--paths, --leaks, --help] < map\n"));
	else
		stat(0, lines, argc, argv);
	return (0);
}

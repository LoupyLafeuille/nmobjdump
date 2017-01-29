/*
** main.c for main in /home/loupy/Rendu/PSU_2015_nmobjdump/nm
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Mon Feb 22 17:19:03 2016
** Last update Fri Feb 26 15:55:32 2016 
*/

#include <elf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "nm.h"

int		g_size = 0;

int		search_info(Elf64_Shdr *shdr, void *data, int nb, char *file)
{
  int		i;

  i = 0;
  while (i < nb)
    {
      if (shdr[i].sh_type == SHT_SYMTAB)
	if (print_line(shdr, data, i, file) == -1 )
	  return (-1);
      ++i;
    }
  return (0);
}

int		my_nm(char *file)
{
  void		*data;
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*shdr;
  int		fd;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (print_error(file, NO_FILE));
  if ((g_size = lseek(fd, 0, SEEK_END)) == 0)
    return (-1);
  data = mmap(NULL, g_size, PROT_READ, MAP_SHARED, fd, 0);
  elf = (Elf64_Ehdr *)data;
  if (elf->e_ident[EI_MAG0] != ELFMAG0 ||
      elf->e_ident[EI_MAG1] != ELFMAG1 ||
      elf->e_ident[EI_MAG2] != ELFMAG2 ||
      elf->e_ident[EI_MAG3] != ELFMAG3 ||
      elf->e_ident[EI_CLASS] != ELFCLASS64)
    return (print_error(file, NOT_ELF));
  if (elf->e_shoff > g_size)
    return (print_error(file, TRUNC));
  shdr = (Elf64_Shdr *)(data + elf->e_shoff);
  if (search_info(shdr, data, elf->e_shnum, file) == -1)
    return (-1);
  close(fd);
  return (0);
}

int		main(int ac, char **av)
{
  int		i;

  i = 1;
  if (ac == 1)
    return (my_nm("a.out"));
  while (i < ac)
    {
      if (ac != 2)
	printf("\n%s:\n", av[i]);
      if (my_nm(av[i]) == -1)
	return (0);
      ++i;
    }
  return (0);
}

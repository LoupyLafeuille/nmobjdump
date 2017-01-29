/*
** main.c for main in /home/loupy/Rendu/PSU_2015_nmobjdump/objdump
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Mon Feb 22 17:20:25 2016
** Last update Fri Feb 26 17:37:57 2016 
*/

#include <elf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "objdump.h"

int		g_size = 0;

static int	my_objdump(char *file)
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
  print_info(shdr, elf, data, file);
  print_obj(shdr, elf, data, file);
  close(fd);
  return (0);
}

int		main(int ac, char **av)
{
  int		i;

  i = 1;
  if (ac == 1)
    return (my_objdump("a.out"));
  while (i < ac)
    {
      if (my_objdump(av[i]) == -1)
	return (0);
      ++i;
    }
  return (0);
}

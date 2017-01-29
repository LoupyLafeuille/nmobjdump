/*
** print.c for obj in /home/loupy/Rendu/PSU_2015_nmobjdump/objdump
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Thu Feb 25 20:53:24 2016
** Last update Fri Feb 26 17:37:20 2016 
*/

#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>

#include "objdump.h"

int		print_error(char *file, char *str)
{
  (!strcmp(file, "a.out")) ?
    fprintf(stderr, "objdump: '%s:' %s\n", file ,str) :
    fprintf(stderr, "objdump: %s: %s\n", file ,str);
  return (-1);
}

void		complete_space(int val, char *buff)
{
  int		i;

  if (val == 16)
    printf(" %s\n", buff);
  else
    {
      while (val < 16)
	{
	  ++val;
	  if (val % 4 == 0)
	    printf(" ");
	  printf("  ");
	}
      printf(" %s", buff);
      if ((i = strlen(buff)) != 16)
	while (i++ < 16)
	  printf(" ");
      printf("\n");
    }
}

int		print_obj(Elf64_Shdr *shdr, Elf64_Ehdr *elf,
			  void *data, char *file)
{
  char		*tb;
  char		*tb2;
  char		buff[LINE + 1];
  int		k;
  int		i;

  i = 0;
  k = 0;
  if (shdr[elf->e_shstrndx].sh_offset > g_size)
    return (print_error(file, TRUNC));
  tb = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
  while (k < elf->e_shnum)
    {
      if (shdr[k].sh_offset > g_size)
	return (print_error(file, TRUNC));
      tb2 = (char *)(data + shdr[k].sh_offset);
      if (shdr[k].sh_flags != 0 && shdr[k].sh_type != SHT_NOBITS)
	{
	  printf("Contents of section %s:\n %04x ",
		 &tb[shdr[k].sh_name], (shdr[k].sh_addr + i));
	  complete_space(data_loop(shdr, tb2, buff, k), buff);
	}
      ++k;
    }
  return (0);
}

int		data_loop(Elf64_Shdr *shdr, char *tb2, char *buff, int k)
{
  int		p;
  int		i;

  i = 0;
  p = 1;
  memset(buff, '\0', 17);
  while (i < shdr[k].sh_size)
    {
      printf("%02x", (unsigned char)tb2[i]);
      buff[p - 1] = (isprint(tb2[i])) ? (unsigned char)tb2[i] : '.';
      if (p % 16 == 0 && (i + 1 != shdr[k].sh_size))
	{
	  printf("  %s\n %04x ", buff,  (shdr[k].sh_addr + (i + 1)));
	  memset(buff, '\0', 17);
	  p = 0;
	}
      else if (p % 4 == 0)
	printf(" ");
      ++i;
      ++p;
    }
  return (p - 1);
}

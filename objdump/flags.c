/*
** flags.c for obj in /home/loupy/Rendu/PSU_2015_nmobjdump/objdump
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Fri Feb 26 17:34:09 2016
** Last update Fri Feb 26 17:36:56 2016 
*/

#include <elf.h>
#include <string.h>
#include <stdio.h>

#include "objdump.h"


void		my_concat(char *dest, char *str, int *val, int i)
{
  strcat(dest, str);
  *val += i;
}

int		flags(char *str, Elf64_Ehdr *elf)
{
  int		val;

  val = 0;
  if (elf->e_type == ET_EXEC)
    my_concat(str, "EXEC_P, ", &val, 2);
  if (elf->e_type == ET_REL)
    my_concat(str, "HAS_RELOC, ", &val, 1);
  if (elf->e_type == ET_DYN)
    {
      (elf->e_phnum != 0) ?
	my_concat(str, "HAS_SYMS, DYNAMIC, D_PAGED\n", &val, 150)
	: my_concat(str, "HAS_SYMS, DYNAMIC\n", &val, 50);
    }
  else
    {
      (elf->e_phnum != 0) ?
	my_concat(str, "HAS_SYMS, D_PAGED\n", &val, 110)
	: my_concat(str, "HAS_SYMS\n", &val, 10);
    }
  return (val);
}

void		print_info(Elf64_Shdr *shdr, Elf64_Ehdr *elf,
			   void *data, char *file)
{
  int		i;
  int		val;
  char		str[50];

  (void)data;
  memset(str, '\0', 50);
  i = (elf->e_ident[EI_CLASS] == ELFCLASS64) ? 64 : 32;
  printf("\n%s:     file format elf%i-x86-%i\n", file, i, i);
  val = flags(str, elf);
  printf("architecture: i386:x86-%i, flags 0x%08i:\n", i, val);
  printf("%s", str);
  printf("start address 0x%016lx\n\n", elf->e_entry);
}

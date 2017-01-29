/*
** print.c for nm in /home/loupy/Rendu/PSU_2015_nmobjdump/nm
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Tue Feb 23 18:10:16 2016
** Last update Fri Feb 26 03:42:08 2016 
*/

#include <stdio.h>
#include <elf.h>
#include <string.h>

#include "nm.h"

int		print_line(Elf64_Shdr *shdr, void *data, int i, char *file)
{
  Elf64_Sym	*sym;
  char		*tb;
  int		j;

  j = 1;
  if (shdr[i].sh_offset > g_size || shdr[shdr[i].sh_link].sh_offset > g_size)
    return (print_error(file, TRUNC));
  sym = (Elf64_Sym *)(data + shdr[i].sh_offset);
  tb = (char *)(data + shdr[shdr[i].sh_link].sh_offset);
  while (j < shdr[i].sh_size / shdr[i].sh_entsize)
    {
      if (ELF64_ST_TYPE(sym[j].st_info) != STT_FILE
	  && ELF64_ST_TYPE(sym[j].st_info) != STT_SECTION)
	{
	  (print_type(&sym[j], shdr) == 'U'
	   || print_type(&sym[j], shdr) == 'w') ?
	    printf("% 16c %c %s\n", ' ',
		   print_type(&sym[j], shdr), &tb[sym[j].st_name]) :
	    printf("%016lx %c %s\n", sym[j].st_value,
		   print_type(&sym[j], shdr), &tb[sym[j].st_name]);
	}
      ++j;
    }
  return (0);
}

int		print_error(char *file, char *str)
{
  (!strcmp(file, "a.out")) ?
    fprintf(stderr, "nm: '%s:' %s\n", file ,str) :
    fprintf(stderr, "nm: %s: %s\n", file ,str);
  return (-1);
}

static char	check_sym(Elf64_Sym *sym)
{
  char		c;

  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    return (c = 'u');
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
      if (sym->st_shndx == SHN_UNDEF)
	return (c = 'w');
      return (c = 'W');
    }
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK
	   && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
      if (sym->st_shndx == SHN_UNDEF)
	return (c = 'v');
      return (c = 'V');
    }
  else if (sym->st_shndx == SHN_UNDEF)
    return (c = 'U');
  else if (sym->st_shndx == SHN_ABS)
    return (c = 'A');
  else if (sym->st_shndx == SHN_COMMON)
    return (c = 'C');
  return (0);
}

static char	check_sym_shdr(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  if (shdr[sym->st_shndx].sh_type == SHT_NOBITS
      && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    return (c = 'B');
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
	   && shdr[sym->st_shndx].sh_flags == SHF_ALLOC)
    return (c = 'R');
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
	   && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    return (c = 'D');
  else if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS
	    && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
	   || shdr[sym->st_shndx].sh_type == SHT_INIT_ARRAY
	   || shdr[sym->st_shndx].sh_type == SHT_FINI_ARRAY
	   || shdr[sym->st_shndx].sh_type == SHT_PREINIT_ARRAY)
    return (c = 'T');
  else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    return (c = 'D');
  else
    return (c = '?');
  return (0);
}

char            print_type(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char  c;

  if ((c = check_sym(sym)) != 0)
    return (c);
  else
    c = check_sym_shdr(sym, shdr);
  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
    c += 32;
  return (c);
}

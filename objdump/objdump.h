/*
** objdump.h for obj in /home/loupy/Rendu/PSU_2015_nmobjdump/objdump
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Tue Feb 23 19:16:47 2016
** Last update Fri Feb 26 17:36:36 2016 
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

# define NO_FILE	"No such file"
# define NOT_ELF	"File format not recognized"
# define TRUNC		"File truncated"
# define LINE		16

extern int		g_size;

int			print_error(char *file, char *str);
int			print_obj(Elf64_Shdr *shdr, Elf64_Ehdr *elf, void *data, char *file);
int			data_loop(Elf64_Shdr *shdr, char *tb2, char *buff, int k);
int			flags(char *str, Elf64_Ehdr *elf);

void			my_concat(char *dest, char *str, int *val, int i);
void			complete_space(int val, char *buff);
void			print_info(Elf64_Shdr *shdr, Elf64_Ehdr *elf,
			   void *data, char *file);

#endif /* !OBJDUMP_H_ */

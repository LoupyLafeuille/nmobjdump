/*
** nm.h for nm in /home/loupy/Rendu/PSU_2015_nmobjdump/nm
**
** Made by
** Login   <loupy@epitech.net>
**
** Started on  Tue Feb 23 17:26:48 2016
** Last update Fri Feb 26 15:53:17 2016 
*/

#ifndef NM_H_
# define NM_H_

# define	NOT_ELF "File format not recognized"
# define	NO_FILE "No such file"
# define	TRUNC	"File truncated"
# define        NO_SYM	"No symbols"

extern int	g_size;

char		print_type(Elf64_Sym *sym, Elf64_Shdr *shdr);

int		search_info(Elf64_Shdr *shdr, void *data, int nb, char *file);
int		print_error(char *file, char *str);
int		my_nm(char *file);

int		print_line(Elf64_Shdr *shdr, void *data, int i, char *file);

#endif /* !NM_H_ */

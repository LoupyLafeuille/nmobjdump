##
## Makefile for minitalk in /home/ye_l/rendu/PSU_2014_minitalk
##
## Made by lp ye
## Login   <ye_l@epitech.net>
##
## Started on  Tue Aug  4 21:21:57 2015 lp ye
## Last update Fri Feb 26 17:37:39 2016 
##


CC	=	gcc

RM	=	rm -f

NM	=	my_nm

OBJDUMP	=	my_objdump

SRCN	=	./nm/main.c \
		./nm/print.c

OBJN	=	$(SRCN:.c=.o)

SRCO	=	./objdump/main.c \
		./objdump/print.c \
		./objdump/flags.c

OBJO	=	$(SRCO:.c=.o)

EFLAGS	=	-W -Werror -Wall -Wextra

all:		$(NM) $(OBJDUMP)

clean:
		$(RM) $(OBJN) $(OBJO)

$(NM):		$(OBJN)
		$(CC) $(OBJN) -o $(NM) $(EFLAGS)

$(OBJDUMP):	$(OBJO)
		$(CC) $(OBJO) -o $(OBJDUMP) $(EFLAGS)

nm:		$(NM)

objdump:	$(OBJDUMP)

fclean:		clean
		$(RM) $(NM) $(OBJDUMP)

re:		fclean all

.PHONY:		all clean fclean re

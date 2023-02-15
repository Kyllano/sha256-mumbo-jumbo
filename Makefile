CC=gcc
OPT=-Wall -lm -g
OBJDIR=bin
SRCDIR=src
EXEC=sha
TARGET=	bin/sha256.o

all : $(EXEC)


#compile couches
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(OPT)

#compile test
test.o : test.c
	$(CC) -o test.o -c test.c $(OPT)

test : $(TARGET) $(OBJDIR)/test.o
	$(CC) $(TARGET) $(OBJDIR)/test.o -o test $(OPT)


$(EXEC): $(TARGET) $(OBJDIR)/program.o
	$(CC) $(TARGET) $(OBJDIR)/program.o -o $(EXEC) $(OPT)


#option du makefile
clean:
	rm -f $(OBJDIR)/*.o
	rm -rf $(EXEC)
	rm -rf test

EXEC = Algorithme_KNN

OBJDIR = bin
SRCDIR = source

creat := $(shell  mkdir -p bin $(BUILD))
$(info $(creat))


SRC := $(wildcard $(SRCDIR)/*.c)

OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all : $(EXEC)

	
	

$(OBJDIR)/%.o : $(SRCDIR)/%.c

	gcc -o $@ -c $< 


$(EXEC) : $(OBJ)

	gcc -o $@ $^ -lm

clean : 
	rm -R $(OBJDIR)

cleanprog :

	rm -rf $(EXEC)
	
zip :	
	tar zcvf $(EXEC).tar.gz ./

exe : $(EXEC)

	./$(EXEC)



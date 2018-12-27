LIBINCLUDES=Types.h Debug.h String.h StringParser.h
LIBSOURCES = String.cpp StringParser.cpp
LIBFILES=String.o StringParser.o
LINK_FLAGS=-lstdc++

.cpp .o:
	gcc -c $<

bday : bday.cpp libs.o Linklist.h
	gcc -o bday bday.cpp libs.o $(LINK_FLAGS)


libs.o : $(LIBFILES) $(LIBSOURCES) $(LIBINCLUDES)
	ld -r -o libs.o $(LIBFILES)

clean :
	rm *.o
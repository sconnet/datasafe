# Makefile for data safe
# 01/13/05
# Steve Connet

TARGET = ds
CFLAGS = -g -Wall
LIBS = -lncurses 
OBJS = datasafe.o config.o document.o util.o screen.o window.o docwindow.o input.o

#.IGNORE:                     # ignore problems (as far as possible)
#.SILENT:                     # don't echo commands executed 
.SUFFIXES: .o .c .cpp

# build the target
$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# build C++ objects
.cpp.o:
	$(CXX) $(CFLAGS) $< -c -o $@

# build C objects
.c.o:
	$(CXX) $(CFLAGS) $< -c -o $@

depends:
#	makedepend -Y -- $(CFLAGS) -- *.cpp	
	rm -rf depends
	$(CXX) -M *.cpp *.c >> depends

clean: 
	@if [ -f $(TARGET) ]; then rm $(TARGET); fi
	@for file in $(OBJS); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done

# DO NOT DELETE
config.o: config.cpp config.h util.h datasafe.h
document.o: document.cpp document.h datasafe.h
datasafe.o: datasafe.cpp config.h document.h datasafe.h
util.o: util.cpp util.h datasafe.h
screen.o: screen.cpp screen.h document.h window.h datasafe.h
window.o: window.cpp window.h datasafe.h
docwindow.o: docwindow.cpp docwindow.h window.h datasafe.h
input.o: input.cpp input.h datasafe.h

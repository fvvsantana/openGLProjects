#parameters:
CC=gcc
CXX=g++
RM=rm -f
CFLAGS=
CPPFLAGS=-g #-I include/
CXXFLAGS=
LDFLAGS=-g
LDLIBS=


#project files:
PNAME=matrixlib
MKFL=makefile
SRCDIR=src
INCDIR=include
OBJDIR=obj
SRCS=$(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) 
HDRS=$(wildcard $(INCDIR)/*.hpp) $(wildcard $(INCDIR)/*/*.hpp)
OBJS=$(subst $(SRCDIR),$(OBJDIR),$(subst .cpp,.o,$(SRCS)))

#build:
all: $(PNAME) 

$(PNAME): $(OBJS) $(MKFL) $(HDRS)
	$(CXX) $(LDFLAGS) -o $(PNAME) $(OBJS) $(LDLIBS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

#run:
run:
	./$(PNAME)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
		$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) $(PNAME)

distclean: clean
	$(RM) *~ .depend

include .depend

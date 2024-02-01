TARGET=calc
CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -O2

OD=src/bin

OBJDIR=$(OD)

ASTOBJS=$(OD)/ast.o $(OD)/boperator.o $(OD)/dividenode.o $(OD)/minusnode.o $(OD)/modulusnode.o $(OD)/multnode.o $(OD)/node.o $(OD)/numnode.o $(OD)/plusnode.o $(OD)/pownode.o

NUMOBJS=$(OD)/num.o $(OD)/long.o $(OD)/short.o

BASEOBJS=$(OD)/calc.o $(OD)/main.o $(OD)/lexer.o $(OD)/parser.o $(OD)/token.o

ALLHEADER=src/ast/ast.h src/ast/boperator.h src/ast/dividenode.h src/ast/minusnode.h src/ast/modulusnode.h src/ast/multnode.h src/ast/node.h src/ast/numnode.h src/ast/plusnode.h src/ast/pownode.h  src/num/num.h src/num/short.h src/num/long.h src/lexer.h src/parser.h src/token.h src/calc.h

ALLSRC=src/ast/ast.cpp src/ast/boperator.cpp src/ast/dividenode.cpp src/ast/minusnode.cpp src/ast/modulusnode.cpp src/ast/multnode.cpp src/ast/node.cpp src/ast/numnode.cpp src/ast/plusnode.cpp src/ast/pownode.cpp  src/num/num.cpp src/num/short.cpp src/num/long.cpp src/main.cpp src/lexer.cpp src/parser.cpp src/token.cpp src/calc.cpp

all: compile

compile: $(TARGET)

$(TARGET): $(ASTOBJS) $(NUMOBJS) $(BASEOBJS)
	$(LD) $(CXXFLAGS) -o $@ $^

run: compile
	./$(TARGET)

clean:
	rm -f -r ./src/bin/* $(TARGET) ./doc/*

doc: doc/index.html
	doxygen Doxyfile

doc/index.html:
	doxygen Doxyfile

$(OBJDIR)/calc.o: src/calc.cpp src/calc.h src/parser.h src/token.h src/ast/node.h src/num/num.h src/lexer.h src/num/num.h

$(OBJDIR)/lexer.o: src/lexer.cpp src/lexer.h src/token.h src/ast/node.h src/num/num.h src/num/num.h

$(OBJDIR)/main.o: src/main.cpp src/calc.h src/parser.h src/token.h src/ast/node.h src/num/num.h src/lexer.h src/num/num.h

$(OBJDIR)/parser.o: src/parser.cpp src/parser.h src/token.h src/ast/node.h src/num/num.h src/lexer.h src/ast/ast.h src/ast/node.h src/token.h src/num/num.h

$(OBJDIR)/token.o: src/token.cpp src/token.h src/ast/node.h src/num/num.h src/num/num.h src/ast/boperator.h src/ast/node.h src/ast/plusnode.h src/ast/boperator.h src/ast/minusnode.h src/ast/multnode.h src/ast/numnode.h src/ast/dividenode.h src/ast/modulusnode.h src/ast/pownode.h

$(OBJDIR)/ast.o: src/ast/ast.cpp src/ast/node.h src/num/num.h src/ast/ast.h src/token.h src/ast/node.h

$(OBJDIR)/boperator.o: src/ast/boperator.cpp src/ast/boperator.h src/ast/node.h src/num/num.h

$(OBJDIR)/dividenode.o: src/ast/dividenode.cpp src/ast/dividenode.h src/ast/boperator.h src/ast/node.h src/num/num.h

$(OBJDIR)/minusnode.o: src/ast/minusnode.cpp src/ast/minusnode.h src/ast/boperator.h src/ast/node.h src/num/num.h

$(OBJDIR)/modulusnode.o: src/ast/modulusnode.cpp src/ast/modulusnode.h src/ast/boperator.h src/ast/node.h src/num/num.h

$(OBJDIR)/multnode.o: src/ast/multnode.cpp src/ast/multnode.h src/ast/boperator.h src/ast/node.h src/num/num.h

$(OBJDIR)/node.o: src/ast/node.cpp src/ast/node.h src/num/num.h

$(OBJDIR)/numnode.o: src/ast/numnode.cpp src/num/num.h src/ast/numnode.h src/ast/node.h

$(OBJDIR)/plusnode.o: src/ast/plusnode.cpp src/ast/plusnode.h src/ast/boperator.h src/ast/node.h src/num/num.h

$(OBJDIR)/pownode.o: src/ast/pownode.cpp src/ast/pownode.h src/ast/boperator.h src/ast/node.h src/num/num.h

$(OBJDIR)/long.o: src/num/long.cpp src/num/num.h src/num/long.h

$(OBJDIR)/num.o: src/num/num.cpp src/num/num.h src/num/short.h src/num/long.h

$(OBJDIR)/short.o: src/num/short.cpp src/num/num.h src/num/short.h

$(OBJDIR)/ast.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJDIR)/boperator.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJDIR)/dividenode.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJDIR)/minusnode.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJDIR)/modulusnode.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/multnode.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/node.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/numnode.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/plusnode.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/pownode.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/num.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/short.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/long.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/main.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/lexer.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/parser.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/token.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/calc.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

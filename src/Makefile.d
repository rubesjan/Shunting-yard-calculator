$(OBJDIR)/calc.o: src/calc.cpp src/calc.h src/parser.h src/token.h src/./ast/node.h \
 src/./ast/../num/num.h src/lexer.h src/./num/num.h

$(OBJDIR)/lexer.o: src/lexer.cpp src/lexer.h src/token.h src/./ast/node.h \
 src/./ast/../num/num.h src/./num/num.h

$(OBJDIR)/main.o: src/main.cpp src/calc.h src/parser.h src/token.h src/./ast/node.h \
 src/./ast/../num/num.h src/lexer.h src/./num/num.h

$(OBJDIR)/parser.o: src/parser.cpp src/parser.h src/token.h src/./ast/node.h \
 src/./ast/../num/num.h src/lexer.h src/./ast/ast.h src/./ast/node.h \
 src/./ast/../token.h src/./num/num.h

$(OBJDIR)/token.o: src/token.cpp src/token.h src/./ast/node.h \
 src/./ast/../num/num.h src/./num/num.h src/./ast/boperator.h \
 src/./ast/node.h src/./ast/plusnode.h src/./ast/boperator.h \
 src/./ast/minusnode.h src/./ast/multnode.h src/./ast/numnode.h \
 src/./ast/dividenode.h src/./ast/modulusnode.h src/./ast/pownode.h

$(OBJDIR)/ast.o: src/ast/ast.cpp src/ast/node.h src/ast/../num/num.h src/ast/ast.h \
 src/ast/../token.h src/ast/.././ast/node.h

$(OBJDIR)/boperator.o: src/ast/boperator.cpp src/ast/boperator.h src/ast/node.h \
 src/ast/../num/num.h

$(OBJDIR)/dividenode.o: src/ast/dividenode.cpp src/ast/dividenode.h \
 src/ast/boperator.h src/ast/node.h src/ast/../num/num.h

$(OBJDIR)/minusnode.o: src/ast/minusnode.cpp src/ast/minusnode.h \
 src/ast/boperator.h src/ast/node.h src/ast/../num/num.h

$(OBJDIR)/modulusnode.o: src/ast/modulusnode.cpp src/ast/modulusnode.h \
 src/ast/boperator.h src/ast/node.h src/ast/../num/num.h

$(OBJDIR)/multnode.o: src/ast/multnode.cpp src/ast/multnode.h src/ast/boperator.h \
 src/ast/node.h src/ast/../num/num.h

$(OBJDIR)/node.o: src/ast/node.cpp src/ast/node.h src/ast/../num/num.h

$(OBJDIR)/numnode.o: src/ast/numnode.cpp src/ast/../num/num.h src/ast/numnode.h \
 src/ast/node.h

$(OBJDIR)/plusnode.o: src/ast/plusnode.cpp src/ast/plusnode.h src/ast/boperator.h \
 src/ast/node.h src/ast/../num/num.h

$(OBJDIR)/pownode.o: src/ast/pownode.cpp src/ast/pownode.h src/ast/boperator.h \
 src/ast/node.h src/ast/../num/num.h

$(OBJDIR)/long.o: src/num/long.cpp src/num/num.h src/num/long.h

$(OBJDIR)/num.o: src/num/num.cpp src/num/num.h src/num/short.h src/num/long.h

$(OBJDIR)/short.o: src/num/short.cpp src/num/num.h src/num/short.h

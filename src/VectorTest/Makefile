LIB = ../../lib
OBJ = ../../obj
OPTIONS = -Wall -Wfatal-errors -I ${LIB}
NAME = VectorTest

${NAME}: ${OBJ}/${NAME}.o ${OBJ}/Algebra.o
	g++ -o ${NAME} ${OBJ}/${NAME}.o ${OBJ}/Algebra.o

${OBJ}/Algebra.o: ${LIB}/Algebra.cpp ${LIB}/Algebra.hpp
	g++ -c ${OPTIONS} ${LIB}/Algebra.cpp
	mv Algebra.o ${OBJ}

${OBJ}/${NAME}.o: ${NAME}.cpp
	g++ -c ${OPTIONS} ${NAME}.cpp
	mv ${NAME}.o ${OBJ}

clean:
	rm -f ${NAME} ${NAME}.o vet.dat ${OBJ}/Algebra.o
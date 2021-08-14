
# binary
BIN_NAME=finalprogram

# sources
C_SOURCE=$(wildcard ./source/*.c)
# get all files from the dir
# headers
H_SOURCE=$(wildcard ./include/*.h)

# compilation objects
OBJ=$(subst .c,.o,$(subst source,object,$(C_SOURCE)))
#OBJ=${C_SOURCE:.c=.o}

# compiler and flags
CPL=gcc

CPL_FLAGS=-c   \
          -lm  \
          -W   \
          -Wall


VALGRIND_FLAGS=-s \
               --leak-check=full \
               --show-leak-kinds=all \
               --track-origins=yes \
               --verbose



# target 'run' to execute binary
run: all
	@ ./bin/${BIN_NAME}


# verify memory management
valgrind: all
	@ clear
	@ valgrind ${VALGRIND_FLAGS} ./bin/${BIN_NAME}


all: objectFolder ./bin/${BIN_NAME}
	@ echo " \033[1;32m  Tudo feito!  \033[0m "
	@ echo ''
# @ hidden code


objectFolder:
	@ mkdir -p object
	@ mkdir -p bin


./bin/${BIN_NAME}: ${OBJ}
	@ ${CPL} $^ -o $@
	@ echo " \033[0;33m  Criando binario \033[43;1;37m$@\033[0m\033[0;33m  \033[0m "
	@ echo ''
# $@ target name, $^ all requisites, $< first requisite


./object/%.o: ./source/%.c ./include/%.h
	@ ${CPL} $< ${CPL_FLAGS} -o $@ -I ./include
	@ echo " \033[0;35m  Gerando objeto de compilacao \033[45;1;37m$@\033[0m\033[0;35m  \033[0m "
	@ echo ''
# '%.o' get the name 'stem' (without extension)


./object/main.o: ./source/main.c ${H_SOURCE}
	@ ${CPL} $< ${CPL_FLAGS} -o $@ -I ./include
	@ echo " \033[0;34m  Gerando objeto de compilacao \033[44;1;37m$@\033[0m\033[0;34m  \033[0m "
	@ echo ''
# -o generate compilation object like output, -I include the libs from selected dir to make unnecessary the #include in codes need navigate in the patch


# clear residual files
clean:
	@ rm -rf ./object/*.o *~ ./bin/${BIN_NAME}
	@ rmdir object bin
	@ echo " \033[1;31m  Removendo binario \033[41;1;37m./bin/${BIN_NAME}\033[0m\033[1;31m e objetos de compilacao \033[41;1;37m${OBJ}\033[0m\033[1;31m e arquivos de backup  \033[0m "
	@ echo ''


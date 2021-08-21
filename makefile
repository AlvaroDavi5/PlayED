
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
			   --show-reachable=yes \
               --track-origins=yes \
               --verbose



# target 'run' to execute binary
run: all
	@ ./bin/${BIN_NAME}


# verify memory management
valgrind: all
	@ clear
	@ valgrind ${VALGRIND_FLAGS} ./bin/${BIN_NAME}


assembly: all
	@ gcc -E ./source/main.c > ./object/precomp_code.i
	@ gcc -S ./object/precomp_code.i -o ./object/assembly_code.s


all: objectFolder ./bin/${BIN_NAME}
	@ echo " \033[1;32m  Done!  \033[0m "
	@ echo ''
# @ hidden code


objectFolder:
	@ mkdir -p object
	@ mkdir -p bin


./bin/${BIN_NAME}: ${OBJ}
	@ ${CPL} $^ -o $@
	@ echo " \033[0;33m  Building Binary \033[43;1;37m$@\033[0m\033[0;33m  \033[0m "
	@ echo ''
# $@ target name, $^ all requisites, $< first requisite


./object/%.o: ./source/%.c ./include/%.h
	@ ${CPL} $< ${CPL_FLAGS} -o $@ -I ./include
	@ echo " \033[0;35m  Generating compilation object \033[45;1;37m$@\033[0m\033[0;35m  \033[0m "
	@ echo ''
# '%.o' get the name 'stem' (without extension)


./object/main.o: ./source/main.c ${H_SOURCE}
	@ ${CPL} $< ${CPL_FLAGS} -o $@ -I ./include
	@ echo " \033[0;34m  Generating compilation object \033[44;1;37m$@\033[0m\033[0;34m  \033[0m "
	@ echo ''
# -o generate compilation object like output, -I include the libs from selected dir to make unnecessary the #include in codes need navigate in the patch


# clear residual files
clean:
	@ rm -rf ./object/*.o ./object/*.i ./object/*.s *~ ./bin/${BIN_NAME}
	@ rm -rf ./output/
	@ rmdir object bin
	@ echo " \033[1;31m  Removing binary \033[41;1;37m./bin/${BIN_NAME}\033[0m\033[1;31m and compilation objects \033[41;1;37m${OBJ}\033[0m\033[1;31m and backup or output files  \033[0m "
	@ echo ''


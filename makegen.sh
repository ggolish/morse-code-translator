# Uses makefile-gen to generate a Makefile for a C project with an include
# folder for headers and a src folder for source files

target="morse"
cflags="-Wall:-g:-Iinclude"
files=""
for cfile in src/*.c; do
  files="${files} ${cfile}"
  for hfile in $(grep '^#include "[a-zA-Z_]*.h"' ${cfile} | cut -d '"' -f2); do
    files="${files}:include/${hfile}"
  done
done

makefile-gen C ${target} ${cflags} "${files}"

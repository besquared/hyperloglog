require 'mkmf'

$CC = "g++"
$CFLAGS += " -Iheaders -Wall -Wextra -Weffc++ -Wconversion -Wno-shadow -Wcast-align -Wwrite-strings -Wstrict-overflow=5 -Wpointer-arith -Winit-self -Wno-unused -Werror"
$LIBS << " -lstdc++"

create_makefile('hyperloglog')

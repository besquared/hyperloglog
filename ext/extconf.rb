require 'mkmf'

$CC = "g++"
$CFLAGS += " -Iheaders -Wall -Wextra -Weffc++ -Wno-conversion -Wno-shadow -Wcast-align -Wwrite-strings -Wstrict-overflow=5 -Wpointer-arith -Winit-self -Wno-unused -Wno-parentheses -Werror"
$LIBS << " -lstdc++"

create_makefile('hyperloglog')

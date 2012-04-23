require 'mkmf'

$CC = "g++"
$CFLAGS += "-Iheaders -Wall -Wextra -Weffc++ -Wconversion -Wshadow -Wcast-align -Wwrite-strings -Wstrict-overflow=5  -Wpointer-arith -Winit-self"
$LIBS << " -lstdc++"

create_makefile('hyperloglog')
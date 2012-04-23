
SHELL = /bin/sh

#### Start of system configuration section. ####

srcdir = .
topdir = /opt/ruby-enterprise-1.8.7-2012.02/lib/ruby/1.8/i686-darwin10.6.0
hdrdir = $(topdir)
VPATH = $(srcdir):$(topdir):$(hdrdir)
prefix = $(DESTDIR)/opt/ruby-enterprise-1.8.7-2012.02
exec_prefix = $(prefix)
mandir = $(datarootdir)/man
sbindir = $(exec_prefix)/sbin
sharedstatedir = $(prefix)/com
pdfdir = $(docdir)
sitearchdir = $(sitelibdir)/$(sitearch)
bindir = $(exec_prefix)/bin
localedir = $(datarootdir)/locale
vendordir = $(libdir)/ruby/vendor_ruby
libexecdir = $(exec_prefix)/libexec
archdir = $(rubylibdir)/$(arch)
oldincludedir = $(DESTDIR)/usr/include
libdir = $(exec_prefix)/lib
docdir = $(datarootdir)/doc/$(PACKAGE)
htmldir = $(docdir)
infodir = $(datarootdir)/info
vendorarchdir = $(vendorlibdir)/$(sitearch)
datadir = $(datarootdir)
psdir = $(docdir)
vendorlibdir = $(vendordir)/$(ruby_version)
rubylibdir = $(libdir)/ruby/$(ruby_version)
sitedir = $(libdir)/ruby/site_ruby
dvidir = $(docdir)
datarootdir = $(prefix)/share
includedir = $(prefix)/include
sysconfdir = $(prefix)/etc
localstatedir = $(prefix)/var
sitelibdir = $(sitedir)/$(ruby_version)

CC = /usr/bin/gcc
LIBRUBY = $(LIBRUBY_A)
LIBRUBY_A = lib$(RUBY_SO_NAME)-static.a
LIBRUBYARG_SHARED = 
LIBRUBYARG_STATIC = -l$(RUBY_SO_NAME)-static

RUBY_EXTCONF_H = 
CFLAGS   =  -fno-common -g -O2  -pipe -fno-common $(cflags)-Iheaders -Wall -Wextra -Weffc++ -Wconversion -Wshadow -Wcast-align -Wwrite-strings -Wstrict-overflow=5  -Wpointer-arith -Winit-self 
INCFLAGS = $(PREINCFLAGS) -I. -I/opt/local/include -I$(topdir) -I$(hdrdir) -I$(srcdir)
DEFS     = 
CPPFLAGS =   -D_XOPEN_SOURCE -D_DARWIN_C_SOURCE $(DEFS) $(cppflags)
CXXFLAGS = $(CFLAGS) 
ldflags  = -L. 
dldflags = 
archflag = 
DLDFLAGS = $(ldflags) $(dldflags) $(archflag)
LDSHARED = cc -dynamic -bundle -undefined suppress -flat_namespace
AR = ar
EXEEXT = 

RUBY_INSTALL_NAME = ruby
RUBY_SO_NAME = ruby
arch = i686-darwin10.6.0
sitearch = i686-darwin10.6.0
ruby_version = 1.8
ruby = /opt/ruby-enterprise-1.8.7-2012.02/bin/ruby
RUBY = $(ruby)
RM = rm -f
MAKEDIRS = mkdir -p
INSTALL = /usr/bin/install -c
INSTALL_PROG = $(INSTALL) -m 0755
INSTALL_DATA = $(INSTALL) -m 644
COPY = cp

#### End of system configuration section. ####

preload = 

libpath = . $(libdir)
LIBPATH =  -L. -L$(libdir)
DEFFILE = 

CLEANFILES = mkmf.log
DISTCLEANFILES = 

extout = 
extout_prefix = 
target_prefix = 
LOCAL_LIBS = 
LIBS =   -L/opt/local/lib -ldl -lobjc   -lstdc++
SRCS = ewah-bitset.cpp hyperloglog.cpp
OBJS = ewah-bitset.o hyperloglog.o
TARGET = hyperloglog
DLLIB = $(TARGET).bundle
EXTSTATIC = 
STATIC_LIB = 

BINDIR        = $(bindir)
RUBYCOMMONDIR = $(sitedir)$(target_prefix)
RUBYLIBDIR    = $(sitelibdir)$(target_prefix)
RUBYARCHDIR   = $(sitearchdir)$(target_prefix)

TARGET_SO     = $(DLLIB)
CLEANLIBS     = $(TARGET).bundle $(TARGET).il? $(TARGET).tds $(TARGET).map
CLEANOBJS     = *.o *.a *.s[ol] *.pdb *.exp *.bak

all:		$(DLLIB)
static:		$(STATIC_LIB)

clean:
		@-$(RM) $(CLEANLIBS) $(CLEANOBJS) $(CLEANFILES)

distclean:	clean
		@-$(RM) Makefile $(RUBY_EXTCONF_H) conftest.* mkmf.log
		@-$(RM) core ruby$(EXEEXT) *~ $(DISTCLEANFILES)

realclean:	distclean
install: install-so install-rb

install-so: $(RUBYARCHDIR)
install-so: $(RUBYARCHDIR)/$(DLLIB)
$(RUBYARCHDIR)/$(DLLIB): $(DLLIB)
	$(INSTALL_PROG) $(DLLIB) $(RUBYARCHDIR)
install-rb: pre-install-rb install-rb-default
install-rb-default: pre-install-rb-default
pre-install-rb: Makefile
pre-install-rb-default: Makefile
$(RUBYARCHDIR):
	$(MAKEDIRS) $@

site-install: site-install-so site-install-rb
site-install-so: install-so
site-install-rb: install-rb

.SUFFIXES: .c .m .cc .cxx .cpp .C .o

.cc.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.cxx.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.cpp.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.C.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.c.o:
	$(CC) $(INCFLAGS) $(CPPFLAGS) $(CFLAGS) -c $<

$(DLLIB): $(OBJS) Makefile
	@-$(RM) $@
	$(LDSHARED) -o $@ $(OBJS) $(LIBPATH) $(DLDFLAGS) $(LOCAL_LIBS) $(LIBS)



$(OBJS): ruby.h defines.h

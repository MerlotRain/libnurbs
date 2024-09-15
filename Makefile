# libnurbs Makefile

CC= gcc
CFLAGS= -Wall -Iinclude

OBJS= nurbs.o \
	  nurbs_analyze.o \
	  nurbs_curveboundingbox.o \
	  nurbs_divide.o \
	  nurbs_eval.o \
	  nurbs_intersect.o \
	  nurbs_make.o \
	  nurbs_mat.o \
	  nurbs_modify.o \
	  nurbs_tess.o \
	  nurbs_vec.o \
	  nurbs_viewer.o

LIBANAME= libnurbs.a	

$(LIBANAME): $(OBJS)
	ar rcs $(LIBANAME) $(OBJS)

all: $(LIBANAME)

clean:
	rm -rf $(OBJS)
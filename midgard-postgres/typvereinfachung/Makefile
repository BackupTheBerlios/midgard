TOPDIR=../..
ECPG_FLAGS=-I/usr/include/postgresql
CXXFLAGS=-I$(TOPDIR)/c++ -I$(TOPDIR)/ManuProC_Base/src $(ECPG_FLAGS)
LIBS=-L$(TOPDIR)/c++ -L$(TOPDIR)/ManuProC_Base/src  -L$(TOPDIR)/ManuProC_Base/src/.libs -lManuProC_Base -lecpg -lpq
#-lcommon++

typvereinf: typvereinf.o
	$(CXX) -o $@ $< $(LIBS)

TOPDIR=../..
ECPG_FLAGS=-I/usr/include/postgresql
CXXFLAGS=-I$(TOPDIR)/c++ -I$(TOPDIR)/ManuProC_Base/src $(ECPG_FLAGS)
LIBS=-L$(TOPDIR)/c++ -L$(TOPDIR)/ManuProC_Base/src -lManuProC_Base
#-lcommon++

typvereinf: typvereinf.o
	$(CXX) -o $@ $< $(LIBS)

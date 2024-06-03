COMPONENT_NAME = RunAllTests
CPPUTEST_HOME = ./CppUTest

CPPUTEST_WARNINGFLAGS += -Wno-c++14-compat
CPPUTEST_WARNINGFLAGS += -std=c++11

LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt 

INCLUDE_DIRS = \
	$(CPPUTEST_HOME)/include \
	../app/include 

		
SRC_DIRS = \
	../app/src 


TEST_SRC_DIRS = \
	. \


MOCKS_SRC_DIRS += \
	./mocks_and_stubs/src
	
#CPPUTEST_CPPFLAGS += -include avr/io.h

include $(CPPUTEST_HOME)/MakefileWorker.mk

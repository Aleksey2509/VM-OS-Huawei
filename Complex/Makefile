CXX = g++
CXXFLAGS = -Wall -std=c++17
CXXFLAGS += -Iinclude

BUILD = build
HEADL = include

SRCL = source
SRCFILES = test.cc Complex.cc
SRC := $(addprefix $(SRCL)/, $(SRCFILES))

OBJL = $(BUILD)/objfiles
OBJECTS = $(SRCFILES:.cc=.o)
OBJ := $(addprefix $(OBJL)/, $(OBJECTS))

MKDIR = @mkdir -p $(@D)
RM = rm -rf

$(OBJL)/%.o: $(SRCL)/%.cc
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: test

depend: $(BUILD)/.depend

$(BUILD)/.depend: 
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(SRC) -MM > $(BUILD)/.depend

test: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o test

clean:
	$(RM) $(BUILD)
	$(RM) test

-include $(BUILD)/.depend
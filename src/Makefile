cc = g++
TARGET=test
src = ${shell find  -name '*.cpp'}
INC = -I../include
OBJS = ${src:.cpp=.o}
all: $(TARGET) clean
$(TARGET):$(OBJS) 
	$(cc) -o $@ $^
%.o:%.cpp
	@echo $@
	$(cc) -c $(INC) $< -o $@
clean:
	rm $(OBJS)

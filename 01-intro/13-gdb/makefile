src    = $(wildcard *.cpp)
objs   = $(patsubst %.cpp, %.o, $(src))
target = main

$(target):$(objs)
	$(CXX) $(objs) -o $(target) -g

%.o:%.cpp
	$(CXX) -c $< -o $@

.PHONY:clean

clean:
	rm -rf $(objs) main

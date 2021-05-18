objects = demo.o Base.o

demo : $(objects)
	g++ -o demo $(objects)

$(objects) : Base.h

.PHONY : clean

clean:
	rm demo $(objects)

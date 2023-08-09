.PHONY: all
all: bin/lib/libFixedPoint.a

bin/test/testFixedPoint: ./inc/*.* bin/obj/doctest.o src/fixedPoint.cpp | bin/test
	g++ ./bin/obj/doctest.o src/fixedPoint.cpp -obin/test/testFixedPoint -Wall -lgcc -I./inc
bin/lib/libFixedPoint.a: ./inc/*.* bin/test/testFixedPoint src/fixedPoint.cpp | bin/lib bin/test
	./bin/test/testFixedPoint
	arm-none-eabi-g++ -r -mlong-calls -fno-exceptions -march=armv6-m src/fixedPoint.cpp -obin/lib/libFixedPoint.a -O3 -Wall -Wno-unused-function -I./inc

bin/obj/doctest.o: ./inc/doctest/doctest.hpp ./inc/doctest/doctest_full.hpp | bin/obj
	g++ -c ./src/doctest/doctest.cpp -I./inc/doctest -obin/obj/doctest.o

bin/obj:
	mkdir -p bin/obj

bin/lib:
	mkdir -p bin/lib

bin/test:
	mkdir -p bin/test
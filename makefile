.PHONY: all
all: bin/inc/vcsLib.h bin/lib/libvcsMock.a bin/lib/libFP32.a bin/inc/boundingBox.hpp

.PHONY: clean
clean:
	rm bin -rf

bin/inc/vcsLib.h: inc/vcsLib.h | bin/inc
	cp -f inc/vcsLib.h bin/inc/vcsLib.h

bin/lib/libvcsMock.a: inc/vcsLib.h src/vcsMock.c | bin/lib
	arm-none-eabi-g++ -r -mlong-calls -fno-exceptions -march=armv6-m src/vcsMock.c -obin/lib/libvcsMock.a -O3 -I./inc

bin/test/testFP32: inc/doctest/*.* ./inc/fp32.hpp bin/obj/doctest.o src/fp32.cpp | bin/test
	g++ ./bin/obj/doctest.o src/fp32.cpp -obin/test/testFP32 -Wall -lgcc -I./inc
bin/lib/libFP32.a: inc/doctest/*.* ./inc/fp32.hpp bin/test/testFP32 src/fp32.cpp | bin/inc bin/lib bin/test
	./bin/test/testFP32
	cp -f inc/fp32.hpp bin/inc/fp32.hpp
	arm-none-eabi-g++ -r -mlong-calls -fno-exceptions -march=armv6-m src/fp32.cpp -obin/lib/libFP32.a -O3 -Wall -Wno-unused-function -I./inc -lgcc
	arm-none-eabi-strip bin/lib/libFP32.a -g

bin/test/testBoundingBox: inc/doctest/*.* ./inc/boundingBox.hpp bin/obj/doctest.o src/boundingBox.cpp | bin/test
	g++ ./bin/obj/doctest.o src/boundingBox.cpp -obin/test/testBoundingBox -Wall -lgcc -I./inc
bin/inc/boundingBox.hpp: inc/doctest/*.* ./inc/boundingBox.hpp bin/test/testBoundingBox src/boundingBox.cpp | bin/inc bin/lib bin/test
	./bin/test/testBoundingBox
	cp -f inc/boundingBox.hpp bin/inc/boundingBox.hpp

bin/obj/doctest.o: ./inc/doctest/doctest.hpp ./inc/doctest/doctest_full.hpp | bin/obj
	g++ -c ./src/doctest/doctest.cpp -I./inc/doctest -obin/obj/doctest.o

bin/obj:
	mkdir -p bin/obj

bin/inc:
	mkdir -p bin/inc

bin/lib:
	mkdir -p bin/lib

bin/test:
	mkdir -p bin/test
.PHONY: all
all: bin/inc/vcsLib.h bin/lib/libFixedPoint.a bin/lib/libBoundingBox.a

bin/inc/vcsLib.h: inc/vcsLib.h | bin/inc
	cp -f inc/vcsLib.h bin/inc/vcsLib.h

bin/test/testFixedPoint: inc/doctest/*.* ./inc/fixedPoint.hpp bin/obj/doctest.o src/fixedPoint.cpp | bin/test
	g++ ./bin/obj/doctest.o src/fixedPoint.cpp -obin/test/testFixedPoint -Wall -lgcc -I./inc
bin/lib/libFixedPoint.a: inc/doctest/*.* ./inc/fixedPoint.hpp bin/test/testFixedPoint src/fixedPoint.cpp | bin/inc bin/lib bin/test
	./bin/test/testFixedPoint
	cp -f inc/fixedPoint.hpp bin/inc/fixedPoint.hpp
	arm-none-eabi-g++ -r -mlong-calls -fno-exceptions -march=armv6-m src/fixedPoint.cpp -obin/lib/libFixedPoint.a -O3 -Wall -Wno-unused-function -I./inc

bin/test/testBoundingBox: inc/doctest/*.* ./inc/boundingBox.hpp bin/obj/doctest.o src/boundingBox.cpp | bin/test
	g++ ./bin/obj/doctest.o src/boundingBox.cpp -obin/test/testBoundingBox -Wall -lgcc -I./inc
bin/lib/libBoundingBox.a: inc/doctest/*.* ./inc/boundingBox.hpp bin/test/testBoundingBox src/boundingBox.cpp | bin/inc bin/lib bin/test
	./bin/test/testBoundingBox
	cp -f inc/boundingBox.hpp bin/inc/boundingBox.hpp
	arm-none-eabi-g++ -r -mlong-calls -fno-exceptions -march=armv6-m src/boundingBox.cpp -obin/lib/libBoundingBox.a -O3 -Wall -Wno-unused-function -I./inc

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
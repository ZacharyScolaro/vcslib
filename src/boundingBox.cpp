#include "./doctest/doctest.hpp"
#include "boundingBox.hpp"

TEST_CASE("BoundingBox") {
	CHECK(BoundingBox<int>(10, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(5, 0, 0, 5, 0, 5)) == false); // right of BB
	CHECK(BoundingBox<int>(10, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(15, 0, 0, 5, 0, 5)) == false); // left of BB
	CHECK(BoundingBox<int>(10, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(6, 0, 0, 5, 0, 5)) == true); // left overlaps BB
	CHECK(BoundingBox<int>(10, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(14, 0, 0, 5, 0, 5)) == true); // right overlaps BB
	CHECK(BoundingBox<int>(10, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(11, 0, 0, 3, 0, 5)) == true); // width encapsulates BB
	CHECK(BoundingBox<int>(10, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(9, 0, 0, 7, 0, 5)) == true); // width encapsulated by BB

	CHECK(BoundingBox<int>(0, 10, 0, 5, 0, 5).Intersects(BoundingBox<int>(0, 5, 0, 5, 0, 5)) == false); // below BB
	CHECK(BoundingBox<int>(0, 10, 0, 5, 0, 5).Intersects(BoundingBox<int>(0, 15, 0, 5, 0, 5)) == false); // above BB
	CHECK(BoundingBox<int>(0, 10, 0, 5, 0, 5).Intersects(BoundingBox<int>(0, 6, 0, 5, 0, 5)) == true); // top overlaps BB
	CHECK(BoundingBox<int>(0, 10, 0, 5, 0, 5).Intersects(BoundingBox<int>(0, 14, 0, 5, 0, 5)) == true); // bottom overlaps BB
	CHECK(BoundingBox<int>(0, 10, 0, 5, 0, 5).Intersects(BoundingBox<int>(0, 11, 0, 5, 0, 3)) == true); // height encapsulates BB
	CHECK(BoundingBox<int>(0, 10, 0, 5, 0, 5).Intersects(BoundingBox<int>(0, 9, 0, 5, 0, 7)) == true); // height encapsulated by BB

	CHECK(BoundingBox<int>(0, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(5, 5, 0, 5, 0, 5)) == false); // bottom right at BBs top left
	CHECK(BoundingBox<int>(0, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(5, 0, -1, 5, 0, 5)) == true); // negative left
	CHECK(BoundingBox<int>(0, 0, 0, 5, 0, 5).Intersects(BoundingBox<int>(0, 5, 0, 5, -1, 5)) == true); // negative top
}

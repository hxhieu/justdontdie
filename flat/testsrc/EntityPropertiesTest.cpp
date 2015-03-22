#include <iostream>
#include "catch.hpp"
#include "EntityImpl.h"
#include "../src/EntityProperties.h"

using namespace flat2d;

TEST_CASE( "Test point matching", "[locprop]" )
{
	EntityProperties lop(100, 100, 100);

	REQUIRE( lop.containsPoint(150, 150) );
	REQUIRE( lop.containsPoint(105, 105) );
	REQUIRE( lop.containsPoint(100, 100) );
	REQUIRE( lop.containsPoint(200, 200) );

	REQUIRE( !lop.containsPoint(201, 201) );
	REQUIRE( !lop.containsPoint(50, 50) );
	REQUIRE( !lop.containsPoint(99, 99) );
}

TEST_CASE( "Test equality", "[locprop]" )
{
	EntityProperties lop1(10, 20, 40);
	EntityProperties lop2(10, 20, 40);
	EntityProperties lop3(10, 10, 40);

	REQUIRE( lop1 == lop2 );
	REQUIRE( !(lop1 == lop3) );
	REQUIRE( lop1 != lop3 );
	REQUIRE( !(lop1 != lop2) );
}

TEST_CASE( "Test less operator", "[locprop]" )
{
	EntityProperties lop1(10, 20, 40);
	EntityProperties lop2(10, 20, 40);
	EntityProperties lop3(10, 10, 40);
	EntityProperties lop4(5, 30, 40);

	REQUIRE( !(lop1 < lop2) );
	REQUIRE( !(lop2 < lop1) );
	REQUIRE( lop3 < lop1 );
	REQUIRE( lop4 < lop1 );
	REQUIRE( !(lop1 < lop3) );
	REQUIRE( !(lop1 < lop4) );
}

TEST_CASE( "Test change trigger", "[locprop]" )
{
	bool hasMovedOutOfSpace = false;
	EntityImpl o(100, 100);

	MapArea area(0, 0, 200, 200);
	EntityProperties& lop = o.getEntityProperties();
	lop.getCurrentAreas().push_back(area);

	REQUIRE( 1 == lop.getCurrentAreas().size() );

	lop.setOnLocationChange([&]() { 
			hasMovedOutOfSpace = true;
			});

	lop.setXpos(150);
	REQUIRE( !hasMovedOutOfSpace );

	lop.setXpos(250);
	REQUIRE( hasMovedOutOfSpace );
	hasMovedOutOfSpace = false;

	lop.setYpos(250);
	REQUIRE( hasMovedOutOfSpace );
	hasMovedOutOfSpace = false;

	lop.incrementXpos(250);
	REQUIRE( hasMovedOutOfSpace );
	hasMovedOutOfSpace = false;

	lop.incrementYpos(250);
	REQUIRE( hasMovedOutOfSpace );
	hasMovedOutOfSpace = false;
}

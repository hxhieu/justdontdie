#include <CppUTest/TestHarness.h>
#include "GameObjectImpl.h"
#include "../src/ObjectContainer.h"
#include "../src/GameData.h"
#include "../src/CollisionDetector.h"
#include "../src/Mixer.h"

TEST_GROUP( ObjectContainerTests )
{
};

TEST( ObjectContainerTests, TestObjectRegister )
{
	flat2d::GameObject* c = new GameObjectImpl(100, 100);
	flat2d::ObjectContainer container;

	CHECK_EQUAL( 0, container.getObjectCount() );
	container.registerObject(c);
	CHECK_EQUAL( 1, container.getObjectCount() );
	container.registerObject(c);
	CHECK_EQUAL( 1, container.getObjectCount() );
	container.unregisterObject(c);
	CHECK_EQUAL( 0, container.getObjectCount() );

	delete c;
}

TEST( ObjectContainerTests, TestObjectContainerDestructor )
{
	flat2d::GameObject* c = new GameObjectImpl(100, 100);
	flat2d::ObjectContainer* container = new flat2d::ObjectContainer();

	CHECK_EQUAL( 0, container->getObjectCount() );

	container->registerObject(c);

	CHECK_EQUAL( 1, container->getObjectCount() );

	container->registerObject(c);

	CHECK_EQUAL( 1, container->getObjectCount() );

	delete container;
}

TEST( ObjectContainerTests, TestObjectContainerUnregister )
{
	flat2d::GameObject* c = new GameObjectImpl(100, 100);
	flat2d::ObjectContainer container;

	container.unregisterObject(c);

	delete c;
}

TEST( ObjectContainerTests, TestObjectContainerLayers )
{
	flat2d::GameObject* c1 = new GameObjectImpl(100, 100);
	flat2d::GameObject* c2 = new GameObjectImpl(100, 100);
	flat2d::GameObject* c3 = new GameObjectImpl(100, 100);
	flat2d::ObjectContainer container;
	
	CHECK_EQUAL( 0, container.getObjectCountFor(0) );

	container.addLayer(0);
	container.addLayer(0);
	container.addLayer(1);

	container.registerObject(c1);

	CHECK_EQUAL( 1, container.getObjectCount() );
	CHECK_EQUAL( 1, container.getObjectCountFor(flat2d::ObjectContainer::DEFAULT_LAYER) );

	container.registerObject(c2, 0);
	container.registerObject(c2, 1);

	CHECK_EQUAL( 2, container.getObjectCount() );
	CHECK_EQUAL( 1, container.getObjectCountFor(0) );
	CHECK_EQUAL( 0, container.getObjectCountFor(1) );

	container.registerObject(c3, 1);

	CHECK_EQUAL( 1, container.getObjectCountFor(1) );
	CHECK_EQUAL( 3, container.getObjectCount() );

	container.unregisterObject(c2);

	CHECK_EQUAL( 0, container.getObjectCountFor(0) );
	CHECK_EQUAL( 2, container.getObjectCount() );

	delete c2;
}

TEST( ObjectContainerTests, TestObjectContainerClearLayers )
{
	flat2d::GameObject* c1 = new GameObjectImpl(100, 100);
	flat2d::GameObject* c2 = new GameObjectImpl(100, 100);
	flat2d::GameObject* c3 = new GameObjectImpl(100, 100);
	flat2d::GameObject* c4 = new GameObjectImpl(100, 100);
	flat2d::GameObject* c5 = new GameObjectImpl(100, 100);
	flat2d::GameObject* c6 = new GameObjectImpl(100, 100);
	flat2d::ObjectContainer container;

	unsigned int backLayer = 0;
	unsigned int frontLayer = 1;

	container.addLayer(backLayer);
	container.addLayer(frontLayer);

	container.registerObject(c1, frontLayer);
	container.registerObject(c2, frontLayer);
	container.registerObject(c3, frontLayer);
	container.registerObject(c4, backLayer);
	container.registerObject(c5, backLayer);
	container.registerObject(c6, backLayer);

	CHECK_EQUAL ( 6, container.getObjectCount() );
	CHECK_EQUAL ( 3, container.getObjectCountFor(frontLayer) );
	CHECK_EQUAL ( 3, container.getObjectCountFor(backLayer) );

	container.unregisterAllObjectsFor(frontLayer);

	CHECK_EQUAL ( 3, container.getObjectCount() );
	CHECK_EQUAL ( 0, container.getObjectCountFor(frontLayer) );
	CHECK_EQUAL ( 3, container.getObjectCountFor(backLayer) );
}

TEST( ObjectContainerTests, TestObjectAutoclean )
{
	flat2d::GameObject* c1 = new GameObjectImpl(100, 100);
	GameObjectImpl* c2 = new GameObjectImpl(100, 100);

	flat2d::ObjectContainer container;
	flat2d::CollisionDetector detector(&container);
	flat2d::Mixer mixer;
	flat2d::GameData gameData(&container, &detector, &mixer, (flat2d::RenderData*) nullptr,
			(flat2d::DeltatimeMonitor*) nullptr);

	container.registerObject(c1);
	container.registerObject(c2);

	CHECK_EQUAL ( 2, container.getObjectCount() );

	c2->setDead(true);
	container.preHandleObjects(&gameData);

	CHECK_EQUAL ( 1, container.getObjectCount() );
}

TEST( ObjectContainerTests, TestSpatialPartitions )
{
	flat2d::ObjectContainer container;

	flat2d::GameObject* o1 = new GameObjectImpl(50, 50);
	flat2d::GameObject* o2 = new GameObjectImpl(150, 150);
	flat2d::GameObject* o3 = new GameObjectImpl(550, 550);
	flat2d::GameObject* o4 = new GameObjectImpl(75, 75);
	flat2d::GameObject* o5 = new GameObjectImpl(1095, 1095);

	container.registerObject(o1);
	CHECK_EQUAL ( 1, container.getSpatialPartitionCount() );

	container.registerObject(o4);
	CHECK_EQUAL ( 1, container.getSpatialPartitionCount() );

	container.registerObject(o2);
	CHECK_EQUAL ( 2, container.getSpatialPartitionCount() );

	container.registerObject(o3);
	CHECK_EQUAL ( 3, container.getSpatialPartitionCount() );

	container.registerObject(o5);
	CHECK_EQUAL ( 7, container.getSpatialPartitionCount() );
}

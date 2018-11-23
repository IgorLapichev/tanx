set(TARGET_SRC 
	src/CalcThread.cpp
	src/Communicator.cpp 
	src/Context.cpp
	src/Entity.cpp
	src/Logics.cpp
	src/MessageManager.cpp
	src/MessageObserver.cpp
	src/ObjectPool.cpp
	src/ThreadPool.cpp
	src/stdafx.cpp
	src/tanx.cpp
	src/UnitEntity.cpp
	src/Trajectory.cpp
   )

set(TARGET_H 
	src/CalcThread.h
	src/Communicator.h 
	src/Context.h
	src/Entity.h
	src/Logics.h
	src/MessageManager.h
	src/MessageObserver.h
	src/ObjectPool.h
	src/ThreadPool.h
	src/stdafx.h
	src/defs.h
	src/UnitEntity.h
	src/Trajectory.h
   )

set(PROJECT_FILES
	${TARGET_SRC}
	${TARGET_H}
   )

set_property(GLOBAL PROPERTY SRC_LIST "${PROJECT_FILES}")
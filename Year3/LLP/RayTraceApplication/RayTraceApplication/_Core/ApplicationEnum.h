#pragma once

enum ApplicationEnum
{
	Application_SequentialStatic = 1,
	Application_SequentialStaticBV,
	Application_SequentialPhysics,
	Application_SequentialPhysicsBV,

	Application_ParallelStatic,
	Application_ParallelStaticBV,
	Application_ParallelPhysics,
	Application_ParallelPhysicsBV,

	Application_Dummy,
};
============================================================================== 
========================== DirectX Physics Project ===========================
============================================================================== 
============================ Author: Ryan Buxton =============================
============================================================================== 

============================================================================== 
================================== Contents ==================================
==============================================================================
	
- Transform
	- Contains Matrix calculations for updating attitudes of 3-dimensional 
		objects
		
- Particle
	- Contains physics calculations for point-mass physics (implementing 
		RK4 Numerical Integration)
	- Contains Collision Detection methods for AABB-AABB Collision Detection
	- Contains Collision Resolution system incorporating Coefficient of 
		Restituition
		
- Rigid Body
	- Inherits from Particle
	- Features Angular Velocity and Acceleration
	- Features Inertia and Moment data

- Collision Manager
	- Currently takes two objects particles when collisions occur between
	  said objects and resolves the collision.
		- Currently only Sphere-Sphere and AABB-AABB.
	
- Vector2
	- Contains FLOATs for 2D POSITION or TEXTURE data
	- Contains OPERATOR overrides for Vector2
	- Contains 2-dimensional vector mathematics functions
	
- Vector3
	- Contains FLOATs for 3D POSITIONs
	- Contains OPERATOR overrides for Vector3
	- Contains 3-dimensional vector mathematics functions
	
- Vector4 
	- Contains FLOATs for Lighting and Material data

- Matrix3x3
	- Holds Matrix information for use as Inertia and Moments
	- Contains instructions for Matrix Mathematics
	
- Quaternion
	- Holds Vector data and a scalar for rotation
	- Contains instructions for Quaternion and Vector mathematics


============================================================================== 
==================================== To-do ===================================
============================================================================== 

- Collision Manager
	- Incorporate a multitude of Collision Detections methods such as:
		- AABB - Plane
		- Sphere - Plane
		- etc.	
	- Resolution
		- Take magnitude of new velocity and apply it on the reflection between the collision
			normal and the old velocity
		
- RigidBody
	- Implement remaining RigidBody functionality based from David Bourg.
	- Test on Boxes (Standard Dropping)
	- Test on stacks for balancing and reaction to collision-based falling.

================================ Update 1.0.3 =================================
============================== Date: 22.08.2016 ==============================

- Particle
	- As flagged on GitHub, the Particle motion bug has been fixed; Objects
	  now fall at equal rate when only gravity is applied.

- Collision Manager
	- Issues regarding object-object collision has been fixed.
	- Particle objects now collide and resolve as they should.

================================ Update 1.0.2 =================================
============================== Date: 12.08.2016 ==============================

- Collision Manager
	- Collision Manager has been created featuring:
		- AABB-AABB Collision for Point-Mass
		- Sphere-Sphere (Untested)
		- Interpenetration Resolution
		- Collision Resolution

================================ Update 1.0.1 =================================
============================== Date: 11.08.2016 ==============================

- FIXED : Vector3
	- objects positions and motion matches that	of the XMFLOAT3 implementation	
	- FIX: Do not return references of Vector3 post-operation.
	
- ADDITION : RigidBody
	- Added Header Data for RigidBody class
	- Added Source File for RigidBody implementing constructors inheriting
		from Particle, its data and functions.























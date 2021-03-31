#pragma once

#define PI									3.14159265f
#define RHO									0.002369f
#define GRAVITY								-9.81f

#define FPOINT_TOLERANCE					0.0000000001f
#define COLLISION_TOLERANCE					0.1f
#define PENETRATON_TOLERANCE				0.05f
#define CONTACT_TOLERANCE					0.1f
#define VELOCITY_TOLERANCE					0.05f

#define NO_COLLISION						0
#define COLLISION							1
#define PENETRATION							-1
#define CONTACT								2

#define FRICTION_FACTOR						0.3f
#define LINEAR_DRAG_COEFFICIENT				10.0f	
#define ANGULAR_DRAG_COEFFICIENT			400.0f
#define COEFFICIENT_RESTITIUTION_GROUND		0.1f

#define DO_PENETRATION_TEST					true
#define DO_FRICTION							true

#define DEGREES_TO_RADIANS(DEGREES)			DEGREES * PI / 180.0f
#define RADIANS_TO_DEGREES(RADIANS)			RADIANS * 180.0f / PI

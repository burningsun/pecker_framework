#include "data/pecker_shape_compare_algorithm.h"
#include "native/pecker_log.h"
USING_PECKER_SDK

void shape_logic_test()
{
	pecker_vector3 vecP(1.0f,-2.0f,1.0f);
	pecker_vector3 vecA(1.0f,3.0f,-5.0f);
	pecker_vector3 vecB(-1.0f,-1.0f,-1.0f);
	Float d = euler_distance_dot_to_line_3d_float(vecA,vecB,vecP);
	
	PECKER_LOG_INFO("distance","distance = %f",d);
}
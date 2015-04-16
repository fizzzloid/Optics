#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

class position;
class ray;

namespace common_functions
{
		position *stretch_intersection
			(position edge_a, position edge_b, ray* r);
};

#endif // COMMON_FUNCTIONS_H

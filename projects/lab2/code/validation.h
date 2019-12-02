#ifndef VALIDATION_H
#define VALIDATION_H

#include <vector> 

#include "types.h"

namespace validation{
	bool originIsInConvexHull(const std::vector<glvec>& points);
	bool duplicatePoints(const std::vector<glvec>& points);
}

#endif

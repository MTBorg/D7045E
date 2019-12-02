#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>

#include "types.h"

/*
 * Compute the convex hull using andrew's algorithm on a set of points.
 *
 * Assumes the set of points to contain at least three points (otherwise behavior is
 * undefined).
 *
 * @param points The set of points to perform andrews algorithm on
 *
 * @returns A new set of points containing the convex hull (starting from the upper hull)
 */
std::vector<glvec> convexHull(const std::vector<glvec> points);


#endif

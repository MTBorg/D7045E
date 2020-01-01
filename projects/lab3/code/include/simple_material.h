#ifndef SIMPLE_MATERIAL_H
#define SIMPLE_MATERIAL_H

#include "material.h"

#include "types.h"

class SimpleMaterial: public Material{
private:
	Color color;
public:
	SimpleMaterial(Color color);
	void applyMaterial() override;
};

#endif

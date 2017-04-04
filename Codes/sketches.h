#ifndef _SKETCHES_H
#define _SKETCHES_H

#include "sketches/A_Sketch_16bit.h"
#include "sketches/CM_Sketch_16bit.h"
#include "sketches/CSM_Sketch_16bit.h"
#include "sketches/CU_Sketch_16bit.h"
#include "sketches/C_Sketch_16bit.h"
#include "sketches/Diamond_Sketch_4bit_nd.h"
#include "sketches/Diamond_Sketch_Delete.h"

static struct Sketch {
	string name[6] = { "CSM", "CM", "A", "C", "CU", "Diamond" };
    CM_Sketch_16bit * cm;
    CU_Sketch_16bit * cu;
    A_Sketch_16bit * a;
    C_Sketch_16bit * c;
    CSM_Sketch_16bit * csm;
    Diamond_Sketch_4bit_nd * d ;
  #if DELETE == 1
    Diamond_Sketch_Delete * del;
  #endif
} sketch;

#endif

#pragma once

// Set this in your compiler flags
// Valid values: 2, 3, 4, 5, 6
#ifndef XM_GENERATION
#define XM_GENERATION 4
#endif


#if XM_GENERATION >=3 && XM_GENERATION <=6
#define IS_XM4
#else
#define IS_XM2
#endif
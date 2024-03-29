/*
 * Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

/* Example of integrating CUDA functions into an existing 
 * application / framework.
 * CPP code representing the existing application / framework.
 * Compiled with default CPP compiler.
 */

// includes, system
#include <iostream>
#include <stdlib.h>

// Required to include CUDA vector types
#include <vector_types.h>
#include "cutil_inline.h"

////////////////////////////////////////////////////////////////////////////////
// declaration, forward
extern "C" void runTest(const int argc, const char** argv, 
                        char* data, int2* data_int2, unsigned int len);

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int
main(int argc, char** argv)
{

    // input data
    int len = 16;
    // the data has some zero padding at the end so that the size is a multiple of
    // four, this simplifies the processing as each thread can process four
    // elements (which is necessary to avoid bank conflicts) but no branching is
    // necessary to avoid out of bounds reads
    char str[] = { 82, 121, 118, 118, 121, 42, 97, 121, 124, 118, 110, 56,
                   10, 10, 10, 10};

    // Use int2 showing that CUDA vector types can be used in cpp code
    int2 i2[16];
    for( int i = 0; i < len; i++ )
    {
        i2[i].x = str[i];
        i2[i].y = 10;
    }

    // run the device part of the program
    runTest(argc, (const char**)argv, str, i2, len);

    std::cout << str << std::endl;
    for( int i = 0; i < len; i++ )
    {
        std::cout << (char)(i2[i].x);
    }
    std::cout << std::endl;

    cutilExit(argc, argv);
}

#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetProperty(libraryPropertyType type, int *value)
{
	cufftResult retval = cufftGetProperty(type, value);
	return retval;
}
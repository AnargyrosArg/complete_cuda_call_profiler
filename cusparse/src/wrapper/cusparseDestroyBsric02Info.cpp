#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyBsric02Info(bsric02Info_t info)
{
	cusparseStatus_t retval = cusparseDestroyBsric02Info(info);
	return retval;
}
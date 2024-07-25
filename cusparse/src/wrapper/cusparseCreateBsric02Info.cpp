#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateBsric02Info(bsric02Info_t *info)
{
	cusparseStatus_t retval = cusparseCreateBsric02Info(info);
	return retval;
}
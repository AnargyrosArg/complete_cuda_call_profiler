#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateBsrilu02Info(bsrilu02Info_t *info)
{
	cusparseStatus_t retval = cusparseCreateBsrilu02Info(info);
	return retval;
}
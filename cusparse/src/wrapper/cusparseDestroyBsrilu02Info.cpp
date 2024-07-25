#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyBsrilu02Info(bsrilu02Info_t info)
{
	cusparseStatus_t retval = cusparseDestroyBsrilu02Info(info);
	return retval;
}
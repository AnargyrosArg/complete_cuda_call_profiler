#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateCsrilu02Info(csrilu02Info_t *info)
{
	cusparseStatus_t retval = cusparseCreateCsrilu02Info(info);
	return retval;
}
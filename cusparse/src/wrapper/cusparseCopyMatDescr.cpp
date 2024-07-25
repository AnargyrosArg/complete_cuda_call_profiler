#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCopyMatDescr(cusparseMatDescr_t dest, const cusparseMatDescr_t src)
{
	cusparseStatus_t retval = cusparseCopyMatDescr(dest, src);
	return retval;
}
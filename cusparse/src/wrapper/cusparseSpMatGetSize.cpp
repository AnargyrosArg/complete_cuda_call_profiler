#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMatGetSize(cusparseSpMatDescr_t spMatDescr, int64_t *rows, int64_t *cols, int64_t *nnz)
{
	cusparseStatus_t retval = cusparseSpMatGetSize(spMatDescr, rows, cols, nnz);
	return retval;
}
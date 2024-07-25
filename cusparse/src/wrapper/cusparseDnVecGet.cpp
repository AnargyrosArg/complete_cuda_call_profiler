#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDnVecGet(cusparseDnVecDescr_t dnVecDescr, int64_t *size, void **values, cudaDataType *valueType)
{
	cusparseStatus_t retval = cusparseDnVecGet(dnVecDescr, size, values, valueType);
	return retval;
}
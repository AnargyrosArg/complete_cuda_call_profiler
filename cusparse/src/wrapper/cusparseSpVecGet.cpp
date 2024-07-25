#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpVecGet(cusparseSpVecDescr_t spVecDescr, int64_t *size, int64_t *nnz, void **indices, void **values, cusparseIndexType_t *idxType, cusparseIndexBase_t *idxBase, cudaDataType *valueType)
{
	cusparseStatus_t retval = cusparseSpVecGet(spVecDescr, size, nnz, indices, values, idxType, idxBase, valueType);
	return retval;
}
#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCooGet(cusparseSpMatDescr_t spMatDescr, int64_t *rows, int64_t *cols, int64_t *nnz, void **cooRowInd, void **cooColInd, void **cooValues, cusparseIndexType_t *idxType, cusparseIndexBase_t *idxBase, cudaDataType *valueType)
{
	cusparseStatus_t retval = cusparseCooGet(spMatDescr, rows, cols, nnz, cooRowInd, cooColInd, cooValues, idxType, idxBase, valueType);
	return retval;
}
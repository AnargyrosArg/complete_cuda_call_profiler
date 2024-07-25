#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseBlockedEllGet(cusparseSpMatDescr_t spMatDescr, int64_t *rows, int64_t *cols, int64_t *ellBlockSize, int64_t *ellCols, void **ellColInd, void **ellValue, cusparseIndexType_t *ellIdxType, cusparseIndexBase_t *idxBase, cudaDataType *valueType)
{
	cusparseStatus_t retval = cusparseBlockedEllGet(spMatDescr, rows, cols, ellBlockSize, ellCols, ellColInd, ellValue, ellIdxType, idxBase, valueType);
	return retval;
}
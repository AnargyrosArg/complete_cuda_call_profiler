#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCsrGet(cusparseSpMatDescr_t spMatDescr, int64_t *rows, int64_t *cols, int64_t *nnz, void **csrRowOffsets, void **csrColInd, void **csrValues, cusparseIndexType_t *csrRowOffsetsType, cusparseIndexType_t *csrColIndType, cusparseIndexBase_t *idxBase, cudaDataType *valueType)
{
	cusparseStatus_t retval = cusparseCsrGet(spMatDescr, rows, cols, nnz, csrRowOffsets, csrColInd, csrValues, csrRowOffsetsType, csrColIndType, idxBase, valueType);
	return retval;
}
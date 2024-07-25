#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateCsc(cusparseSpMatDescr_t *spMatDescr, int64_t rows, int64_t cols, int64_t nnz, void *cscColOffsets, void *cscRowInd, void *cscValues, cusparseIndexType_t cscColOffsetsType, cusparseIndexType_t cscRowIndType, cusparseIndexBase_t idxBase, cudaDataType valueType)
{
	cusparseStatus_t retval = cusparseCreateCsc(spMatDescr, rows, cols, nnz, cscColOffsets, cscRowInd, cscValues, cscColOffsetsType, cscRowIndType, idxBase, valueType);
	return retval;
}
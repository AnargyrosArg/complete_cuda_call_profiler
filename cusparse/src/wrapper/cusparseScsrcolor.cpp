#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseScsrcolor(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const float *fractionToColor, int *ncolors, int *coloring, int *reordering, const cusparseColorInfo_t info)
{
	cusparseStatus_t retval = cusparseScsrcolor(handle, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, fractionToColor, ncolors, coloring, reordering, info);
	return retval;
}
#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsrgeam2_bufferSizeExt)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, int, const cuDoubleComplex *, const int *, const int *, const cuDoubleComplex *, const cusparseMatDescr_t, int, const cuDoubleComplex *, const int *, const int *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsrgeam2_bufferSizeExt(cusparseHandle_t handle, int m, int n, const cuDoubleComplex *alpha, const cusparseMatDescr_t descrA, int nnzA, const cuDoubleComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cuDoubleComplex *beta, const cusparseMatDescr_t descrB, int nnzB, const cuDoubleComplex *csrSortedValB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const cusparseMatDescr_t descrC, const cuDoubleComplex *csrSortedValC, const int *csrSortedRowPtrC, const int *csrSortedColIndC, size_t *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsrgeam2_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsrgeam2_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, int, const cuDoubleComplex *, const int *, const int *, const cuDoubleComplex *, const cusparseMatDescr_t, int, const cuDoubleComplex *, const int *, const int *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsrgeam2_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseZcsrgeam2_bufferSizeExt:%p\n", wrapper_cusparseZcsrgeam2_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsrgeam2_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsrgeam2_bufferSizeExt(handle, m, n, alpha, descrA, nnzA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, beta, descrB, nnzB, csrSortedValB, csrSortedRowPtrB, csrSortedColIndB, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBufferSizeInBytes);
		return retval;
	}
}
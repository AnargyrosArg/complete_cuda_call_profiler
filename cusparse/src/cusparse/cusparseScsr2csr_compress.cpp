#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsr2csr_compress)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, int, const int *, float *, int *, int *, float);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsr2csr_compress(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedColIndA, const int *csrSortedRowPtrA, int nnzA, const int *nnzPerRow, float *csrSortedValC, int *csrSortedColIndC, int *csrSortedRowPtrC, float tol) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsr2csr_compress)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsr2csr_compress = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, int, const int *, float *, int *, int *, float)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsr2csr_compress");
			fprintf(stderr, "wrapper_cusparseScsr2csr_compress:%p\n", wrapper_cusparseScsr2csr_compress);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsr2csr_compress():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsr2csr_compress(handle, m, n, descrA, csrSortedValA, csrSortedColIndA, csrSortedRowPtrA, nnzA, nnzPerRow, csrSortedValC, csrSortedColIndC, csrSortedRowPtrC, tol);
		return retval;
	}
}
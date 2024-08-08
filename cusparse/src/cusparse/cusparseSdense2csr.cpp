#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSdense2csr)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, int, const int *, float *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSdense2csr(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const float *A, int lda, const int *nnzPerRow, float *csrSortedValA, int *csrSortedRowPtrA, int *csrSortedColIndA) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSdense2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSdense2csr = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, int, const int *, float *, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSdense2csr");
			fprintf(stderr, "wrapper_cusparseSdense2csr:%p\n", wrapper_cusparseSdense2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSdense2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSdense2csr(handle, m, n, descrA, A, lda, nnzPerRow, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA);
		return retval;
	}
}
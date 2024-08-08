#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpruneDense2csr)(cusparseHandle_t, int, int, const float *, int, const float *, const cusparseMatDescr_t, float *, const int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpruneDense2csr(cusparseHandle_t handle, int m, int n, const float *A, int lda, const float *threshold, const cusparseMatDescr_t descrC, float *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpruneDense2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpruneDense2csr = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, int, const float *, const cusparseMatDescr_t, float *, const int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpruneDense2csr");
			fprintf(stderr, "wrapper_cusparseSpruneDense2csr:%p\n", wrapper_cusparseSpruneDense2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpruneDense2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpruneDense2csr(handle, m, n, A, lda, threshold, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBuffer);
		return retval;
	}
}
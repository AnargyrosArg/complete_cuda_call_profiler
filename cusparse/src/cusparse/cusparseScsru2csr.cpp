#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsru2csr)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, float *, const int *, int *, csru2csrInfo_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsru2csr(cusparseHandle_t handle, int m, int n, int nnz, const cusparseMatDescr_t descrA, float *csrVal, const int *csrRowPtr, int *csrColInd, csru2csrInfo_t info, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsru2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsru2csr = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, float *, const int *, int *, csru2csrInfo_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsru2csr");
			fprintf(stderr, "wrapper_cusparseScsru2csr:%p\n", wrapper_cusparseScsru2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsru2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsru2csr(handle, m, n, nnz, descrA, csrVal, csrRowPtr, csrColInd, info, pBuffer);
		return retval;
	}
}
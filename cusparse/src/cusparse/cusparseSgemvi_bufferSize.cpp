#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgemvi_bufferSize)(cusparseHandle_t, cusparseOperation_t, int, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgemvi_bufferSize(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, int nnz, int *pBufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgemvi_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgemvi_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, int, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgemvi_bufferSize");
			fprintf(stderr, "wrapper_cusparseSgemvi_bufferSize:%p\n", wrapper_cusparseSgemvi_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgemvi_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgemvi_bufferSize(handle, transA, m, n, nnz, pBufferSize);
		return retval;
	}
}
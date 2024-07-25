#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgemvi_bufferSize)(cusparseHandle_t, cusparseOperation_t, int, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgemvi_bufferSize(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, int nnz, int *pBufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgemvi_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgemvi_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, int, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgemvi_bufferSize");
			fprintf(stderr, "wrapper_cusparseDgemvi_bufferSize:%p\n", wrapper_cusparseDgemvi_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgemvi_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgemvi_bufferSize(handle, transA, m, n, nnz, pBufferSize);
		return retval;
	}
}
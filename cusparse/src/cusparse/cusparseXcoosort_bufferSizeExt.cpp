#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcoosort_bufferSizeExt)(cusparseHandle_t, int, int, int, const int *, const int *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcoosort_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnz, const int *cooRowsA, const int *cooColsA, size_t *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcoosort_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcoosort_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const int *, const int *, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcoosort_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseXcoosort_bufferSizeExt:%p\n", wrapper_cusparseXcoosort_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcoosort_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcoosort_bufferSizeExt(handle, m, n, nnz, cooRowsA, cooColsA, pBufferSizeInBytes);
		return retval;
	}
}
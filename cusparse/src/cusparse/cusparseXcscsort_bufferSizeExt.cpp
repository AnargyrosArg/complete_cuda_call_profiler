#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcscsort_bufferSizeExt)(cusparseHandle_t, int, int, int, const int *, const int *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcscsort_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnz, const int *cscColPtrA, const int *cscRowIndA, size_t *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcscsort_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcscsort_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const int *, const int *, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcscsort_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseXcscsort_bufferSizeExt:%p\n", wrapper_cusparseXcscsort_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcscsort_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcscsort_bufferSizeExt(handle, m, n, nnz, cscColPtrA, cscRowIndA, pBufferSizeInBytes);
		return retval;
	}
}
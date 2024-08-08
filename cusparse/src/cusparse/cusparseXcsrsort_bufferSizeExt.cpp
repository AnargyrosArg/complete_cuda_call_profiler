#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsrsort_bufferSizeExt)(cusparseHandle_t, int, int, int, const int *, const int *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsrsort_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnz, const int *csrRowPtrA, const int *csrColIndA, size_t *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsrsort_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsrsort_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const int *, const int *, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsrsort_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseXcsrsort_bufferSizeExt:%p\n", wrapper_cusparseXcsrsort_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsrsort_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsrsort_bufferSizeExt(handle, m, n, nnz, csrRowPtrA, csrColIndA, pBufferSizeInBytes);
		return retval;
	}
}
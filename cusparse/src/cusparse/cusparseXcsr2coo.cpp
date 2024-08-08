#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsr2coo)(cusparseHandle_t, const int *, int, int, int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsr2coo(cusparseHandle_t handle, const int *csrSortedRowPtr, int nnz, int m, int *cooRowInd, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsr2coo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsr2coo = (cusparseStatus_t (*)(cusparseHandle_t, const int *, int, int, int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsr2coo");
			fprintf(stderr, "wrapper_cusparseXcsr2coo:%p\n", wrapper_cusparseXcsr2coo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsr2coo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsr2coo(handle, csrSortedRowPtr, nnz, m, cooRowInd, idxBase);
		return retval;
	}
}
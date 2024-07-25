#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgthr)(cusparseHandle_t, int, const cuComplex *, cuComplex *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgthr(cusparseHandle_t handle, int nnz, const cuComplex *y, cuComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgthr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgthr = (cusparseStatus_t (*)(cusparseHandle_t, int, const cuComplex *, cuComplex *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgthr");
			fprintf(stderr, "wrapper_cusparseCgthr:%p\n", wrapper_cusparseCgthr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgthr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgthr(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
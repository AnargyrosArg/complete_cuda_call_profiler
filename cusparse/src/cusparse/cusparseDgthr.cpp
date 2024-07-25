#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgthr)(cusparseHandle_t, int, const double *, double *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgthr(cusparseHandle_t handle, int nnz, const double *y, double *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgthr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgthr = (cusparseStatus_t (*)(cusparseHandle_t, int, const double *, double *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgthr");
			fprintf(stderr, "wrapper_cusparseDgthr:%p\n", wrapper_cusparseDgthr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgthr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgthr(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
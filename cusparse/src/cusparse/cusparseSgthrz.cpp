#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgthrz)(cusparseHandle_t, int, float *, float *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgthrz(cusparseHandle_t handle, int nnz, float *y, float *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgthrz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgthrz = (cusparseStatus_t (*)(cusparseHandle_t, int, float *, float *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgthrz");
			fprintf(stderr, "wrapper_cusparseSgthrz:%p\n", wrapper_cusparseSgthrz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgthrz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgthrz(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
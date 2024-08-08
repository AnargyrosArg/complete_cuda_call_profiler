#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSaxpyi)(cusparseHandle_t, int, const float *, const float *, const int *, float *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSaxpyi(cusparseHandle_t handle, int nnz, const float *alpha, const float *xVal, const int *xInd, float *y, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSaxpyi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSaxpyi = (cusparseStatus_t (*)(cusparseHandle_t, int, const float *, const float *, const int *, float *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSaxpyi");
			fprintf(stderr, "wrapper_cusparseSaxpyi:%p\n", wrapper_cusparseSaxpyi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSaxpyi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSaxpyi(handle, nnz, alpha, xVal, xInd, y, idxBase);
		return retval;
	}
}
#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgthr)(cusparseHandle_t, int, const float *, float *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgthr(cusparseHandle_t handle, int nnz, const float *y, float *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgthr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgthr = (cusparseStatus_t (*)(cusparseHandle_t, int, const float *, float *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgthr");
			fprintf(stderr, "wrapper_cusparseSgthr:%p\n", wrapper_cusparseSgthr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgthr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgthr(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
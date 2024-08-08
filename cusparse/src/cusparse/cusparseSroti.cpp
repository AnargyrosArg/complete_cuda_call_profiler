#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSroti)(cusparseHandle_t, int, float *, const int *, float *, const float *, const float *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSroti(cusparseHandle_t handle, int nnz, float *xVal, const int *xInd, float *y, const float *c, const float *s, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSroti)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSroti = (cusparseStatus_t (*)(cusparseHandle_t, int, float *, const int *, float *, const float *, const float *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSroti");
			fprintf(stderr, "wrapper_cusparseSroti:%p\n", wrapper_cusparseSroti);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSroti():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSroti(handle, nnz, xVal, xInd, y, c, s, idxBase);
		return retval;
	}
}
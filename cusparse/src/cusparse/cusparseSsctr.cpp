#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSsctr)(cusparseHandle_t, int, const float *, const int *, float *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSsctr(cusparseHandle_t handle, int nnz, const float *xVal, const int *xInd, float *y, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSsctr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSsctr = (cusparseStatus_t (*)(cusparseHandle_t, int, const float *, const int *, float *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSsctr");
			fprintf(stderr, "wrapper_cusparseSsctr:%p\n", wrapper_cusparseSsctr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSsctr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSsctr(handle, nnz, xVal, xInd, y, idxBase);
		return retval;
	}
}
#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDaxpyi)(cusparseHandle_t, int, const double *, const double *, const int *, double *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDaxpyi(cusparseHandle_t handle, int nnz, const double *alpha, const double *xVal, const int *xInd, double *y, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDaxpyi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDaxpyi = (cusparseStatus_t (*)(cusparseHandle_t, int, const double *, const double *, const int *, double *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDaxpyi");
			fprintf(stderr, "wrapper_cusparseDaxpyi:%p\n", wrapper_cusparseDaxpyi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDaxpyi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDaxpyi(handle, nnz, alpha, xVal, xInd, y, idxBase);
		return retval;
	}
}
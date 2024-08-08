#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgthrz)(cusparseHandle_t, int, double *, double *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgthrz(cusparseHandle_t handle, int nnz, double *y, double *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgthrz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgthrz = (cusparseStatus_t (*)(cusparseHandle_t, int, double *, double *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgthrz");
			fprintf(stderr, "wrapper_cusparseDgthrz:%p\n", wrapper_cusparseDgthrz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgthrz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgthrz(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
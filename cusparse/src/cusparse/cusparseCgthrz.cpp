#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgthrz)(cusparseHandle_t, int, cuComplex *, cuComplex *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgthrz(cusparseHandle_t handle, int nnz, cuComplex *y, cuComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgthrz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgthrz = (cusparseStatus_t (*)(cusparseHandle_t, int, cuComplex *, cuComplex *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgthrz");
			fprintf(stderr, "wrapper_cusparseCgthrz:%p\n", wrapper_cusparseCgthrz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgthrz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgthrz(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
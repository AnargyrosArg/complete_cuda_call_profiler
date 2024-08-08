#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZaxpyi)(cusparseHandle_t, int, const cuDoubleComplex *, const cuDoubleComplex *, const int *, cuDoubleComplex *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZaxpyi(cusparseHandle_t handle, int nnz, const cuDoubleComplex *alpha, const cuDoubleComplex *xVal, const int *xInd, cuDoubleComplex *y, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZaxpyi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZaxpyi = (cusparseStatus_t (*)(cusparseHandle_t, int, const cuDoubleComplex *, const cuDoubleComplex *, const int *, cuDoubleComplex *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZaxpyi");
			fprintf(stderr, "wrapper_cusparseZaxpyi:%p\n", wrapper_cusparseZaxpyi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZaxpyi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZaxpyi(handle, nnz, alpha, xVal, xInd, y, idxBase);
		return retval;
	}
}
#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgthr)(cusparseHandle_t, int, const cuDoubleComplex *, cuDoubleComplex *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgthr(cusparseHandle_t handle, int nnz, const cuDoubleComplex *y, cuDoubleComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgthr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgthr = (cusparseStatus_t (*)(cusparseHandle_t, int, const cuDoubleComplex *, cuDoubleComplex *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgthr");
			fprintf(stderr, "wrapper_cusparseZgthr:%p\n", wrapper_cusparseZgthr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgthr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgthr(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgthrz)(cusparseHandle_t, int, cuDoubleComplex *, cuDoubleComplex *, const int *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgthrz(cusparseHandle_t handle, int nnz, cuDoubleComplex *y, cuDoubleComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgthrz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgthrz = (cusparseStatus_t (*)(cusparseHandle_t, int, cuDoubleComplex *, cuDoubleComplex *, const int *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgthrz");
			fprintf(stderr, "wrapper_cusparseZgthrz:%p\n", wrapper_cusparseZgthrz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgthrz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgthrz(handle, nnz, y, xVal, xInd, idxBase);
		return retval;
	}
}
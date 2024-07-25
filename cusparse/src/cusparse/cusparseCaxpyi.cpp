#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCaxpyi)(cusparseHandle_t, int, const cuComplex *, const cuComplex *, const int *, cuComplex *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCaxpyi(cusparseHandle_t handle, int nnz, const cuComplex *alpha, const cuComplex *xVal, const int *xInd, cuComplex *y, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCaxpyi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCaxpyi = (cusparseStatus_t (*)(cusparseHandle_t, int, const cuComplex *, const cuComplex *, const int *, cuComplex *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCaxpyi");
			fprintf(stderr, "wrapper_cusparseCaxpyi:%p\n", wrapper_cusparseCaxpyi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCaxpyi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCaxpyi(handle, nnz, alpha, xVal, xInd, y, idxBase);
		return retval;
	}
}
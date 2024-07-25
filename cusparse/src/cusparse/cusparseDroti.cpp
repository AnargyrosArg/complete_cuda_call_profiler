#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDroti)(cusparseHandle_t, int, double *, const int *, double *, const double *, const double *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDroti(cusparseHandle_t handle, int nnz, double *xVal, const int *xInd, double *y, const double *c, const double *s, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDroti)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDroti = (cusparseStatus_t (*)(cusparseHandle_t, int, double *, const int *, double *, const double *, const double *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDroti");
			fprintf(stderr, "wrapper_cusparseDroti:%p\n", wrapper_cusparseDroti);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDroti():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDroti(handle, nnz, xVal, xInd, y, c, s, idxBase);
		return retval;
	}
}
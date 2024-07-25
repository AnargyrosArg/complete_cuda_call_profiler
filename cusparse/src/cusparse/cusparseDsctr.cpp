#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDsctr)(cusparseHandle_t, int, const double *, const int *, double *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDsctr(cusparseHandle_t handle, int nnz, const double *xVal, const int *xInd, double *y, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDsctr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDsctr = (cusparseStatus_t (*)(cusparseHandle_t, int, const double *, const int *, double *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDsctr");
			fprintf(stderr, "wrapper_cusparseDsctr:%p\n", wrapper_cusparseDsctr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDsctr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDsctr(handle, nnz, xVal, xInd, y, idxBase);
		return retval;
	}
}
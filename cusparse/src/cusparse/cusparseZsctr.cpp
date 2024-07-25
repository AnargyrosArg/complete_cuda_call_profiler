#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZsctr)(cusparseHandle_t, int, const cuDoubleComplex *, const int *, cuDoubleComplex *, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZsctr(cusparseHandle_t handle, int nnz, const cuDoubleComplex *xVal, const int *xInd, cuDoubleComplex *y, cusparseIndexBase_t idxBase) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZsctr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZsctr = (cusparseStatus_t (*)(cusparseHandle_t, int, const cuDoubleComplex *, const int *, cuDoubleComplex *, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZsctr");
			fprintf(stderr, "wrapper_cusparseZsctr:%p\n", wrapper_cusparseZsctr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZsctr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZsctr(handle, nnz, xVal, xInd, y, idxBase);
		return retval;
	}
}
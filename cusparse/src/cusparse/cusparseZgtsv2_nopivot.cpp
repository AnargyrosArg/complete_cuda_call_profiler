#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgtsv2_nopivot)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, cuDoubleComplex *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgtsv2_nopivot(cusparseHandle_t handle, int m, int n, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, cuDoubleComplex *B, int ldb, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgtsv2_nopivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgtsv2_nopivot = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, cuDoubleComplex *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgtsv2_nopivot");
			fprintf(stderr, "wrapper_cusparseZgtsv2_nopivot:%p\n", wrapper_cusparseZgtsv2_nopivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgtsv2_nopivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgtsv2_nopivot(handle, m, n, dl, d, du, B, ldb, pBuffer);
		return retval;
	}
}
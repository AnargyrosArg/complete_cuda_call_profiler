#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgtsv2)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, cuDoubleComplex *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgtsv2(cusparseHandle_t handle, int m, int n, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, cuDoubleComplex *B, int ldb, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgtsv2)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgtsv2 = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, cuDoubleComplex *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgtsv2");
			fprintf(stderr, "wrapper_cusparseZgtsv2:%p\n", wrapper_cusparseZgtsv2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgtsv2():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgtsv2(handle, m, n, dl, d, du, B, ldb, pBuffer);
		return retval;
	}
}
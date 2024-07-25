#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgpsvInterleavedBatch)(cusparseHandle_t, int, int, cuComplex *, cuComplex *, cuComplex *, cuComplex *, cuComplex *, cuComplex *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuComplex *ds, cuComplex *dl, cuComplex *d, cuComplex *du, cuComplex *dw, cuComplex *x, int batchCount, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgpsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgpsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, cuComplex *, cuComplex *, cuComplex *, cuComplex *, cuComplex *, cuComplex *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgpsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseCgpsvInterleavedBatch:%p\n", wrapper_cusparseCgpsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgpsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
		return retval;
	}
}
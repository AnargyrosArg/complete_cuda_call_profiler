#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgtsvInterleavedBatch)(cusparseHandle_t, int, int, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuDoubleComplex *dl, cuDoubleComplex *d, cuDoubleComplex *du, cuDoubleComplex *x, int batchCount, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgtsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgtsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgtsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseZgtsvInterleavedBatch:%p\n", wrapper_cusparseZgtsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgtsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
		return retval;
	}
}
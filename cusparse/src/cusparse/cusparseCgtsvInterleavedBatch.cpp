#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgtsvInterleavedBatch)(cusparseHandle_t, int, int, cuComplex *, cuComplex *, cuComplex *, cuComplex *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuComplex *dl, cuComplex *d, cuComplex *du, cuComplex *x, int batchCount, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgtsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgtsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, cuComplex *, cuComplex *, cuComplex *, cuComplex *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgtsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseCgtsvInterleavedBatch:%p\n", wrapper_cusparseCgtsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgtsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
		return retval;
	}
}
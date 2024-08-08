#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgpsvInterleavedBatch)(cusparseHandle_t, int, int, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuDoubleComplex *ds, cuDoubleComplex *dl, cuDoubleComplex *d, cuDoubleComplex *du, cuDoubleComplex *dw, cuDoubleComplex *x, int batchCount, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgpsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgpsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, cuDoubleComplex *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgpsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseZgpsvInterleavedBatch:%p\n", wrapper_cusparseZgpsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgpsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
		return retval;
	}
}
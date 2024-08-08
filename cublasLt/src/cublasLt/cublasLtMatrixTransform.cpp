#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixTransform)(cublasLtHandle_t, cublasLtMatrixTransformDesc_t, const void *, const void *, cublasLtMatrixLayout_t, const void *, const void *, cublasLtMatrixLayout_t, void *, cublasLtMatrixLayout_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixTransform(cublasLtHandle_t lightHandle, cublasLtMatrixTransformDesc_t transformDesc, const void *alpha, const void *A, cublasLtMatrixLayout_t Adesc, const void *beta, const void *B, cublasLtMatrixLayout_t Bdesc, void *C, cublasLtMatrixLayout_t Cdesc, cudaStream_t stream){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixTransform)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixTransform = (cublasStatus_t (*)(cublasLtHandle_t, cublasLtMatrixTransformDesc_t, const void *, const void *, cublasLtMatrixLayout_t, const void *, const void *, cublasLtMatrixLayout_t, void *, cublasLtMatrixLayout_t, cudaStream_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixTransform");
			fprintf(stderr, "wrapper_cublasLtMatrixTransform:%p\n", wrapper_cublasLtMatrixTransform);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixTransform():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixTransform(lightHandle, transformDesc, alpha, A, Adesc, beta, B, Bdesc, C, Cdesc, stream);
		return retval;
	}
}
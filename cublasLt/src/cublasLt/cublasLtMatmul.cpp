#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmul)(cublasLtHandle_t, cublasLtMatmulDesc_t, const void *, const void *, cublasLtMatrixLayout_t, const void *, cublasLtMatrixLayout_t, const void *, const void *, cublasLtMatrixLayout_t, void *, cublasLtMatrixLayout_t, const cublasLtMatmulAlgo_t *, void *, size_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmul(cublasLtHandle_t lightHandle, cublasLtMatmulDesc_t computeDesc, const void *alpha, const void *A, cublasLtMatrixLayout_t Adesc, const void *B, cublasLtMatrixLayout_t Bdesc, const void *beta, const void *C, cublasLtMatrixLayout_t Cdesc, void *D, cublasLtMatrixLayout_t Ddesc, const cublasLtMatmulAlgo_t *algo, void *workspace, size_t workspaceSizeInBytes, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmul)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmul = (cublasStatus_t (*)(cublasLtHandle_t, cublasLtMatmulDesc_t, const void *, const void *, cublasLtMatrixLayout_t, const void *, cublasLtMatrixLayout_t, const void *, const void *, cublasLtMatrixLayout_t, void *, cublasLtMatrixLayout_t, const cublasLtMatmulAlgo_t *, void *, size_t, cudaStream_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmul");
			fprintf(stderr, "wrapper_cublasLtMatmul:%p\n", wrapper_cublasLtMatmul);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmul():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, beta, C, Cdesc, D, Ddesc, algo, workspace, workspaceSizeInBytes, stream);
		return retval;
	}
}
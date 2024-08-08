#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixTransformDescCreate)(cublasLtMatrixTransformDesc_t *, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixTransformDescCreate(cublasLtMatrixTransformDesc_t *transformDesc, cudaDataType scaleType){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixTransformDescCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixTransformDescCreate = (cublasStatus_t (*)(cublasLtMatrixTransformDesc_t *, cudaDataType)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixTransformDescCreate");
			fprintf(stderr, "wrapper_cublasLtMatrixTransformDescCreate:%p\n", wrapper_cublasLtMatrixTransformDescCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixTransformDescCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixTransformDescCreate(transformDesc, scaleType);
		return retval;
	}
}
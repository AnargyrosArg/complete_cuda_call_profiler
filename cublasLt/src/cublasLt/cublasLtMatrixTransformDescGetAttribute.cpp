#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixTransformDescGetAttribute)(cublasLtMatrixTransformDesc_t, cublasLtMatrixTransformDescAttributes_t, void *, size_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixTransformDescGetAttribute(cublasLtMatrixTransformDesc_t transformDesc, cublasLtMatrixTransformDescAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixTransformDescGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixTransformDescGetAttribute = (cublasStatus_t (*)(cublasLtMatrixTransformDesc_t, cublasLtMatrixTransformDescAttributes_t, void *, size_t, size_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixTransformDescGetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatrixTransformDescGetAttribute:%p\n", wrapper_cublasLtMatrixTransformDescGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixTransformDescGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixTransformDescGetAttribute(transformDesc, attr, buf, sizeInBytes, sizeWritten);
		return retval;
	}
}
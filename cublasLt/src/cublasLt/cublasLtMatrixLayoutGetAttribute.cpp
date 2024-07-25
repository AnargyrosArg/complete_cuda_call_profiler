#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixLayoutGetAttribute)(cublasLtMatrixLayout_t, cublasLtMatrixLayoutAttribute_t, void *, size_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixLayoutGetAttribute(cublasLtMatrixLayout_t matLayout, cublasLtMatrixLayoutAttribute_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixLayoutGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixLayoutGetAttribute = (cublasStatus_t (*)(cublasLtMatrixLayout_t, cublasLtMatrixLayoutAttribute_t, void *, size_t, size_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixLayoutGetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatrixLayoutGetAttribute:%p\n", wrapper_cublasLtMatrixLayoutGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixLayoutGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten);
		return retval;
	}
}
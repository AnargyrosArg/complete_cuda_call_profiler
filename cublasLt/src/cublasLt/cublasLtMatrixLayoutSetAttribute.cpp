#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixLayoutSetAttribute)(cublasLtMatrixLayout_t, cublasLtMatrixLayoutAttribute_t, const void *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixLayoutSetAttribute(cublasLtMatrixLayout_t matLayout, cublasLtMatrixLayoutAttribute_t attr, const void *buf, size_t sizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixLayoutSetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixLayoutSetAttribute = (cublasStatus_t (*)(cublasLtMatrixLayout_t, cublasLtMatrixLayoutAttribute_t, const void *, size_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixLayoutSetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatrixLayoutSetAttribute:%p\n", wrapper_cublasLtMatrixLayoutSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixLayoutSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixLayoutSetAttribute(matLayout, attr, buf, sizeInBytes);
		return retval;
	}
}
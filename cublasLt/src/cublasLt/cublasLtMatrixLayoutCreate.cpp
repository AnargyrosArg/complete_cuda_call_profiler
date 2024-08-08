#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixLayoutCreate)(cublasLtMatrixLayout_t *, cudaDataType, uint64_t, uint64_t, int64_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixLayoutCreate(cublasLtMatrixLayout_t *matLayout, cudaDataType type, uint64_t rows, uint64_t cols, int64_t ld){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixLayoutCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixLayoutCreate = (cublasStatus_t (*)(cublasLtMatrixLayout_t *, cudaDataType, uint64_t, uint64_t, int64_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixLayoutCreate");
			fprintf(stderr, "wrapper_cublasLtMatrixLayoutCreate:%p\n", wrapper_cublasLtMatrixLayoutCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixLayoutCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixLayoutCreate(matLayout, type, rows, cols, ld);
		return retval;
	}
}
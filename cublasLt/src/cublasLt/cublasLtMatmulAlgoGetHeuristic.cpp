#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulAlgoGetHeuristic)(cublasLtHandle_t, cublasLtMatmulDesc_t, cublasLtMatrixLayout_t, cublasLtMatrixLayout_t, cublasLtMatrixLayout_t, cublasLtMatrixLayout_t, cublasLtMatmulPreference_t, int, cublasLtMatmulHeuristicResult_t *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulAlgoGetHeuristic(cublasLtHandle_t lightHandle, cublasLtMatmulDesc_t operationDesc, cublasLtMatrixLayout_t Adesc, cublasLtMatrixLayout_t Bdesc, cublasLtMatrixLayout_t Cdesc, cublasLtMatrixLayout_t Ddesc, cublasLtMatmulPreference_t preference, int requestedAlgoCount, cublasLtMatmulHeuristicResult_t heuristicResultsArray[], int *returnAlgoCount){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulAlgoGetHeuristic)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulAlgoGetHeuristic = (cublasStatus_t (*)(cublasLtHandle_t, cublasLtMatmulDesc_t, cublasLtMatrixLayout_t, cublasLtMatrixLayout_t, cublasLtMatrixLayout_t, cublasLtMatrixLayout_t, cublasLtMatmulPreference_t, int, cublasLtMatmulHeuristicResult_t *, int *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulAlgoGetHeuristic");
			fprintf(stderr, "wrapper_cublasLtMatmulAlgoGetHeuristic:%p\n", wrapper_cublasLtMatmulAlgoGetHeuristic);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulAlgoGetHeuristic():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulAlgoGetHeuristic(lightHandle, operationDesc, Adesc, Bdesc, Cdesc, Ddesc, preference, requestedAlgoCount, heuristicResultsArray, returnAlgoCount);
		return retval;
	}
}
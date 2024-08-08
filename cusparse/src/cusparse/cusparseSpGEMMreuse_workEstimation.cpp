#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpGEMMreuse_workEstimation)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpGEMMreuse_workEstimation(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, cusparseSpMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseSpMatDescr_t matC, cusparseSpGEMMAlg_t alg, cusparseSpGEMMDescr_t spgemmDescr, size_t *bufferSize1, void *externalBuffer1) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpGEMMreuse_workEstimation)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpGEMMreuse_workEstimation = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t, size_t *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpGEMMreuse_workEstimation");
			fprintf(stderr, "wrapper_cusparseSpGEMMreuse_workEstimation:%p\n", wrapper_cusparseSpGEMMreuse_workEstimation);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpGEMMreuse_workEstimation():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpGEMMreuse_workEstimation(handle, opA, opB, matA, matB, matC, alg, spgemmDescr, bufferSize1, externalBuffer1);
		return retval;
	}
}
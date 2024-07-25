#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMMOp_createPlan)(cusparseHandle_t, cusparseSpMMOpPlan_t *, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseDnMatDescr_t, cudaDataType, cusparseSpMMOpAlg_t, const void *, size_t, const void *, size_t, const void *, size_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMMOp_createPlan(cusparseHandle_t handle, cusparseSpMMOpPlan_t *plan, cusparseOperation_t opA, cusparseOperation_t opB, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, cusparseDnMatDescr_t matC, cudaDataType computeType, cusparseSpMMOpAlg_t alg, const void *addOperationNvvmBuffer, size_t addOperationBufferSize, const void *mulOperationNvvmBuffer, size_t mulOperationBufferSize, const void *epilogueNvvmBuffer, size_t epilogueBufferSize, size_t *SpMMWorkspaceSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMMOp_createPlan)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMMOp_createPlan = (cusparseStatus_t (*)(cusparseHandle_t, cusparseSpMMOpPlan_t *, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseDnMatDescr_t, cudaDataType, cusparseSpMMOpAlg_t, const void *, size_t, const void *, size_t, const void *, size_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMMOp_createPlan");
			fprintf(stderr, "wrapper_cusparseSpMMOp_createPlan:%p\n", wrapper_cusparseSpMMOp_createPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMMOp_createPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMMOp_createPlan(handle, plan, opA, opB, matA, matB, matC, computeType, alg, addOperationNvvmBuffer, addOperationBufferSize, mulOperationNvvmBuffer, mulOperationBufferSize, epilogueNvvmBuffer, epilogueBufferSize, SpMMWorkspaceSize);
		return retval;
	}
}
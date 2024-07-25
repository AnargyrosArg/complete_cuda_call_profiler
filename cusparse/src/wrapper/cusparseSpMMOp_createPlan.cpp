#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMMOp_createPlan(cusparseHandle_t handle, cusparseSpMMOpPlan_t *plan, cusparseOperation_t opA, cusparseOperation_t opB, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, cusparseDnMatDescr_t matC, cudaDataType computeType, cusparseSpMMOpAlg_t alg, const void *addOperationNvvmBuffer, size_t addOperationBufferSize, const void *mulOperationNvvmBuffer, size_t mulOperationBufferSize, const void *epilogueNvvmBuffer, size_t epilogueBufferSize, size_t *SpMMWorkspaceSize)
{
	cusparseStatus_t retval = cusparseSpMMOp_createPlan(handle, plan, opA, opB, matA, matB, matC, computeType, alg, addOperationNvvmBuffer, addOperationBufferSize, mulOperationNvvmBuffer, mulOperationBufferSize, epilogueNvvmBuffer, epilogueBufferSize, SpMMWorkspaceSize);
	return retval;
}
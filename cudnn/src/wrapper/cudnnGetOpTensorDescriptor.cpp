#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetOpTensorDescriptor(const cudnnOpTensorDescriptor_t opTensorDesc, cudnnOpTensorOp_t *opTensorOp, cudnnDataType_t *opTensorCompType, cudnnNanPropagation_t *opTensorNanOpt)
{
	cudnnStatus_t retval = cudnnGetOpTensorDescriptor(opTensorDesc, opTensorOp, opTensorCompType, opTensorNanOpt);
	return retval;
}
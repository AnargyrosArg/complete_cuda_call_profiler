#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMMOp(cusparseSpMMOpPlan_t plan, void *externalBuffer)
{
	cusparseStatus_t retval = cusparseSpMMOp(plan, externalBuffer);
	return retval;
}
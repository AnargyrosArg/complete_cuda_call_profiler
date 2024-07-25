#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMMOp_destroyPlan(cusparseSpMMOpPlan_t plan)
{
	cusparseStatus_t retval = cusparseSpMMOp_destroyPlan(plan);
	return retval;
}
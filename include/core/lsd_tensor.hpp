/*!
 * @file lsd_tensor.hpp
 *
 * @author David Losteiner
 * @date 2015.11.18.
 *
 * Basic tensor indexing up to 4 dimenesion at compile time.
 * Original:
 *      http://www.sitmo.com/article/a-simple-and-extremely-fast-c-template-for-matrices-and-tensors/
 *
 */

#pragma once

#include "lsd_types"

namespace lsd
{

	template <uint32_t Dim1,uint32_t Dim2=1,uint32_t Dim3=1,uint32_t Dim4=1>
	class TensorIndex {
        
        public:
            enum {SIZE = Dim1*Dim2*Dim3*Dim4 };
            enum {DIM1 = Dim1 };
            enum {DIM2 = Dim2 };
            enum {DIM3 = Dim3 };
            enum {DIM4 = Dim4 };
        
            static uint32_t indexOf(const uint32_t i) { 
            return i;
            }
            static uint32_t indexOf(const uint32_t i,const uint32_t j) {
            return j*Dim1 + i;
            }
            static uint32_t indexOf(const uint32_t i,const uint32_t j, const uint32_t k) {
            return (k*Dim2 + j)*Dim1 + i;
            }
            static uint32_t indexOf(const uint32_t i,const uint32_t j, const uint32_t k,const uint32_t l) {
            return ((l*Dim3 + k)*Dim2 + j)*Dim1 + i;
            }
	};

}

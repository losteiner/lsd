/*!
 * @file lsd_circularbuffer.hpp
 *
 * @author David Losteiner
 * @date 2015.02.11.
 *
 * This implements fixed size ring buffer container.
 *
 */
 
 #pragma once

/// Include section
#include "lsd/core/lsd_types.hpp"


namespace lsd
{
    template<class ElementType, lsd::uint32_t SIZE>
    class TRingBuffer
    {
        public:
            TRingBuffer():
                m_capacity_ui32(SIZE),
                m_size_ui32(0),
                m_head_p(&m_buffer[SIZE-1]),
                m_tail_p(&m_buffer[0])
            {
                
            }
            
            virtual ~TRingBuffer()
            {
            }
            
            
            void push(const ElementType& f_element_r)
            {
                // If the head points to the end of buffer
                if(m_head_p == &m_buffer[SIZE-1])
                {
                    // Set head to the first position
                    m_head_p = &m_buffer[0];
                }
                else
                {
                    // Increase head pointer
                    ++m_head_p;
                }
                
                // Align the tail pointer
                if(m_size_ui32 == m_capacity_ui32)
                {
                    if(m_tail_p == &m_buffer[SIZE-1])
                    {
                        // Set tail to the first position
                        m_tail_p = &m_buffer[0];
                    }
                    else
                    {
                        ++m_tail_p;
                    }
                }
                
                // Put the element in to head position
                *m_head_p = f_element_r;
                
                if(m_size_ui32 < m_capacity_ui32 )
                {
                    ++m_size_ui32;
                }            
                
            }
            
            bool pop(ElementType& f_element_r)
            {
                
                f_element_r = *m_tail_p;
                
                if(m_tail_p == &m_buffer[SIZE-1])
                {
                    // Set tail to the first position
                    m_tail_p = &m_buffer[0];
                }
                else
                {
                    ++m_tail_p;
                }
                
                if(m_size_ui32 >= 0 )
                {
                    --m_size_ui32;
                } 
                
            }
            
            ElementType& back() const
            {
                // TODO: Implement back (oldest element)
                return *m_tail_p;
            }
            
            ElementType& front() const
            {
                // TODO: Implement front (newest element)
                return *m_head_p;
            }
            
        const lsd::uint32_t size() const
        {
            return m_size_ui32;
        }
                
        private:
            ElementType m_buffer[SIZE];
            const lsd::uint32_t m_capacity_ui32;
            lsd::uint32_t m_size_ui32;
            ElementType* m_head_p;
            ElementType* m_tail_p;

            
    };
    
    //typedef TRingBuffer<ElementType> CRingBuffer;
}

/*!
 * @file lsd_bitfieldcounter.hpp
 *
 * @author David Losteiner
 * @date 2014.08.11.
 *
 * This implements a compact time framed counter that works on a bitfield.
 *
 */

#pragma once

/// Include section
#include "lsd/core/lsd_types.hpp"


namespace lsd
{

	/*!
	 * @class CBitfieldCounter
	 * @brief Counts logical value in a time frame.
	 *
	 * The bitfield counter manages the logical values that comes via the update function.
	 *
	 * @tparam IntegerType An integer that enough large for timeframe (eg.: uint32_t, uint64_t)
	 * @tparam TimeFrame The size of timeframe (less than IntegerType bits!)
	 */
	template <typename IntegerType, uint32_t TimeFrame>
	class CBitfieldCounter
	{
	public:

		/// C'tor
		CBitfieldCounter():
			m_count_u8(0),
			m_storage_t(static_cast<IntegerType>(0))
		{
			/// Creating a mask for given time frame
			m_maskOfFrame_t = static_cast<IntegerType>(0);
			for(uint8_t l_idx_u8=0; l_idx_u8 < TimeFrame; ++l_idx_u8)
			{
				m_maskOfFrame_t <<= 1;
				m_maskOfFrame_t |= static_cast<IntegerType>(0x1);
			}

		}

#ifdef LSD_DEBUG
		/*!
		* @brief Add a new value to storage.
		* @note This only for debug purpose.
		*/
		inline
		const IntegerType getMask(void) const
		{
			return m_maskOfFrame_t;
		}
#endif

		/*!
		 * @brief Returns the counted true values in windowed storage.
		 * @return Counted true values (uint8_t).
		 */
		inline
		const uint8_t get(void) const
		{
			return m_count_u8;
		}


		/*!
		 * @brief Add a new value to storage.
		 *
		 * The function updates the bit storage and updates the counter.
		 *
		 * @param[in] f_value_b The current logical value
		 * \note The counter is uint8_t
		 */
		inline
		void update(bool f_value_b)
		{
			/// Shift the storage bits
			m_storage_t <<= 1;

			/// Decrement if a true value left the time frame
			if(0x1 == ((m_storage_t+1) >> TimeFrame))
			{
				--m_count_u8;
			}

			/// Toggle the current storage bit
			if(true == f_value_b)
			{
				++m_count_u8;
				m_storage_t |= 0x00000001;
			}
			else
			{
				m_storage_t |= 0x00000000;
			}

			/// Mask out according to time frame
			m_storage_t &= m_maskOfFrame_t;

			// @todo: count the ones according to architecture
		}

	protected:
		uint8_t		m_count_u8;			///< Counter for true values in time frame.
		IntegerType	m_storage_t;		///< The inner storage of bitfield.
		IntegerType	m_maskOfFrame_t;	///< The storage mask for the time frame.
	};


}

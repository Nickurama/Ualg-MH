#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace Problems
{
	class BitArray
	{
	private:
		size_t m_true_size;
		size_t m_size_bits;
		std::unique_ptr<unsigned long[]> m_arr;

		static inline void copyMemberArray(BitArray& to, const BitArray& from);
		static inline size_t getTrueIndexFromBit(size_t k);
		static inline char getBitIndex(size_t k);
		inline void clearMemberArray();
		inline void verify(size_t k) const;

	public:
		BitArray(size_t size);
		BitArray(const BitArray& other);
		BitArray(BitArray&& other) = default;
		~BitArray() = default;
		BitArray& operator=(const BitArray& other);
		BitArray& operator=(BitArray&& other);

		inline bool get(size_t k) const;
		inline void set(size_t k, bool val);
		inline void invert(size_t k);
		inline void increment();

		inline size_t size() const;

		inline bool operator[](size_t index) const;
		inline bool operator==(const BitArray& other) const;
	};
}

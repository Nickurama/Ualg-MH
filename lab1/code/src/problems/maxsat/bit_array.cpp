#include "problems/maxsat/bit_array.hpp"
#include <cstring>

using namespace Problems;

BitArray::BitArray(size_t size) :
	m_true_size((size + (sizeof(unsigned long) * 8) - 1) / (sizeof(unsigned long) * 8)), // will do +1 when there's a remainder by the division
	m_size_bits(size),
	m_arr(std::make_unique_for_overwrite<unsigned long[]>(m_true_size))
{
	clearMemberArray();
}

inline void BitArray::copyMemberArray(BitArray& to, const BitArray& from)
{
	memcpy(to.m_arr.get(), from.m_arr.get(), to.m_true_size * sizeof(unsigned long));
}

inline void BitArray::clearMemberArray()
{
	memset(m_arr.get(), 0, m_true_size * sizeof(unsigned long));
}

BitArray::BitArray(const BitArray& other) :
	m_true_size(other.m_true_size),
	m_size_bits(other.m_size_bits),
	m_arr(std::make_unique_for_overwrite<unsigned long[]>(other.m_true_size))
{
	copyMemberArray(*this, other);
}

BitArray& BitArray::operator=(const BitArray& other)
{
	m_true_size = other.m_true_size;
	m_size_bits = other.m_size_bits;
	m_arr = std::make_unique_for_overwrite<unsigned long[]>(other.m_true_size);
	copyMemberArray(*this, other);
	return *this;
}

BitArray& BitArray::operator=(BitArray&& other)
{
	m_true_size = std::move(other.m_true_size);
	m_size_bits = std::move(other.m_size_bits);
	m_arr = std::move(other.m_arr);
	return *this;
}

inline void BitArray::verify(size_t k) const
{
	if (k >= m_size_bits || k < 0)
		throw std::out_of_range("index " + std::to_string(k) + " out of range for " + std::to_string(m_size_bits) + ".");
}

inline size_t BitArray::getTrueIndexFromBit(size_t k)
{
	return k / (sizeof(unsigned long) * 8);
}

inline char BitArray::getBitIndex(size_t k)
{
	return k % (sizeof(unsigned long) * 8);
}

inline bool BitArray::get(size_t k) const
{
	verify(k);
	return (m_arr[getTrueIndexFromBit(k)] >> getBitIndex(k)) & 1ul;
}

inline void BitArray::set(size_t k, bool value)
{
	verify(k);
	size_t true_index = getTrueIndexFromBit(k);
	char bit_index = getBitIndex(k);
	m_arr[true_index] = (m_arr[true_index] & ~(1ul << bit_index)) | ((unsigned long)value << bit_index);
	// m_arr[true_index] = value ? m_arr[true_index] | (1ul << getBitIndex(k)) : m_arr[true_index] & ~(1ul << getBitIndex(k));
}

inline void BitArray::invert(size_t k)
{
	verify(k);
	size_t true_index = getTrueIndexFromBit(k);
	m_arr[true_index] = m_arr[true_index] ^ (1ul << getBitIndex(k));
}

inline void BitArray::increment()
{
	for (size_t i = 0; i < m_true_size; i++)
		if (m_arr[i]++ == ~0ul) break;
}

inline size_t BitArray::size() const
{
	return m_size_bits;
}

inline bool BitArray::operator[](size_t k) const
{
	verify(k);
	return get(k);
}

#include "problems/maxsat/bit_array.hpp"
#include <cstring>

using namespace Problems;

BitArray::BitArray(size_t size) :
	m_true_size((size + (sizeof(uint64_t) * 8) - 1) / (sizeof(unsigned long) * 8)), // will do +1 when there's a remainder by the division
	m_size_bits(size),
	m_arr(std::make_unique_for_overwrite<uint64_t[]>(m_true_size))
{
	clearMemberArray();
}

void BitArray::copyMemberArray(BitArray& to, const BitArray& from)
{
	memcpy(to.m_arr.get(), from.m_arr.get(), to.m_true_size * sizeof(uint64_t));
}

void BitArray::clearMemberArray()
{
	memset(m_arr.get(), 0, m_true_size * sizeof(uint64_t));
}

BitArray::BitArray(const BitArray& other) :
	m_true_size(other.m_true_size),
	m_size_bits(other.m_size_bits),
	m_arr(std::make_unique_for_overwrite<uint64_t[]>(other.m_true_size))
{
	copyMemberArray(*this, other);
}

BitArray& BitArray::operator=(const BitArray& other)
{
	m_true_size = other.m_true_size;
	m_size_bits = other.m_size_bits;
	m_arr = std::make_unique_for_overwrite<uint64_t[]>(other.m_true_size);
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

void BitArray::verify(size_t k) const
{
	if (k >= m_size_bits) // no need to check for k < 0 since it's unsigned
		throw std::out_of_range("index " + std::to_string(k) + " out of range for " + std::to_string(m_size_bits) + ".");
}

size_t BitArray::getTrueIndexFromBit(size_t k)
{
	return k / (sizeof(uint64_t) * 8);
}

char BitArray::getBitIndex(size_t k)
{
	return k % (sizeof(uint64_t) * 8);
}

bool BitArray::get(size_t k) const
{
	verify(k);
	return (m_arr[getTrueIndexFromBit(k)] >> getBitIndex(k)) & 1ul;
}

void BitArray::set(size_t k, bool value)
{
	verify(k);
	size_t true_index = getTrueIndexFromBit(k);
	char bit_index = getBitIndex(k);
	m_arr[true_index] = (m_arr[true_index] & ~(1ul << bit_index)) | ((uint64_t)value << bit_index);
	// m_arr[true_index] = value ? m_arr[true_index] | (1ul << getBitIndex(k)) : m_arr[true_index] & ~(1ul << getBitIndex(k));
}

void BitArray::flip(size_t k)
{
	verify(k);
	size_t true_index = getTrueIndexFromBit(k);
	m_arr[true_index] = m_arr[true_index] ^ (1ul << getBitIndex(k));
}

void BitArray::increment()
{
	for (size_t i = 0; i < m_true_size; i++)
		if (m_arr[i]++ == ~0ul) break;
}

size_t BitArray::size() const
{
	return m_size_bits;
}

bool BitArray::operator[](size_t k) const
{
	return get(k);
}

bool BitArray::operator==(const BitArray& other) const
{
	return this->m_size_bits == other.m_size_bits ? memcmp(this->m_arr.get(), other.m_arr.get(), this->m_true_size * sizeof(uint64_t)) : false;
}

size_t BitArray::hash() const
{
	size_t seed = m_true_size;
	for (size_t i = 0; i < m_true_size; i++)
	{
		seed ^= std::hash<uint64_t>{}(m_arr[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2); // integral part of the golden ratio's fractional part
	}
	return seed;
}

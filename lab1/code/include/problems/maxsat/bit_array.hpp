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
		std::unique_ptr<uint64_t[]> m_arr;

		static void copyMemberArray(BitArray& to, const BitArray& from);
		static size_t getTrueIndexFromBit(size_t k);
		static char getBitIndex(size_t k);
		void clearMemberArray();
		void verify(size_t k) const;

	public:
		BitArray(size_t size);
		BitArray(const BitArray& other);
		BitArray(BitArray&& other) = default;
		~BitArray() = default;
		BitArray& operator=(const BitArray& other);
		BitArray& operator=(BitArray&& other);
		BitArray& operator++();

		bool get(size_t k) const;
		void set(size_t k, bool val);
		void flip(size_t k);
		void increment();

		size_t hash() const;
		size_t size() const;
		std::string str() const;

		bool operator[](size_t index) const;
		bool operator==(const BitArray& other) const;
		// std::ostream& operator<<(std::ostream& os);
		// friend std::ostream& operator<<(std::ostream& os, const BitArray& obj);
	};
}

std::ostream& operator<<(std::ostream& os, const Problems::BitArray& obj);

namespace std
{
	template<>
	struct hash<Problems::BitArray>
	{
		size_t operator()(const Problems::BitArray &bit_arr) const
		{
			return bit_arr.hash();
		}
	};
}


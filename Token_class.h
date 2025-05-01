#pragma once
#include <cstdint> // �������� � ������

class Token {
private:
	uint16_t offset; // �������� ���
	uint8_t length;  // �������� ���
	char next_char;
public:
	Token(uint16_t offset, uint8_t len, char n_char)
		: offset(offset), length(len), next_char(n_char) {}

	uint16_t get_offset() const { return offset; }
	uint8_t get_length() const { return length; }
	char get_char() const { return next_char; }
};
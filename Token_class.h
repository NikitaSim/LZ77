class Token {
private:
	size_t offset;
	size_t length;
	char next_char;
public:
	Token(size_t offset, size_t len, char n_char) : offset(offset), length(len), next_char(n_char){}
	size_t get_offset() const { return offset; }
	size_t get_length() const { return length; }
	char get_char() const { return next_char; }
};
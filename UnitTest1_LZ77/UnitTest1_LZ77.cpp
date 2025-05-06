#include "pch.h"
#include "CppUnitTest.h"
#include "../SFML_PROJECT/LZ77.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1LZ77
{
	TEST_CLASS(UnitTest1LZ77)
	{
	public:
		
        TEST_METHOD(EmptyStringTest)
        {
            std::string input = "";
            auto compressed = encode(input);
            auto decompressed = decode(compressed);
            Assert::AreEqual(input, decompressed);
            Assert::IsTrue(compressed.empty());
        }

        TEST_METHOD(SingleCharacterTest)
        {
            std::string input = "X";
            auto compressed = encode(input);
            auto decompressed = decode(compressed);
            Assert::AreEqual(input, decompressed);
            Assert::AreEqual((size_t)1, compressed.size());
            Assert::AreEqual('X', compressed[0].get_char());
        }

        TEST_METHOD(RepeatingPatternTest)
        {
            std::string input(10, 'A');
            auto compressed = encode(input);
            auto decompressed = decode(compressed);
            Assert::AreEqual(input, decompressed);
            Assert::IsTrue(compressed.size() < 5);
        }

        TEST_METHOD(InvalidTokenTest)
        {
            std::vector<Token> broken_tokens = { Token(1000, 5, 'X') };
            auto func = [&] { decode(broken_tokens); };
            Assert::ExpectException<std::runtime_error>(func);
        }

        TEST_METHOD(NoRepeatsTest)
        {
            // Тест строки без повторений
            std::string input = "ABCDEFGHIJKL";
            auto compressed = encode(input);
            auto decompressed = decode(compressed);

            // Проверяем что декодированная строка совпадает
            Assert::AreEqual(input, decompressed);

            // Проверяем что каждый символ закодирован как отдельный токен
            Assert::AreEqual(input.size(), compressed.size());
            for (size_t i = 0; i < compressed.size(); ++i) {
                Assert::AreEqual((uint16_t)0, compressed[i].get_offset());
                Assert::AreEqual((uint8_t)0, compressed[i].get_length());
                Assert::AreEqual(input[i], compressed[i].get_char());
            }
        }

        TEST_METHOD(CyclicCopyTest)
        {

            std::string expected = "ABABABAB"; // A B (AB copied 3 times)

            auto compressed = encode(expected);
            auto decompressed = decode(compressed);

            Assert::AreEqual(expected, decompressed);
        }

        TEST_METHOD(BoundaryValuesTest)
        {
            // Тест граничных значений
            std::string input(4096 + 18, 'A'); // window_size + lookahead
            auto compressed = encode(input);

            // Проверяем что последний токен использует максимальный offset
            bool has_max_offset = false;
            for (const auto& t : compressed) {
                if (t.get_offset() == 4096) {
                    has_max_offset = true;
                    break;
                }
            }
            Assert::IsTrue(has_max_offset);

            auto decompressed = decode(compressed);
            Assert::AreEqual(input, decompressed);
        }
	};
}

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

static std::map<unsigned int, std::string> NumPad = {
      {2, "abc"}
    , {3, "def"}
    , {4, "ghi"}
    , {5, "jkl"}
    , {6, "mno"}
    , {7, "pqrs"}
    , {8, "tuv"}
    , {9, "wxyz"}
};

std::vector<unsigned short> GetDigits(const unsigned int& n)
{
    std::vector<unsigned short> digits;
    if (n > 0) {
        auto prev = GetDigits(n / 10);
        digits.insert(digits.end(), prev.begin(), prev.end());
        digits.push_back(n % 10);
    }

    return digits;
}

std::vector<std::string> DigitsToChars(const std::vector<unsigned short> &digits)
{
	std::vector<std::string> result;

	std::for_each(digits.begin(), digits.end(), [&result](const unsigned short& digit)
		{
            if (NumPad[digit].length() > 0) {
                result.push_back(NumPad[digit]);
            }
		});

	return result;
}

void GetSequences(const std::vector<std::string>& keys, std::string sequence, const size_t index, std::unordered_set<std::string>& oSequences)
{
	static const auto letters = keys.size();
	if (letters > 0) {
		std::vector<char> seq(letters + 1);
        std::copy(sequence.begin(), sequence.end(), seq.begin());

		const auto count = keys[index].size();
		for (size_t i = 0; i < count; ++i) {
			seq[index] = keys[index][i];
			sequence = seq.data();
            if (sequence.length() == letters) {
                oSequences.insert(sequence);
            }
			if (index < letters - 1) {
				GetSequences(keys, sequence, index + 1, oSequences);
			}
		}
	}
}

std::unordered_set<std::string> GetAllStrings(const std::vector<std::string>& keys)
{
    std::unordered_set<std::string> result;
	GetSequences(keys, "", 0, result);

    return result;
}

std::unordered_set<std::string> GetStringsNumPad(const unsigned int& n)
{
	const auto digits = GetDigits(n);
	const auto digChars = DigitsToChars(digits);
    auto result = GetAllStrings(digChars);

    return result;
}

int main()
{
    unsigned int n;
    std::cin >> n;

    auto combinations = GetStringsNumPad(n);
	
    for (const auto& vStr : combinations) {
        std::cout << vStr << std::endl;
    }
    std::cout << std::endl << "count : " << combinations.size();

    return 0;
}

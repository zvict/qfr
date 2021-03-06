#include "algorithms/BernsteinVazirani.hpp"
#include "gtest/gtest.h"
class BernsteinVazirani : public testing::TestWithParam<int> {
protected:
	void TearDown() override {}
	void SetUp() override {}
};

INSTANTIATE_TEST_SUITE_P(BernsteinVazirani, BernsteinVazirani,
	testing::Values(0ull,						// Zero-Value
		3ull, 63ull, 170ull,					// 0-bit < hInt <= 8-bit
		819ull, 4032ull, 33153ull,				// 8-bit < hInt <= 16-bit
		87381ull, 16777215ull, 1234567891011ull	// 16-bit < hInt <= 32-bit
		),
	[](const testing::TestParamInfo<BernsteinVazirani::ParamType>& info) {

		// Generate names for test cases
		int hInt = info.param;
		std::stringstream ss{};
		ss << hInt << "_HiddenInteger";
		return ss.str();
	});

TEST_P(BernsteinVazirani, FunctionTest) {
	std::bitset<64> hInt = GetParam();
	auto dd = std::make_unique<dd::Package>();
	std::unique_ptr<qc::BernsteinVazirani> qc;
	dd::Edge e{};

	// Create the QuantumCircuite with the hidden integer
	ASSERT_NO_THROW({ qc = std::make_unique<qc::BernsteinVazirani>(hInt.to_ulong()); });
	qc->printStatistics(std::cout);
	ASSERT_NO_THROW({ e = qc->buildFunctionality(dd); });
	
	// Test the Number of Operations & the number of Qubits
	ASSERT_EQ(qc->getNops(), qc->size * 2 + hInt.count());
	ASSERT_EQ(qc->getNqubits(), qc->size);

	dd::Edge r = dd->multiply(e, dd->makeZeroState(qc->size));
	std::string hIntPath = std::string(qc->size, '0');

	// Create the path-string
	for (unsigned int i = 0; i < qc->size; i++)
	{
		if (hInt[i] == 1) {
			hIntPath[i] = '2';
		}
	}

	// Test the path
	EXPECT_EQ(dd->getValueByPath(r, hIntPath), (dd::ComplexValue{ 1, 0 }));
}

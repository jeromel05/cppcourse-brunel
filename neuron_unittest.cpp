#include <iostream>
#include "neuron.hpp"
#include "cmath"
#include "gtest/include/gtest/gtest.h"

TEST (neuron_unittest, MembranePotential) {
	Neuron neuron;
	
	neuron.update(0.0, 1, 1.0);
	
	EXPECT_EQ(((1.0-std::exp(-0.1 / 20.0)) * 20.0 ), neuron.getMbPotential());
}

TEST (neuron_unittest, SpikeTime) {
	Neuron neuron;
	int i(0);
	
	while(i < 1000){
		neuron.update(i, 1, 1.01);
		++i;
	}
	std::cerr << "taille: " << neuron.getTimeSpikes().size() << std::endl;
	
	EXPECT_EQ(92.4, neuron.getSingleSpikeTime(1));
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



#include <iostream>
#include "neuron.hpp"
#include "cmath"
#include "gtest/include/gtest/gtest.h"

TEST (neuron_unittest, MembranePotential) {
	Neuron neuron;
	
	neuron.set_i_ext(1.0);
	neuron.update(1);
	
	EXPECT_EQ(((1.0-std::exp(-0.1 / 20.0)) * 20.0 ), neuron.getMbPotential());
}

TEST (neuron_unittest, SpikeTime) {
	Neuron neuron;
	
	neuron.set_i_ext(1.01);
	neuron.update(4000);
	std::cerr << "taille: " << neuron.getTimeSpikes().size() << std::endl;
	
	EXPECT_EQ(92.4, neuron.getSingleSpikeTime(1));
	EXPECT_NEAR(185.100 - 1E-3, neuron.getSingleSpikeTime(2), 185.100 + 1E-3); //pas posiible de faible l'égalité exacte avec ce nb
	EXPECT_EQ(277.7, neuron.getSingleSpikeTime(3));
	EXPECT_EQ(370.3, neuron.getSingleSpikeTime(4));
}

TEST (neuron_unittest, SpikeTimeV2) {
	Neuron neuron;
	
	neuron.set_i_ext(1.01);
	neuron.update(924);
	
	EXPECT_EQ(0, neuron.getTimeSpikes().size());
	neuron.update(1);
	EXPECT_EQ(1, neuron.getTimeSpikes().size());
}

TEST (neuron_unittest, RestingPotential) {
	Neuron neuron;
	
	neuron.set_i_ext(0.0);
	neuron.update(4000);
	
	EXPECT_NEAR(0, neuron.getMbPotential(), 1E-3);
}

TEST (neuron_unittest, NoSpikes) {
	Neuron neuron;
	
	neuron.set_i_ext(1.0);
	neuron.update(4000);
	
	EXPECT_EQ(0, neuron.getTimeSpikes().size());
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



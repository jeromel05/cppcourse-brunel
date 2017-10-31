#include <iostream>
#include "neuron.hpp"
#include "cmath"
#include "gtest/include/gtest/gtest.h"

//WARNING: The background noise has to be disabled for the tests to work!
/**
 * Series of tests verifying that:
 * 	- No spike if i_ext == 1.0
 *  - Spikes arrive at right time with i_ext == 1.01
 *  - Mb potential decreases to 0 with i_ext == 0.0
 */

TEST (neuron_unittest, MembranePotential) {
	Neuron neuron;
	
	neuron.set_i_ext(1.0);
	neuron.update(1);
	
	EXPECT_EQ(((1.0-std::exp(-0.1 / 20.0)) * 20.0 ), neuron.getMbPotential());
}

TEST (neuron_unittest, SpikeTime) {
	Neuron neuron;
	
	neuron.set_i_ext(1.01);
	neuron.update(5000);
	
	EXPECT_EQ(92.4, neuron.getSingleSpikeTime(1) * h);
	EXPECT_NEAR(185.100 - 1E-3, neuron.getSingleSpikeTime(2) * h, 185.100 + 1E-3); //pas possible de faible l'égalité exacte avec ce nb
	EXPECT_EQ(277.7, neuron.getSingleSpikeTime(3) * h);
	EXPECT_EQ(370.3, neuron.getSingleSpikeTime(4) * h);
}

TEST (neuron_unittest, SpikeTimeV2) {
	Neuron neuron;
	
	neuron.set_i_ext(1.01);
	neuron.update(924);
	
	EXPECT_EQ(0, neuron.getTimeSpikes().size());
	neuron.update(1);
	EXPECT_EQ(1, neuron.getNbSpikes());
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

TEST (neuron_unittest, excitatory_buffer_test){
	Neuron neuron;
	
	neuron.fill_buffer(0.0, J_E);
	neuron.update(15);
	
	EXPECT_EQ(0.1, neuron.getMbPotential());
}

TEST (neuron_unittest, inhibitory_buffer_test){
	Neuron neuron;
	
	neuron.fill_buffer(0.0, J_I);
	neuron.update(15);
	
	EXPECT_NEAR(0, neuron.getMbPotential(), 1E-3);
}

TEST (neuron_unittest, SpikeCausedbyBuffer){
	Neuron neuron;
	
	neuron.fill_buffer(0.0, 20.1);
	neuron.update(16);
	
	EXPECT_EQ(1, neuron.getNbSpikes());
}

TEST (neuron_unittest, Neuron_type){
	Neuron N_E(true);
	Neuron N_I(false);
	
	EXPECT_TRUE(N_E.isExitatory());
	EXPECT_FALSE(!N_I.isExitatory());
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



#include <iostream>
#include "network.hpp"
#include "neuron.hpp"
#include "cmath"
#include "gtest/include/gtest/gtest.h"

//NOTICE: The poisson distibution has been disabled in this test in order to obtain predictable results
/**
 * Series of tests verifying that:
 * 	- No spike if i_ext == 1.0
 *  - Spikes arrive at right time with i_ext == 1.01
 *  - Mb potential decreases to 0 with i_ext == 0.0
 *  - If the buffer system works proprerly and is able to cause spikes
 *  - If the Inhibitory and excitatory neurons send signals with the correct amplitude J
 *  - If there is no negative MbPotential
 *  - If we are able to correctly create inhibitory and excitatory neurons
 *  - If the netork has the correct number of excitatoy and inhibitory neurons
 *  - If the neuron firing rate is approximatively correct
 *  - If the connection function works properly
 *  - The buffer is put back to 0 after it has been used
 */

TEST (neuron_unittest, MembranePotential) {
	Neuron neuron(0, true, false);
	
	neuron.set_i_ext(1.0);
	neuron.update(1);
	
	EXPECT_EQ(((1.0-std::exp(-0.1 / 20.0)) * 20.0 ), neuron.getMbPotential());
}

TEST (neuron_unittest, SpikeTime) {
	Neuron neuron(0, true, false);
	
	neuron.set_i_ext(1.01);
	neuron.update(5000);
	
	EXPECT_EQ(92.4, neuron.getSingleSpikeTime(1) * h);
	EXPECT_NEAR(185.100 - 1E-3, neuron.getSingleSpikeTime(2) * h, 185.100 + 1E-3); //pas possible de faible l'égalité exacte avec ce nb
	EXPECT_EQ(281.3, neuron.getSingleSpikeTime(3) * h);
	EXPECT_NEAR(375.700 - 1E-3, neuron.getSingleSpikeTime(2) * h, 375.700 + 1E-3);
}

TEST (neuron_unittest, SpikeTimeV2) {
	Neuron neuron(0, true, false);
	
	neuron.set_i_ext(1.01);
	neuron.update(924);
	
	EXPECT_EQ(0, neuron.getTimeSpikes().size());
	neuron.update(1);
	EXPECT_EQ(1, neuron.getNbSpikes());
}

TEST (neuron_unittest, RestingPotential) {
	Neuron neuron(0, true, false);
	
	neuron.set_i_ext(0.0);
	neuron.update(4000);
	
	EXPECT_NEAR(0, neuron.getMbPotential(), 1E-3);
}

TEST (neuron_unittest, NoSpikes) {
	Neuron neuron(0, true, false);
	
	neuron.set_i_ext(1.0);
	neuron.update(4000);
	
	EXPECT_EQ(0, neuron.getTimeSpikes().size());
}

TEST (neuron_unittest, excitatory_buffer_test){
	Neuron neuron(0, true, false);
	
	neuron.fill_buffer(0.0, J_E);
	neuron.update(15);
	
	EXPECT_EQ(0.1, neuron.getMbPotential());
	
	for(size_t i(0); i < D+1 ; ++i){
		EXPECT_NEAR(0, neuron.getBufferCase(i), 1E-3);
	}
}

TEST (neuron_unittest, inhibitory_buffer_test){
	Neuron neuron(0, true, false);
	
	neuron.fill_buffer(0.0, J_I);
	neuron.update(15);
	
	EXPECT_NEAR(0, neuron.getMbPotential(), 1E-3);
}

TEST (neuron_unittest, SpikeCausedbyBuffer){
	Neuron neuron(0, true, false);
	
	neuron.fill_buffer(0.0, 20.1);
	neuron.update(16);					//we need to update one more step for the neuron to fire
	
	EXPECT_EQ(1, neuron.getNbSpikes());
}

TEST (neuron_unittest, Neuron_type){
	Neuron N_E(0, true, false);
	Neuron N_I(1, false, false);
	
	EXPECT_TRUE(N_E.isExitatory());
	EXPECT_FALSE(N_I.isExitatory());
}

TEST (neuron_unittest, NeuronFiringRate){
	Network net;
	
	net.update(1000);
	
	//firing must be more or less equal to 40 (for state C), here we test if it's between 20 and 60
	EXPECT_LE(20, net.calculateFiringRatePerSecond(1000));
	EXPECT_GE(60, net.calculateFiringRatePerSecond(1000));
}

TEST (neuron_unittest, Neuron_type_in_Network){
	Network net;
	
	for(size_t i(0); i < nb_neurons; ++i){
		if(i < nb_excitateur){
			EXPECT_TRUE(net.getNeuron(i).isExitatory());
		}else{
			EXPECT_FALSE(net.getNeuron(i).isExitatory());
		}
	}
}

TEST (neuron_unittest, Connection_in_Network){
	Network net;
	
	net.addConnection(1, 47);
	
	EXPECT_EQ(47 , net.getConnections(1).back());
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



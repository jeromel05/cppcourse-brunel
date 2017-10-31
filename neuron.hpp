#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include "constants.hpp"
#include <cassert>
#include <random>

typedef std::array<double, D + 1> Buffer;

/**
 * This class represents a single Neuron
 */

class Neuron
{
private:
	double membrane_potential_;				///<Neuron Membrane potential
	double i_ext_;							///<external current
	std::vector<unsigned int> spike_times_;	///<number of times this neuron has spiked
	bool refractory_;						///<indicates if the neuron is in refractory state
	Time break_time_;						///<time that the neuron spends in refractory state
	Buffer buffer_;							///<buffer that stores that spike arriving to the neuron
	unsigned int index_;					///<index of the neuron
	bool exitatory_;						///<indicates the type of the neuron: excitatory or inhibitory
	bool poisson_;							///<choose wehter to include the background noise or not

	/**
	 * calculates the new membrane potential for the neuron by solving the differential equation
	 * @return membrane potential
	 */
	double solveVoltEqu() const;
	
	/**
	 * stores a spike that occured at a given time in spike_times_
	 * @param time at which the spike occured
	 */
	void addSpike(unsigned int time_step);
	
	/**
	 * shifts all the elements stored in the buffer one place to the right to simulate time passing
	 */
	void rotateBuffer();
	
	/**
	 * sets the state of the neurn: refractory or not
	 * @param refrac: true to set the neuron to refractory, false to set it to normal
	 */
	 void setRefractory(bool refrac);
	

public:

	/**
	 * @return Membrane potential
	 */
	double getMbPotential() const;
	
	/**
	 * @return number of times this neuron has spiked
	 */
	unsigned int getNbSpikes() const;

	/**
	 * @return Vector storing all the spike times
	 */
	std::vector<unsigned int> getTimeSpikes() const;
	
	/**
	 * @param i: index of the spike
	 * @return returns a single spike time
	 */
	unsigned int getSingleSpikeTime(int i) const;
	
	/**
	 * @return if the neuron is in a refractory period(true) or not(false)
	 */
	bool isRefractory() const;

	/**
	 * @return true if this neuron is an excitatory neuron, false if it is inhibitory
	 */
	bool isExitatory() const;
	
	/**
	 * returns the index of the neuron
	 * @return index of the neuron
	 */
	unsigned int getIndex() const;

	/**
	 * @param potMb: Membrane potential
	 */
	void setMbPotential(double potMb);
	
	/**
	 * sets the external current injected into the neuron
	 * @param i_ext: external current
	 */
	void set_i_ext(double i_ext);
	
	/**
	 * calculates the index for the buffer
	 * @param i: time to be converted into index
	 * @return index
	 */
	unsigned int idx(int i) const;
	
	/**
	 * prints all the elements stored in the buffer, used verify that it functions correctly
	 */
	void affiche_buffer() const;
	/**
	 * puts a new element into this neuron's buffer
	 * @param local_steps: time at which the pre-synaptic spike occured 
	 * @param psp_amplitude: post synaptic potential amplitude
	 */
	void fill_buffer(int local_steps, double psp_amplitude);
	/**
	 * updates the neuron: MbPotential, refractory state, Post Synaptic potentials, rotates buffer...
	 * @param simulation_steps: number of times that the neuron is updated
	 * @param start_step: time step at which we start
	 */	
	 
	bool update(int simulation_steps, int start_step = 0);
	/**
	 * default constructor
	 * @param index: index of the neuron
	 * @param excitatory: indicates the type of the neuron: excitatory or inhibitory
	 * @param poisson: indicates if you want to enable the background noise: true = enabled, false = disabled
	 */
	Neuron(unsigned int index = 0, bool excitatory = true, bool poisson = true);
	/**
	 * destructor
	 */
	~Neuron();
	

};

#endif

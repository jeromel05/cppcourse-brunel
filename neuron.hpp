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
	std::vector<unsigned int> spike_times_;			///<number of times this neuron has spiked
	bool refractory_;						///<indicates if the neuron is in refractory state
	Time break_time_;						///<time that the neuron spends in refractory state
	Buffer buffer_;							///<buffer that stores that spike arriving to the neuron
	double J_;								///<Amplitude of the signal that this neuron sends to the ones downstream
	unsigned int index_;
	bool exitatory_;						///<indicates the type of the neuron: excitatory or inhibitory

	
	void set_J(double j);
	/**
	 * @brief sets J, which is the strength of post synaptic potentiel sent by this neuron, depends on the type of the neuron
	 * @param j: the strength of post synaptic potentiel
	 */

public:

	double getMbPotential() const;
	/**
	 * @return Membrane potential
	 */
	unsigned int getNbSpikes() const;
	/**
	 * @return number of times this neuron has spiked
	 */
	std::vector<unsigned int> getTimeSpikes() const;
	/**
	 * @return Vector storing all the spike times
	 */
	unsigned int getSingleSpikeTime(int i) const;
	/**
	 * @param i: index of the spike
	 * @return returns a single spike time
	 */
	bool isRefractory() const;
	/**
	 * @return if the neuron is in a refractory period(true) or not(false)
	 */
	bool isExitatory() const;
	/**
	 * @return true if this neuron is an excitatory neuron, false if it is inhibitory
	 */
	unsigned int getIndex() const;
	
	void setMbPotential(double potMb);
	/**
	 * @param potMb: Membrane potential
	 */
	void setRefractory(bool refrac);
	/**
	 * sets the state of the neurn: refractory or not
	 * @param refrac: true to set the neuron to refractory, false to set it to normal
	 */
	void set_i_ext(double i_ext);
	/**
	 * sets the external current injected into the neuron
	 * @param i_ext: external current
	 */
	
	unsigned int idx(int i) const;
	/**
	 * calculates the index for the buffer
	 * @param i: time to be converted into index
	 * @return index
	 */
	double solveVoltEqu() const;
	/**
	 * calculates the new membrane potential for the neuron by solving the differential equation
	 * @return membrane potential
	 */
	void addSpike(unsigned int time_step);
	/**
	 * stores a spike that occured at a given time in spike_times_
	 * @param time at which the spike occured
	 */
	void rotateBuffer();
	/**
	 * shifts all the elements stored in the buffer one place to the right to simulate time passing
	 */
	void affiche_buffer() const;
	/**
	 * prints all the elements stored in the buffer, used verify that it functions correctly
	 */
	void fill_buffer(int local_steps, int delay = D);
	/**
	 * puts a new element into this neuron's buffer
	 * @param local_steps: time at which the pre-synaptic spike occured 
	 * @param delay: time that the spike takes to arrive to the soma
	 */
	bool update(int simulation_steps, int start_step = 0);
	/**
	 * updates the neuron: MbPotential, refractory state, Post Synaptic potentials, rotates buffer...
	 * @param simulation_steps: number of times that the neuron is updated
	 * @param start_step: time step at which we start
	 */	
	Neuron(unsigned int index = 0, bool excitatory = true);
	/**
	 * default constructor
	 * @param excitatory: indicates the type of the neuron: excitatory or inhibitory
	 */
	~Neuron();
	/**
	 * destructor
	 */

};

#endif

#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include <cassert>
#include <random>

typedef double Time;

//-------CONSTANTS----------------------------------------------------//
//smallest time unit available is 1ms
constexpr Time h(0.1);
constexpr double threshold_potential(20.0);
constexpr Time tau(20.0);
constexpr Time refractory_period(0.2);
//doit etre a 0.0 car la formule le fait revenir à cette valeur, shift tout de +0.070
constexpr double resting_potential(0.0);
//capacitance = [Farad] = [Volt/Coulomb]
constexpr double C(1.0);
//membrane_resistance
constexpr double R(tau / C);

constexpr int C_E(1000);
constexpr int C_I(250);
//g = (J_I/J_E)
constexpr int g(5);
//J_E = EPSP Amplitude [mV]
constexpr double J_E(0.1);
//J_I = IPSP Amplitude [mV]
constexpr double J_I(- g * J_E);

//D = Delay (travel time of spike in axon) [ms]
constexpr int D(15); // [steps]

//2 constantes initialisées dns le constructeur
const double c1(std::exp(-h / tau));  
const double c2(1 - std::exp(-h / tau));

constexpr double nu_thr(threshold_potential / (C_E * J_E * tau));		//J_E ou J_I ????
constexpr double nu_ext(2 * nu_thr);

typedef std::array<double, D + 1> Buffer;




class Neuron
{
private:
	double membrane_potential_;
	double i_ext_;
	std::vector<Time> spike_times_;
	bool refractory_;
	double input_current_;
	Time break_time_;
	Buffer buffer_;
	bool exitatory_;
	double J_;

public:

	double getMbPotential() const;
	double getNbSpikes() const;
	std::vector<Time> getTimeSpikes() const;
	Time getSingleSpikeTime(int i) const;
	bool isRefractory() const;
	bool isExitatory() const;
	
	void setMbPotential(double potMb);
	void setNbspikes(double nbSp);
	void setRefractory(bool refrac);
	void set_i_ext(double i_ext);
	void set_J(double j);
	
	int idx(int i) const;
	double solveVoltEqu() const;
	void addSpike(Time temps);
	void receive_excitatory(int time_step);
	
	void rotateBuffer();
	void affiche_buffer() const;
	void fill_buffer(int local_steps, int delay = D);
	
	bool update(int simulation_steps, int start_step = 0);
	
	void reset();
	
	Neuron(bool exitatory = true);
	~Neuron();

};

#endif

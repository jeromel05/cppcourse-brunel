#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <chrono>

typedef double Time;

//-------CONSTANTS----------------------------------------------------//
//smallest time unit available is 1ms
constexpr Time h(0.001);
constexpr double threshold_potential(0.020);
constexpr Time tau(0.020);
constexpr Time refractory_period(0.002);
//doit etre a 0.0 car la formule le fait revenir à cette valeur, shift tout de +0.070
constexpr double resting_potential(0.0);
//capacitance = [Farad] = [Volt/Coulomb]
constexpr double C(1.0);
//membrane_resistance
constexpr double R(tau / C);




class Neuron
{
private:
	double membrane_potential_;
	double nb_spikes_;
	std::vector<Time> spike_times_;
	bool refractory_;
	double input_current_;
	
public:

	double getMbPotential() const;
	double getNbSpikes() const;
	std::vector<Time> getTimeSpikes() const;
	bool isRefractory() const;
	
	void setMbPotential(double potMb);
	void setNbspikes(double nbSp);
	void setRefractory(bool refrac);
	
	double solveVoltEqu() const;
	void addSpike(Time temps);
	void update(Time simtime, Time runTime, double courant);
	
	Neuron();
	~Neuron();

};

#endif

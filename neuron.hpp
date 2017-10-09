#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <array>

typedef double Time;
typedef std::array<double, 10> Buffer;

//-------CONSTANTS----------------------------------------------------//
//smallest time unit available is 1ms
constexpr Time h(1.0);
constexpr double threshold_potential(20.0);
constexpr Time tau(20.0);
constexpr Time refractory_period(2);
//doit etre a 0.0 car la formule le fait revenir à cette valeur, shift tout de +0.070
constexpr double resting_potential(0.0);
//capacitance = [Farad] = [Volt/Coulomb]
constexpr double C(1.0);
//membrane_resistance
constexpr double R(tau / C);

//J = EPSP Amplitude [mV]
constexpr double J(5.0);
//D = Delay (travel time of spike in axon) [ms]
constexpr double D(3.0);




class Neuron
{
private:
	double membrane_potential_;
	std::vector<Time> spike_times_;
	bool refractory_;
	double input_current_;
	int index_;
	Time break_time_;
	Buffer buffer_;

public:

	double getMbPotential() const;
	double getNbSpikes() const;
	std::vector<Time> getTimeSpikes() const;
	bool isRefractory() const;
	int getIndex() const;
	
	void setMbPotential(double potMb);
	void setNbspikes(double nbSp);
	void setRefractory(bool refrac);
	
	double solveVoltEqu() const;
	void addSpike(Time temps);
	void receive_excitatory(Time temps, double EPSP_amp);
	
	void rotateBuffer();
	void affiche_buffer() const;
	void fill_buffer(double delay = D, double EPSP_amp = J);
	
	bool update(Time start_time, int simulation_steps, double courant);
	
	Neuron(int index);
	~Neuron();

};

#endif

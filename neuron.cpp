#include <iostream>
#include "neuron.hpp"
#include <cmath>

using namespace std;

double Neuron::getMbPotential() const
{	return membrane_potential_;	}

double Neuron::getNbSpikes() const
{	return spike_times_.size();	}

vector<Time> Neuron::getTimeSpikes() const
{	return spike_times_;	}

Time Neuron::getSingleSpikeTime(int i) const
{	
	assert(i > 0.0 and i <= getTimeSpikes().size());
	return spike_times_[i -1];	
}
		
bool Neuron::isRefractory() const
{	return refractory_;		}

bool Neuron::isExitatory() const
{	return exitatory_;	}

void Neuron::setMbPotential(double potMb)
{
	string s("Mb Potential out of bounds");
    //throw catch pour pas sortir du range
	try{
		if(potMb < 0.0 or potMb > 100){
			throw s;
		}
		membrane_potential_ = potMb;
	}
	catch(string a){
		cerr << a << ": " << potMb << endl;
		setMbPotential(resting_potential);	
	}
}

void Neuron::setRefractory(bool refrac)
{
	refractory_ = refrac;
}

void Neuron::set_i_ext(double i_ext)
{
	i_ext_ = i_ext;
}

void Neuron::set_J(double j)
{
	J_ = j;
}

int Neuron::idx(int i) const
{
	return i%(D+1);
}

double Neuron::solveVoltEqu() const
{
	std::random_device rd;
    std::mt19937 gen(rd());
	std::poisson_distribution<> d(nu_ext * C_E * h * J_E);
	return c1 * getMbPotential() + i_ext_ * R * c2; //+ d(gen);
}

void Neuron::addSpike(Time temps)
{
	spike_times_.push_back(temps);
}

void Neuron::receive_excitatory(int time_step)
{
	if(buffer_[0] < -solveVoltEqu()){
		setMbPotential(resting_potential);								//possible d'avoir une valeur négative donc on remet à 0
	}else{
		setMbPotential(solveVoltEqu() + buffer_[0]);
	}
	//on a utilisé le premier element du buffer donc on le remet à 0
	cerr << "recu a: " << time_step * h << endl;
	buffer_[0] = 0.0;
}

void Neuron::affiche_buffer() const
{
	for(auto i: buffer_){
		cout << i;
	}
	cout << endl;
}

void Neuron::fill_buffer(int local_steps, int delay)
{
	buffer_[idx(delay + local_steps)] += J_;
}
		
void Neuron::rotateBuffer()
{
	buffer_.back() = buffer_[0];										//crée effet cyclique
	for(size_t i(0); i < buffer_.size(); ++i){
		buffer_[i] = buffer_[i + 1];
	}
}

bool Neuron::update(int simulation_steps, int start_step)
{
	if(simulation_steps < 1) return false;
	int step_count(start_step);
	int nb_spikes(0);
	simulation_steps += start_step;
	
	while(step_count < simulation_steps){
			
		if(getMbPotential() >= threshold_potential){					//on test d'abord si potentiel >= threshold -> passe moins souvent dans la boucle
				addSpike(step_count * h);
				setMbPotential(resting_potential);
				setRefractory(true);
				++nb_spikes;
				cerr << "spike at:" << spike_times_[getNbSpikes() - 1] << " ms" << endl;
			
		}
		if(isRefractory()){												//pas de nouveau calcul en période réfractaire
				setMbPotential(resting_potential);
					if(break_time_ <= 0.0){
						setRefractory(false);
						break_time_ = refractory_period;				//on reset breaktime à sa valeur initiale
					}
				break_time_ -= h;										//break_time stocke le resting time et est décrementée à chaque passage dans la boucle
				
		}else if(buffer_[0] <= 0.0){
					setMbPotential(solveVoltEqu());
				}else{
					receive_excitatory(start_step);
				}	
				
	rotateBuffer();
	++step_count;
	};
	
	if(nb_spikes > 0) return true; else return false;
}

Neuron::Neuron(bool exitatory)
:membrane_potential_(resting_potential), i_ext_(0.0), refractory_(false), input_current_(0.0), break_time_(refractory_period), exitatory_(exitatory)
{
	for(auto& e: buffer_){
		e = 0.0;
	}
	if(exitatory_){
		set_J(J_E);
	}else{
		set_J(J_I);
	}	
}

Neuron::~Neuron()
{}

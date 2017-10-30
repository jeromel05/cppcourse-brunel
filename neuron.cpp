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

vector<Neuron> Neuron::get_synapses_post() const
{	return synapses_post_;	}

		
bool Neuron::isRefractory() const
{	return refractory_;		}

bool Neuron::isExitatory() const
{	return exitatory_;	}

void Neuron::setMbPotential(double potMb)
{
	if(potMb >= 0.0){		//Impossible d'avoir un MbPot negatif
		membrane_potential_ = potMb;
	}else{
		membrane_potential_ = resting_potential;	
	}
	assert(membrane_potential_ >= 0.0);
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

void Neuron::add_connection(Neuron post_neuron)
{
	synapses_post_.push_back(post_neuron);
}

/*
int Neuron::idx(int i) const
{
	return i%(D+1);
}
*/

double Neuron::solveVoltEqu() const
{
	//if(buffer_[0] > 0.0) cerr << "recu" << endl;
	std::random_device rd;
    std::mt19937 gen(rd());
	std::poisson_distribution<> d(nu_ext * C_E * h * J_E);
	
	return c1 * getMbPotential() + i_ext_ * R * c2 + buffer_[0] + d(gen);
}

void Neuron::addSpike(Time temps)
{
	spike_times_.push_back(temps);
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
	//buffer_[idx(delay + local_steps)] += J_;
	buffer_[delay - 1] += J_;
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
				//cerr << "spike at:" << spike_times_[getNbSpikes() - 1] << " ms" << endl;
		}
		if(isRefractory()){												//pas de nouveau calcul en période réfractaire
				setMbPotential(resting_potential);
					if(break_time_ <= 0.0){
						setRefractory(false);
						break_time_ = refractory_period;				//on reset breaktime à sa valeur initiale
					}
				break_time_ -= h;										//break_time stocke le resting time et est décrementée à chaque passage dans la boucle
				
		}else{
			setMbPotential(solveVoltEqu());
			buffer_[0] = 0.0;											//on a utilisé le premier element du buffer donc on le remet à 0
		}
	//cerr << "MbPotential :" << getMbPotential() << endl;		
	rotateBuffer();
	++step_count;
	};
	
	if(nb_spikes > 0) return true; else return false;
}

Neuron::Neuron(bool excitatory)
:membrane_potential_(resting_potential), i_ext_(0.0), refractory_(false), break_time_(refractory_period), exitatory_(excitatory)
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

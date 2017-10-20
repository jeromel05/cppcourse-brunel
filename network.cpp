#include "network.hpp"
#include "iostream"

using namespace std;

void Network::addNeuron(Neuron* neuron)
{
	assert(neuron != nullptr);
	neurons_.push_back(neuron);
}

Neuron Network::getNeuron(int index) const
{
	assert(index > 0);
	return *neurons_[index - 1];
}

void Network::update(int start_step, int simulation_steps, double courant_ext)
{
	assert(simulation_steps > 0 and start_step < simulation_steps);
	bool spike(false);
	int step_count(start_step);
		
	while(step_count < simulation_steps)
	{	
		assert(!neurons_.empty() and neurons_.front() != nullptr);
			for(auto& e: neurons_){
				if(e->getSynapses().empty()){
					spike = e->update(step_count, 1, 0.0);
				}else{
					spike = e->update(step_count, 1, courant_ext);
				}
			}
	++step_count;
	};		
}

void Network::reset()
{
	if(!neurons_.empty()){
		for(auto& c: neurons_){
			delete c;
			c = nullptr;
		}
		neurons_.clear();
	}
	//appel à reset() seulement necessaire si on crée des new neurones
}

Network::Network()
{		
	reset();
}

Network::~Network()
{}

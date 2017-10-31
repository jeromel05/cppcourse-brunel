#include "network.hpp"
#include "iostream"

using namespace std;


Neuron Network::getNeuron(unsigned int index) const
{
	return *neurons_[index];
}

std::deque<size_t> Network::getConnections(unsigned int indiceNeuron) const
{
	return synapses_post_[indiceNeuron];
}

void Network::net_set_i_ext(double i_ext)
{
	assert(!neurons_.empty());
	for(auto& e: neurons_){
		assert(e != nullptr);
		e->set_i_ext(i_ext);
	}	
}

double Network::calculateFiringRatePerSecond(unsigned int total_steps) const
{
	double res(0.0);
	for(auto e: neurons_){
		res += e->getNbSpikes();
	}
	return res * 10000 / (total_steps * nb_neurons);					// 1 [s] = 10000 [steps]
}

void Network::addConnection(unsigned int indiceN1, unsigned int indiceN2)
{
	synapses_post_[indiceN1].push_back(indiceN2);
}

void Network::create_connections()
{
	//ou selectionner 1000 nb random des indices des excitateurs et 250 des inhibiteurs
	//ainsi on pourra avoir 2x le meme indice
	std::random_device rd;
    std::mt19937 gen(rd());
   
    std::uniform_int_distribution<> dis1(0, nb_excitateur - 1);
    
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    
    std::uniform_int_distribution<> dis2(nb_excitateur, nb_neurons - 1);
    
    int temp(0);
    
    //on reprend un autre nb tant que on a pris le meme que l'indice i pck pas de connection d'un neurone avec lui meme
     for(size_t i(0); i < nb_neurons; ++i){
		for(size_t j(0); j < (C_E + C_I); ++j){
			do{
				if(j < C_E){
					temp = dis1(gen);
				}else{
					temp = dis2(gen2);
				}
			}while(temp == i);
				assert(neurons_[i] != nullptr);
				synapses_post_[i].push_back(neurons_[temp]->getIndex());
		}
	}
}

void Network::update(int simulation_steps)
{
	assert(simulation_steps > 0);
	bool spike(false);
	int step_count(0);
	
	cout << "Simulation started" << endl;

	string file_name = "data.txt";
	
	ofstream out(file_name);
		
	// affiche nb spike par pas de temps
	
	while(step_count < simulation_steps)
	{	
		assert(!neurons_.empty());
			for(size_t i(0); i < nb_neurons; ++i){
				assert(neurons_[i] != nullptr);
					spike = neurons_[i]->update(1, step_count);
					if(spike){
						if(i < 50){
							out << step_count * h << '\t' << i << '\n';
						}
						for(size_t y(0); y < (C_E + C_I); ++y){
							if(neurons_[i]->isExitatory()){
								neurons_[synapses_post_[i][y]]->fill_buffer(step_count, J_E);
							}else{
								neurons_[synapses_post_[i][y]]->fill_buffer(step_count, J_I);
							}
						}
					}
				}
					
	++step_count;
	};
	
	out.close();
	
	cout << "Neurons firing rate per second: " << calculateFiringRatePerSecond(simulation_steps) << endl;
	
}

void Network::reset()
{
	if(!neurons_.empty()){
		for(auto& c: neurons_){
			delete c;
			c = nullptr;
		}
	}
	//appel à reset() seulement necessaire si on crée des new neurones
}

Network::Network()
{		
	for(size_t i(0); i < nb_neurons; ++i){
	try{
		if(i < nb_excitateur){										
				neurons_[i] = new Neuron(i, true);
			}else{
				neurons_[i] = new Neuron(i, false);
		}
	}
		catch (std::bad_alloc &e)
		{
			cerr << "new Failed";
		}
	}
	
	create_connections();

	cout << "Network initialised" << endl;
}

Network::~Network()
{
	reset();
}

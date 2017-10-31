#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

typedef double Time;


//-------SINGLE NEURON--------------------------------------------------//
constexpr Time h(0.1);													///< smallest time unit available is 1ms
constexpr double threshold_potential(20.0);								///< potential above which the neuron spikes [mV]
constexpr Time tau(20.0);
constexpr Time refractory_period(0.2);
constexpr double resting_potential(0.0);								///< doit etre a 0.0 car la formule le fait revenir à cette valeur, shift tout de +0.070
constexpr double C(1.0);												///< capacitance = [picoFarad]
constexpr double R(tau / C);											///< membrane_resistance

const double c1(std::exp(-h / tau)); 									///< 2 constantes initialisées dns le constructeur
const double c2(1 - std::exp(-h / tau));


//--------------NETWORK-------------------------------------------------//
constexpr int nb_excitateur(10000);							///< number of excitatory neurons
constexpr int nb_inhibiteur(2500);							///< number of inhibitory neurons
constexpr int nb_neurons(nb_excitateur + nb_inhibiteur);	///< total number of neurons	

constexpr int g(5);														///< g = (J_I/J_E) = relative synaptic weight
constexpr int C_E(0.1 * nb_excitateur);									///< Number of excitatory connections (10% of connections)
constexpr int C_I(0.1 * nb_inhibiteur);									///< Number of inhibitory connections (10% of connections)
constexpr double J_E(0.1);												///< J_E = Excitatory Post Synaptic Potential Amplitude [mV]
constexpr double J_I(- g * J_E);										///< J_I = IPSP Amplitude [mV]

constexpr double eta(2);												///< eta = nu_ext / nu_thr;
constexpr double nu_thr(threshold_potential / (C_E * J_E * tau));		///< frequence [Hz]
constexpr double nu_ext(eta * nu_thr);									///< frequence ext [Hz]

constexpr int D(15); 													///< D = Delay (travel time of spike in axon) [steps]



#endif

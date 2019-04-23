//
// Created by mitja on 23.4.2019.
//

#ifndef VAJA_IV_2_MCQOSCILATOR_AH_H
#define VAJA_IV_2_MCQOSCILATOR_AH_H

#include <vector>
#include <random>
#include "pcg_random.hpp"

static const uint32_t baseSize = 1 << 10;
static const double stepRange = 1.0;

class MCQoscilator_ah
{
public:
    explicit MCQoscilator_ah(double beta);
    void setBeta(double newBeta);
    void step();
    inline double energy() const {return m_kinetic + m_potential;}
    inline double kinetic() const {return m_kinetic;}
    inline double potential() const {return m_potential;}
    inline void warmup(uint32_t cycles) {for (uint32_t i = 0; i < baseSize * baseSize * cycles; ++i) step();}

private:
    std::vector<double> m_slices;
    std::uniform_real_distribution<double> m_step;
    std::uniform_real_distribution<double> m_chi;
    std::uniform_int_distribution<uint32_t> m_spot;
    pcg32_fast m_twister;
    double m_beta;
    double m_factor1;
    double m_factor2;
    double m_kinetic;
    double m_potential;
};


#endif //VAJA_IV_2_MCQOSCILATOR_AH_H

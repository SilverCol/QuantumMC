//
// Created by mitja on 21.4.2019.
//

#ifndef VAJA_IV_2_MCQOSCILATOR_H
#define VAJA_IV_2_MCQOSCILATOR_H

#include <vector>
#include <random>
#include "pcg_random.hpp"

static const uint32_t baseSize = 1 << 7;
static const double stepRange = .5;

class MCQoscilator
{
public:
    explicit MCQoscilator(double beta);
    void setBeta(double newBeta);
    void step();
    inline double energy() const {return m_energy;}

private:
    std::vector<double> m_slices;
    std::uniform_real_distribution<double> m_step;
    std::uniform_real_distribution<double> m_chi;
    std::uniform_int_distribution<uint32_t> m_spot;
    pcg32_fast m_twister;
    double m_beta;
    double m_factor1;
    double m_factor2;
    double m_energy;
};


#endif //VAJA_IV_2_MCQOSCILATOR_H

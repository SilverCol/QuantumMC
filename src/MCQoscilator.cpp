//
// Created by mitja on 21.4.2019.
//

#include "MCQoscilator.h"

MCQoscilator::MCQoscilator(double beta):
m_slices(baseSize, 0),
m_step(-stepRange, stepRange),
m_twister(std::random_device{}()),
m_beta(beta),
m_factor1(baseSize/beta),
m_factor2(beta/baseSize),
m_energy(m_factor1/2)
{
    std::vector<double> differences(baseSize);
    std::adjacent_difference(m_slices.begin(), m_slices.end(), differences.begin());
    differences[0] -= m_slices.back();
    m_energy -= m_factor1
            * std::inner_product(differences.begin(), differences.end(), differences.begin(), 0.0)
            / (2*m_beta);
    m_energy += m_factor2 * std::inner_product(m_slices.begin(), m_slices.end(), m_slices.begin(), 0.0) / (2 * beta);
}

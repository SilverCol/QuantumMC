//
// Created by mitja on 21.4.2019.
//

#include "MCQoscilator.h"

MCQoscilator::MCQoscilator(double beta):
m_slices(baseSize, 0),
m_step(-stepRange, stepRange),
m_chi(0.0, 1.0),
m_spot(0, baseSize - 1),
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

void MCQoscilator::setBeta(double newBeta)
{
    m_beta = newBeta;
    m_factor1 = baseSize/newBeta;
    m_factor2 = newBeta/baseSize;

    m_energy = m_factor1/2;
    std::vector<double> differences(baseSize);
    std::adjacent_difference(m_slices.begin(), m_slices.end(), differences.begin());
    differences.front() -= m_slices.back();
    m_energy -= m_factor1
                * std::inner_product(differences.begin(), differences.end(), differences.begin(), 0.0)
                / (2*m_beta);
    m_energy += m_factor2 * std::inner_product(m_slices.begin(), m_slices.end(), m_slices.begin(), 0.0) / (2 * m_beta);
}

void MCQoscilator::step()
{
    const uint32_t j = m_spot(m_twister);
    const double newSlice = m_slices[j] + m_step(m_twister);

    double squareDiff = newSlice*newSlice - m_slices[j] * m_slices[j];

    double neighbours = 0;
    if (j == 0) neighbours += m_slices.back() + m_slices[1];
    else if (j == baseSize - 1) neighbours += m_slices[j - 1] + m_slices.front();
    else neighbours += m_slices[j - 1] + m_slices[j + 1];

    double chunk1 = m_factor1 * (squareDiff + (m_slices[j] - newSlice)*neighbours); // kinetic
    double chunk2 = m_factor2 * squareDiff / 2;                                     // potential

    double probability = std::exp(-chunk1 - chunk2);
    if (probability > 1)
    {
        m_slices[j] = newSlice;
        m_energy += (-chunk1 + chunk2)/m_beta;
    }
    else if(m_chi(m_twister) < probability)
    {
        m_slices[j] = newSlice;
        m_energy += (-chunk1 + chunk2)/m_beta;
    }
}

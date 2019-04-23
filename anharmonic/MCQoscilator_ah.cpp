//
// Created by mitja on 23.4.2019.
//

#include <algorithm>
#include "MCQoscilator_ah.h"

MCQoscilator_ah::MCQoscilator_ah(double beta):
m_slices(baseSize, 0),
m_step(-stepRange, stepRange),
m_chi(0.0, 1.0),
m_spot(0, baseSize - 1),
m_twister(std::random_device{}()),
m_beta(beta),
m_factor1(baseSize/beta),
m_factor2(beta/baseSize),
m_kinetic(m_factor1/2),
m_potential(0)
{
    // Create initial state
    std::normal_distribution<double> sliceGen;
    for (auto& slice : m_slices) slice = sliceGen(m_twister);

    // calculate initial kintic energy
    std::vector<double> differences(baseSize);
    std::adjacent_difference(m_slices.begin(), m_slices.end(), differences.begin());
    differences[0] -= m_slices.back();
    m_kinetic -= m_factor1
            * std::inner_product(differences.begin(), differences.end(), differences.begin(), 0.0)
            / (2*m_beta);

    // calculate initial potential energy
    std::vector<double> squares(baseSize);
    std::transform(m_slices.begin(), m_slices.end(), squares.begin(), [](double x){return x*x;});
    m_potential += m_factor2 * (
            std::accumulate(squares.begin(), squares.end(), 0.0) / 2 +                  //harmonic
            std::inner_product(squares.begin(), squares.end(), squares.begin(), 0.0)    //anharmonic
            )/ beta;
}

void MCQoscilator_ah::setBeta(double newBeta)
{
    m_beta = newBeta;
    m_factor1 = baseSize/newBeta;
    m_factor2 = newBeta/baseSize;

    m_kinetic = m_factor1/2;
    std::vector<double> differences(baseSize);
    std::adjacent_difference(m_slices.begin(), m_slices.end(), differences.begin());
    differences.front() -= m_slices.back();
    m_kinetic -= m_factor1
                * std::inner_product(differences.begin(), differences.end(), differences.begin(), 0.0)
                / (2*m_beta);

    std::vector<double> squares(baseSize);
    std::transform(m_slices.begin(), m_slices.end(), squares.begin(), [](double x){return x*x;});
    m_potential = m_factor2 * (
            std::accumulate(squares.begin(), squares.end(), 0.0) / 2 +                  //harmonic
            std::inner_product(squares.begin(), squares.end(), squares.begin(), 0.0)    //anharmonic
    )/ m_beta;
}

void MCQoscilator_ah::step()
{
    const uint32_t j = m_spot(m_twister);
    const double newSlice = m_slices[j] + m_step(m_twister);

    double newSquare = newSlice*newSlice;
    double oldSquare = m_slices[j] * m_slices[j];
    double squareDiff =  newSquare - oldSquare;
    double anharmonicDiff = squareDiff * (newSquare + oldSquare);

    double neighbours = 0;
    if (j == 0) neighbours += m_slices.back() + m_slices[1];
    else if (j == baseSize - 1) neighbours += m_slices[j - 1] + m_slices.front();
    else neighbours += m_slices[j - 1] + m_slices[j + 1];

    double chunk1 = m_factor1 * (squareDiff + (m_slices[j] - newSlice)*neighbours); // kinetic
    double chunk2 = m_factor2 * (squareDiff / 2 + anharmonicDiff);                  // potential

    double probability = std::exp(-chunk1 - chunk2);
    if (probability > 1)
    {
        m_slices[j] = newSlice;
        m_kinetic -= chunk1 / m_beta;
        m_potential += chunk2 / m_beta;
    }
    else if(m_chi(m_twister) < probability)
    {
        m_slices[j] = newSlice;
        m_kinetic -= chunk1 / m_beta;
        m_potential += chunk2 / m_beta;
    }
}

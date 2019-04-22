//
// Created by mitja on 21.4.2019.
//

#include <fstream>
#include "MCQoscilator.h"

static const double iBeta = .0;
static const double dBeta = .01;
static const uint32_t nBeta = 200;

static const uint32_t steps = baseSize * 10000;
static const uint32_t modulo = baseSize;

void writeBinary(std::vector<double>& data, const std::string& file)
{
    std::ofstream output(file, std::ios::binary);
    for (double& x : data)
    {
        output.write(reinterpret_cast<char*>(&x), sizeof(x));
    }
    output.close();
}

int main()
{
    MCQoscilator oscilator(iBeta);
    double beta = iBeta;
    std::vector<double> output;

    std::cout << "Iterating over betas: " << std::endl;
    for (uint32_t i = 0; i < nBeta; ++i)
    {
        std::cout << "beta " << beta << std::endl;
        std::vector<double> energies;

        for (uint32_t j = 0; j < steps; ++j)
        {
            oscilator.step();
            if (j % modulo == 0)
            {
                energies.push_back(oscilator.energy());
            }
        }

        output.push_back(beta);
        output.push_back(modulo * std::accumulate(energies.begin(), energies.end(), 0.0) / steps);

        beta += dBeta;
    }

    std::string file("../data/");
    if (dBeta > 0) file.append("cooling");
    else file.append("heating");
    file.append("_");
    file.append(std::to_string(baseSize));
    file.append("_");
    file.append(std::to_string(steps));
    file.append("_");
    file.append(std::to_string(stepRange));
    file.append(".bin");

    std::cout << "Writting to " << file << std::endl;
    writeBinary(output, file);

    return 0;
}

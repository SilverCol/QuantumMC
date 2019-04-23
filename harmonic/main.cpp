//
// Created by mitja on 21.4.2019.
//

#include <fstream>
#include <chrono>
#include "MCQoscilator.h"

static const double iBeta = 1;
static const double dBeta = 1;
static const uint32_t nBeta = 200;

static const uint32_t steps = baseSize * 10000;
static const uint32_t modulo = 128;
static const uint32_t initWarmup = 1000;

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
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Setting up the oscilator." << std::endl;
    MCQoscilator oscilator(iBeta);
    oscilator.warmup(initWarmup);

    std::vector<double> output;

    std::cout << "Iterating over betas: " << std::endl;
    double beta = iBeta;
    for (uint32_t i = 0; i < nBeta; ++i)
    {
        std::cout << "beta " << beta << std::endl;
        std::vector<double> energies;
        oscilator.warmup(1);

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
        oscilator.setBeta(beta);
    }

    std::string file("../../harmonic/data/");
    if (dBeta > 0) file.append("cooling");
    else file.append("heating");
    file.append("_");
    file.append(std::to_string(baseSize));
    file.append("_");
    file.append(std::to_string((uint32_t)(iBeta + nBeta * dBeta - dBeta)));
    file.append("_");
    file.append(std::to_string((uint32_t)(100*stepRange)));
    file.append(".bin");

    std::cout << "Writting to " << file << std::endl;
    writeBinary(output, file);

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout   << "Finished in "
                << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
                << "ms" << std::endl;

    return 0;
}

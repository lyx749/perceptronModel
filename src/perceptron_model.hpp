#ifndef PERCEPTRON_MODEL_HPP
#define PERCEPTRON_MODEL_HPP
#include "get_data_set.hpp"
#include <iostream>

getDataSet *getDataSetPtr = getDataSet::GetInterface();
const int layersNumber = 2;
const double learningRate = 0.2;
const int maxEpochs = 10;

double activationFunction(double x)
{
    return (x > 0) ? 1 : 0;
}

class perceptronModel
{
private:
    std::vector<std::pair<int, int>> input;
    std::vector<int> expectedOutput;
    std::vector<double> weights;
    double threshold;

public:
    perceptronModel()
    {
        weights.resize(layersNumber);
        for (auto &e : weights)
        {
            e = getDoubleRandom(0.0, 0.0001);
        }
        threshold = getDoubleRandom(0.0, 0.0001);
    }

    std::vector<double> feedForward(std::vector<std::pair<int, int>> input)
    {
        std::vector<double> output;
        for (auto &e : input)
        {
            double prediction = activationFunction(e.first * weights[0] + e.second * weights[1] + threshold);
            output.push_back(prediction);
        }
        return output;
    }

    bool backPropagation()
    {
        std::vector<double> actualOutput = feedForward(this->input);
        bool perfectFit = true;
        std::cout << "Trainning weights[0] = " << weights[0] << " weights[1] = " << weights[1] << " threshold = " << threshold << std::endl;
        for (int i = 0; i < actualOutput.size(); ++i)
        {
            double error = expectedOutput[i] - actualOutput[i];

            // updata weight and threshold
            if (error != 0)
            {
                std::cout << "NotMatched   " << input[i].first << " " << input[i].second << "    expected " << expectedOutput[i]
                          << "  actual " << actualOutput[i] << std::endl;
                perfectFit = false;
                weights[0] += error * learningRate * input[i].first;
                weights[1] += error * learningRate * input[i].second;
                threshold += learningRate * error;
            }
            else
            {
                std::cout << "Matched   " << input[i].first << " " << input[i].second << "    expected " << expectedOutput[i]
                          << "  actual " << actualOutput[i] << std::endl;
            }
        }
        return perfectFit;
    }

    void train()
    {
        bool perfectFit = false;
        int count = maxEpochs;
        while (count-- )
        {
            inputAndOutputDataSet IO = getDataSetPtr->getSet();
            input = std::move(IO.first);
            expectedOutput = std::move(IO.second);
            perfectFit = backPropagation();
        }
    }

    void test()
    {
        inputAndOutputDataSet IO = getDataSetPtr->getSet();
        input = std::move(IO.first);
        expectedOutput = std::move(IO.second);
        std::vector<double> output = feedForward(this->input);
        double conrrect = 0.0;
        std::cout << "Testing weights[0] = " << weights[0] << " weights[1] = " << weights[1] << " threshold = " << threshold << std::endl;
        for (int i = 0; i < output.size(); ++i)
        {
            if (expectedOutput[i] == output[i])
            {
                std::cout << "Matched   " << input[i].first << " " << input[i].second << "    expected " << expectedOutput[i]
                          << "  actual " << output[i] << std::endl;

                ++conrrect;
            }
            else
            {
                std::cout << "NotMatched   " << input[i].first << " " << input[i].second << "    expected " << expectedOutput[i]
                          << "  actual " << output[i] << std::endl;
            }
        }

        std::cout << conrrect / output.size() << std::endl;
    }
};

void run()
{
    perceptronModel p;
    p.train();
    std::cout << "\n"
              << "\n"
              << std::endl;
    p.test();
}
#endif
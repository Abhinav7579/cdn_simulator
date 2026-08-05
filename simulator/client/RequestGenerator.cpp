#include "RequestGenerator.h"

#include <random>
#include <ctime>
using namespace std;
RequestGenerator::RequestGenerator()
{
    files =
    {
        "A",
        "B",
        "C",
        "D",
        "E"
    };

    states =
    {
        "Punjab",
        "Delhi",
        "Haryana",
        "Tamil Nadu",
        "Kerala",
        "Odisha",
        "Chhattisgarh"
    };
}

Request RequestGenerator::generateRequest()
{
    static random_device rd;

    static mt19937 gen(rd());

    uniform_int_distribution<> fileDist(0, files.size() - 1);

    uniform_int_distribution<> stateDist(0, states.size() - 1);

    string file = files[fileDist(gen)];

    string state = states[stateDist(gen)];

    return Request(file, state);
}
vector<Request> RequestGenerator::generateRequests(int n)
{
    vector<Request> requests;

    for(int i = 0; i < n; i++)
    {
        requests.push_back(generateRequest());
    }

    return requests;
}
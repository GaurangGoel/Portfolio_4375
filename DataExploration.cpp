#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

void readData(string fileName, vector<float> &rm, vector<float> &medv) {
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        throw runtime_error("Can't open file");
    }

    string line;
    getline(inFile, line);

    string num1, num2;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, num1, ',');
        getline(ss, num2);

        rm.push_back(stof(num1));
        medv.push_back(stof(num2));
    }
    inFile.close();
}

float sum(vector<float> v) {
    float total = 0.0;
    for (int i = 0; i < v.size(); i++) {
        total += v[i];
    }
    return total;
}

float average(vector<float> v) {
    return sum(v) / v.size();
}

float median(vector<float> v) {
    sort(v.begin(), v.end());
    int size = v.size();
    if (size % 2 == 0) {
        return (v[size / 2 - 1] + v[size / 2]) / 2;
    }
    return v[size / 2];
}

float range(vector<float> v) {
    float max = -1e10;
    float min = 1e10;
    float rng;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > max) {
            max = v[i];
        }
        if (v[i] < min) {
            min = v[i];
        }
    }
    rng = max - min;
    return rng;
}

float covariance(vector<float> x, vector<float> y) {
    float meanX = average(x);
    float meanY = average(y);
    float num = 0.0;
    for (int i = 0; i < x.size(); i++) {
        num += (x[i] - meanX) * (y[i] - meanY);
    }
    float den = x.size() - 1;
    return num / den;
}

float correlation(vector<float> x, vector<float> y) {
    float varX = covariance(x, x);
    float sigmaX = sqrt(varX);
    float varY = covariance(y, y);
    float sigmaY = sqrt(varY);
    float covXY = covariance(x, y);
    return covXY / (sigmaX * sigmaY);
}

int main() {
    vector<float> rm;
    vector<float> medv;
    string fileName = "Boston.csv";

    readData(fileName, rm, medv);

    cout << "rm sum: " << sum(rm) << "\n";
    cout << "medv sum: " << sum(medv) << "\n";

    cout << "rm mean: " << average(rm) << "\n";
    cout << "medv mean: " << average(medv) << "\n";

    cout << "rm median: " << median(rm) << "\n";
    cout << "medv median: " << median(medv) << "\n";

    cout << "rm range: " << range(rm) << "\n";
    cout << "medv range: " << range(medv) << "\n";

    cout << "Covariance between rm and medv : " << covariance(rm, medv) << "\n";
    cout << "Correlation between rm and medv : " << correlation(rm, medv) << "\n";
}
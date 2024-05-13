#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <unordered_set>
#include <ctime>
#include <iomanip>
#include <random>


#define MEASUREMENT 100

class Experiment {
public:

    static const std::string LOG_PATH;

    static std::unordered_set<int> generateStartVertexes(int vertexes) {
        std::unordered_set<int> data;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, vertexes - 1);

        while (data.size() < 5) {
            int num = dis(gen);
            if (data.find(num) == data.end()) { // Jeśli liczba nie została jeszcze wylosowana
                data.insert(num);
            }
        }

        return data;
    }

    static std::stringstream generateGraph(int vertexes, int density = 100, bool genNegative = false) {
        int maxEdges = (vertexes * (vertexes - 1));
        double calcEdges = std::ceil(maxEdges * (density * 0.01f));
        double edgesPerRow = std::ceil(calcEdges / vertexes);
        std::stringstream ss;
        //append vertexes and edges count
        ss << vertexes << " " << calcEdges << "\n";
        int min = genNegative ? -1000 : 0;
        for (int vertex = 0; vertex < vertexes; vertex++) {
            std::unordered_set<int> edgesIndexes;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(0, vertexes - 1);

            while (edgesIndexes.size() < edgesPerRow) {
                int num = dis(gen);
                if (edgesIndexes.find(num) == edgesIndexes.end() && num != vertex) { // Jeśli liczba nie została jeszcze wylosowana
                    edgesIndexes.insert(num);
                }
            }

            for (const int& target: edgesIndexes) {

                std::random_device rd2;
                std::mt19937 gen2(rd2());
                std::uniform_int_distribution<int> dis2(min, 1000);

                ss << vertex << " " << target << " " << dis2(gen2) << "\n";
            }
        }
        return ss;
    }

    static void perform(
            const std::string& experimentName,
            const std::function<void()>& experiment,
            std::vector<long>* results = nullptr,
            bool saveInFile = false
    ) {
        auto start = std::chrono::high_resolution_clock::now();

        experiment();

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::stringstream msg;

        msg << "Pomiar: " << experimentName << " wykonywal sie przez: " << duration.count() << " ms \n";

        std::cout << msg.str() << std::endl;

        if (results != nullptr) {
            results->push_back((long) duration.count());
        }

        if (saveInFile) {

            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

            std::time_t now_c = std::chrono::system_clock::to_time_t(now);

            std::tm* now_tm = std::localtime(&now_c);

            auto date = std::put_time(now_tm, "%Y-%m-%dT%H-%M-%S");

            std::stringstream fileName;
            fileName << LOG_PATH << experimentName << " " << date << ".txt";
            auto d = fileName.str();
            std::fstream log(fileName.str(), std::ios::out);
            log << msg.str();
            log.close();
        }

    }
};
const std::string Experiment::LOG_PATH = "./logs/";
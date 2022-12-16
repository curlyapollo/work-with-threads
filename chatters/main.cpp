#include <iostream>
#include <map>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <fstream>

std::vector<std::string> callers_vec;
std::vector<std::string> receivers_vec;
std::map<std::string, bool> callers;
std::map<std::string, bool> receivers;

std::ifstream input;
std::ofstream output;

void inputOfCallers(int n) {
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cout << "Name: ";
        input >> name;
        callers[name] = false;
        callers_vec.push_back(name);
    }
}

void inputOfReceivers(int n) {
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cout << "Name: ";
        input >> name;
        receivers[name] = false;
        receivers_vec.push_back(name);
    }
}

pthread_mutex_t mutex;

void *call(void *param) {
    pthread_mutex_lock(&mutex);
    int c = rand() % callers_vec.size();
    while (callers[callers_vec[c]]) {
        c = rand() % callers_vec.size();
    }
    int r = rand() % receivers_vec.size();
    while (receivers[receivers_vec[r]]) {
        r = rand() % receivers_vec.size();
    }
    callers[callers_vec[c]] = true;
    receivers[receivers_vec[r]] = true;
    output << callers_vec[c] << " calls to " << receivers_vec[r] << '\n';
    pthread_mutex_unlock(&mutex);
    //sleep(5);
    pthread_mutex_lock(&mutex);
    callers[callers_vec[c]] = false;
    receivers[receivers_vec[r]] = false;
    output << callers_vec[c] << " ends with " << receivers_vec[r] << '\n';
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

int main(int argc, char **argv) {
    srand(std::stoi(argv[3]));
    input.open(argv[1]);
    output.open(argv[2]);
    pthread_mutex_init(&mutex, nullptr);
    int n;
    std::cin >> n;
    pthread_t threads[2 * n];
    inputOfCallers(n / 2);
    inputOfReceivers(n - n / 2);
    for (int i = 0; i < n * 2; ++i) {
        pthread_create(&threads[i], nullptr, call, nullptr);
        std::cout << i + 1 << " thread\n";
    }
    sleep(100);
    return 0;
}
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct filme {
    int h_inicio;
    int h_fim;
    int cat;
};

int checkIsValid(vector<int> &combination, vector<int> &categorias, vector<filme> &filmes) {
    int n_watched = 0;
    vector<int> categoryCount(categorias.size(), 0); // Initialize category count

    // Check if there are conflicts in start time and end time
    for (unsigned long int i = 0; i < combination.size(); i++) {
        if (combination[i] == 1) {
            for (unsigned long int j = i + 1; j < combination.size(); j++) {
                if (combination[j] == 1) {
                    if (filmes[i].h_inicio < filmes[j].h_fim && filmes[j].h_inicio < filmes[i].h_fim)
                        return 0;
                }
            }
            // Increment the category count
            int categoryIndex = filmes[i].cat - 1; // Assuming category indices start from 1
            categoryCount[categoryIndex]++;
            // Check if the category count exceeds the maximum limit
            if (categoryCount[categoryIndex] > categorias[categoryIndex])
                return 0;

            n_watched++;
        }
    }

    return n_watched;
}

int main(int argc, char **argv) {
    vector<filme> filmes;
    // vector<filme> programacao;
    vector<int> categorias;

    int n_filmes = 0;
    int n_cat = 0;
    int temp = 0;

    cin >> n_filmes >> n_cat;
    filmes.reserve(n_filmes);

    for (int i = 0; i < n_cat; i++) {
        cin >> temp;
        categorias.push_back(temp);
    }

    int h_inicio, h_fim, cat;
    for (int i = 0; i < n_filmes; i++) {
        cin >> h_inicio >> h_fim >> cat;
        filmes.push_back({h_inicio, h_fim, cat});
    }

    sort(filmes.begin(), filmes.end(), [](auto &i, auto &j) { return i.h_fim < j.h_fim; });

    long unsigned int totalCombinations = (1 << n_filmes);

    int max_watched = 0;

// Generate all combinations
#pragma omp parallel
    {
#pragma omp for
        for (long unsigned int i = 1; i < totalCombinations; ++i) {
            vector<int> combination(n_filmes);

            for (int j = 0; j < n_filmes; ++j) {
                if (i & (1 << j)) {
                    combination[j] = 1;
                }
            }
            int watched = checkIsValid(combination, categorias, filmes);
            if (watched > max_watched) {
#pragma omp critical
                {
                    if (watched > max_watched) {
                        max_watched = watched;
                    }
                }
            }
        }
    }

    cout << "Max number of watched movies is: " << max_watched << endl;

    return 0;
}

// if (argc == 1)
//     print_filmes(programacao, total_number_of_hours);
// else {
//     cout << programacao.size() << endl;    // Número de filmes
//     cout << total_number_of_hours << endl; // Número de horas
// }

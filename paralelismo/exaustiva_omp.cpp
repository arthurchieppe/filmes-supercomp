#include <algorithm>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

using namespace std;

struct filme {
    int start_time;
    int end_time;
    int category;
};

// Check if a movie is available to be scheduled given the timetable and the availability of its category
// bool is_available(filme &el, bool (&timetable)[24], vector<int> &categorias) {
//     if (el.h_inicio >= el.h_fim)
//         return false;
//     if (categorias[el.cat - 1] == 0)
//         return false;
//     for (int i = el.h_inicio; i < el.h_fim; i++) {
//         if (timetable[i] == true)
//             return false;
//     }
//     return true;
// }

// Print the list of scheduled movies along with the total number of movies and hours scheduled
// void print_filmes(vector<filme> &filmes, int &total_number_of_hours) {
//     cout << "Numero total de filmes: " << filmes.size() << "\n\n";
//     cout << "Numero total de horas: " << total_number_of_hours << "\n\n";

//     cout << left << setw(10) << "H_Inicio"
//          << left << setw(10) << "H_Fim"
//          << left << setw(10) << "Categoria" << '\n';

//     for (auto &el : filmes) {
//         cout << left << setw(10) << el.h_inicio
//              << left << setw(10) << el.h_fim
//              << left << setw(10) << el.cat << '\n';
//     }
// }

// Check if the scheduling should be terminated given the total number of hours scheduled and the number of movies allowed
// bool should_break(int &total_number_of_hours, long unsigned int &allowed_number_movies, vector<filme> &programacao) {
//     if (total_number_of_hours == 23) // 23 é o número máximo de filmes que podem ser exibidos, dado que filmes não podem começar e terminar no mesmo horário
//         return true;
//     if (allowed_number_movies == (programacao.size()))
//         return true;
//     return false;
// }

// Add a movie to the timetable, decrease the availability of its category, and add it to the list of scheduled movies
// void add_to_timetable(filme &el, bool (&timetable)[24], vector<int> &categorias, vector<filme> &programacao, int &total_number_of_hours) {
//     for (int i = el.h_inicio; i < el.h_fim; i++) {
//         timetable[i] = true;
//         total_number_of_hours++;
//     }
//     categorias[el.cat - 1]--;
//     programacao.push_back(el);
// }

void insertMovie(vector<int> &start_times, vector<int> &end_times, vector<int> &movie_categories, const filme &movie) {
    // Find the correct position to insert the new movie
    auto it = upper_bound(end_times.begin(), end_times.end(), movie.end_time);

    // Calculate the insertion index
    int index = it - end_times.begin();

    // Insert the new movie at the calculated index
    start_times.insert(start_times.begin() + index, movie.start_time);
    end_times.insert(end_times.begin() + index, movie.end_time);
    movie_categories.insert(movie_categories.begin() + index, movie.category);
}

int main(int argc, char **argv) {
    int N = 0;
    int M = 0;
    long unsigned int allowed_number_movies = 0; // Soma dos filmes permitidos por cada categoria

    cin >> N >> M;

    vector<filme> filmes;

    vector<int> allowed_categories;

    int temp = 0;
    for (int i = 0; i < M; i++) {
        cin >> temp;
        allowed_categories.push_back(temp);
        allowed_number_movies += temp;
    }

    int h_inicio, h_fim, cat;
    int to_subctract = 0;
    for (int i = 0; i < N; i++) {
        cin >> h_inicio >> h_fim >> cat;
        cout << h_inicio << " " << h_fim << " " << cat << endl;
        // Ignore movies that start and end at the same time, or movies that start before midnight
        if (h_inicio >= h_fim) {
            to_subctract++;
            continue;
        }
        filmes.push_back({h_inicio, h_fim, cat});
    }
    N -= to_subctract;
    sort(filmes.begin(), filmes.end(), [](auto &i, auto &j) { return i.end_time < j.end_time; });

    cout << "Numero total de filmes: " << N << "\n\n";
    vector<int> start_times(N);
    vector<int> end_times(N);
    vector<int> movie_categories(N);

    // Fill start times, end times and movie categories vectors
    for (int i = 0; i < N; i++) {
        start_times[i] = filmes[i].start_time;
        end_times[i] = filmes[i].end_time;
        movie_categories[i] = filmes[i].category;
    }

    // Print start times end times
    for (int i = 0; i < N; i++) {
        cout << start_times[i] << " " << end_times[i] << " " << movie_categories[i] << endl;
    }
    return 0;
}

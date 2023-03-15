import argparse
import os
import time


def main(n_movies: int, ncat: int):
    # Create directory for the inputs
    os.makedirs('input_files', exist_ok=True)
    current_path = os.getcwd()
    # Prompt user if current_path is the correct path
    print(f'Current path is {current_path + "/input_files"}\n')
    print('Is this the correct path?')
    print('If not, please change the path to the correct directory')
    print('Press any key to continue')
    input()

    # Nested for loop to generate inputs
    # Get time
    start_time = time.time()
    for i in range(1, n_movies+1, 50):
        for j in range(1, ncat+1):
            os.system(f'./gerador {i} {j} "input_files/movies{i}_cat_{j}.txt"')
    # Calculate time
    end_time = time.time()
    print(f'Elapsed time: {end_time - start_time}')


if __name__ == '__main__':
    # Get arguments from argv
    parser = argparse.ArgumentParser(
        description='Generate inputs for the model')
    parser.add_argument('--n_movies', type=str,
                        help='Number of movies to generate')
    parser.add_argument('--n_cat', type=str,
                        help='Number of categories to generate')

    main(n_movies=int(parser.parse_args().n_movies),
         ncat=int(parser.parse_args().n_cat))

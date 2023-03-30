import subprocess
import time
import argparse
import os
import pandas as pd
from pathlib import Path
from tqdm.auto import tqdm
import pickle


def main(input_folder: str, heuristica: str, early_stopping_rounds=None):
    input_folder = Path(input_folder)

    # Iterate over all files in the input folder
    df = pd.DataFrame(columns=['n_movies', 'n_cat', 'time', "n_output"])
    early_stop = 0
    for file in tqdm(os.listdir(input_folder)):

        # print(f'Running {file}...', end='\r')
        if early_stopping_rounds is not None:
            if early_stop >= int(early_stopping_rounds):
                break
        early_stop += 1

        with open(input_folder / file) as f:
            start = time.perf_counter()
            proc = subprocess.run(
                [heuristica, "no_output"], input=f.read(), text=True, capture_output=True)
            end = time.perf_counter()
            # Append results to dataframe without df.append for performance
            df.loc[len(df)] = [int(file.split('_')[1]),
                               int(file.split('_')[3].split('.')[0]),
                               end - start,
                               int(proc.stdout)]

        # print('Saída:', proc.stdout)
        # print('Stderr:', proc.stderr)
        # print('Tempo total(s):', end - start)

    df = df.sort_values(by=['n_movies', 'n_cat']).reset_index(drop=True)
    # print(df)
    # print(df.dtypes)
    df.to_pickle(f'{heuristica.split("/")[-1]}.pkl')
    df.to_csv(f'{heuristica.split("/")[-1]}.csv')


if __name__ == '__main__':
    # Get arguments from argv
    parser = argparse.ArgumentParser(
        description='Generate inputs for the model')
    parser.add_argument('-i', type=str,
                        help='Input folder relative path')
    parser.add_argument('-f', type=str,
                        help='Path da Heuristica a ser utilizada')
    parser.add_argument('-s', type=str, help="Number of early stopping rounds"
                        " (default: 10)", default=None)

    main(input_folder=parser.parse_args().i,
         heuristica=parser.parse_args().f,
         early_stopping_rounds=parser.parse_args().s)

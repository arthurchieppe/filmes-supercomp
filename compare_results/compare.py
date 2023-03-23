import subprocess
import time
import argparse
import os
import pandas as pd
from pathlib import Path
from tqdm.auto import tqdm


def main(input_folder: str, heuristica: str):
    input_folder = Path(input_folder)

    # Iterate over all files in the input folder
    df = pd.DataFrame(columns=['n_movies', 'n_cat', 'time'])

    for file in tqdm(os.listdir(input_folder)):

        # print(f'Running {file}...', end='\r')

        with open(input_folder / file) as f:
            start = time.perf_counter()
            proc = subprocess.run(
                [heuristica], input=f.read(), text=True, capture_output=True)
            end = time.perf_counter()
            # Append results to dataframe without df.append for performance
            df.loc[len(df)] = [file.split('_')[1],
                               file.split('_')[3].split('.')[0],
                               end - start]

            # print('Saída:', proc.stdout)
            # print('Stderr:', proc.stderr)
            # print('Tempo total(s):', end - start)

    df.to_csv(f'{heuristica.split("/")[-1]}.csv')


if __name__ == '__main__':
    # Get arguments from argv
    parser = argparse.ArgumentParser(
        description='Generate inputs for the model')
    parser.add_argument('-i', type=str,
                        help='Input folder relative path')
    parser.add_argument('-f', type=str,
                        help='Path da Heuristica a ser utilizada')

    main(input_folder=parser.parse_args().i,
         heuristica=parser.parse_args().f)

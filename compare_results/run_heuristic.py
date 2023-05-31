import subprocess
import time
import argparse
import os
import pandas as pd
from pathlib import Path
from tqdm.auto import tqdm
import pickle


def main(input_file: str, heuristica: str, early_stopping_rounds=None):
    input_file = Path(input_file)
    with open(input_file) as f:
        start = time.perf_counter()
        proc = subprocess.run(
            [heuristica, "no_output"], input=f.read(), text=True, capture_output=True)
        end = time.perf_counter()
        print("stdout:")
        print(proc.stdout)


if __name__ == '__main__':
    # Get arguments from argv
    parser = argparse.ArgumentParser(
        description='Generate inputs for the model')
    parser.add_argument('-i', type=str,
                        help='Input folder relative path')
    parser.add_argument('-f', type=str,
                        help='Path da Heuristica a ser utilizada')
    parser.add_argument('-s', type=str, help="Number of early stopping rounds"
                        " (default: None)", default=None)

    main(input_file=parser.parse_args().i,
         heuristica=parser.parse_args().f,
         early_stopping_rounds=parser.parse_args().s)

#! /usr/bin/env python3


import matplotlib.pyplot as plt
import sys


def parse_data(fname):
    hits = []
    misses = []
    with open(fname) as fd:
        for line in fd:
            hit_miss, timing = line.split(";")
            if hit_miss == "hit":
                if int(timing) > 1000:
                    continue
                hits.append(int(timing))
                pass
            elif hit_miss == "miss":
                if int(timing) > 1000:
                    continue
                misses.append(int(timing))
            else:
                print("Ill-formatted CSV file 'cache.log'!")
                assert False
    return hits, misses


def main():
    if len(sys.argv) != 2:
        print(f"USAGE: {sys.argv[0]} <cache.log>")
        exit(0)
    fname = sys.argv[1]

    hits, misses = parse_data(fname)

    plt.hist(misses, bins=200, color="orange")
    plt.hist(hits, bins=200, color="blue")
    plt.show()


if __name__ == "__main__":
    main()

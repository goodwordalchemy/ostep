"""explores the effects of tlb caching on paging performance"""
import subprocess

import matplotlib.pyplot as plt

NUM_TRIALS = 100000

def _run_experiment(num_trials, num_pages):
    output = subprocess.run(f'./tlb {num_trials} {num_pages}', shell=True, stdout=subprocess.PIPE)
    print(f"output: {output}")
    output = output.stdout.decode('utf-8')
    output = output.strip()
    output = round(float(output))

    return output


def _collect_results(num_pages_list, num_trials):
    results = []

    for i, n_p in enumerate(num_pages_list):
        print(f'experiment {i+1} of {len(num_pages_list)}')
        results.append(_run_experiment(num_trials, n_p))

    return results


def _plot_results(num_pages_list, paging_results):
    plt.semilogx()
    plt.scatter(num_pages_list, paging_results)
    plt.title("TLB size analysis")
    plt.xlabel("Number of pages")
    plt.ylabel("time per access (ns)")


def main():
    """collect experiment results and plot"""
    num_pages_list = [2**x for x in range(1, 11)]

    results = _collect_results(num_pages_list, NUM_TRIALS)

    _plot_results(num_pages_list, results)

    plt.show()

if __name__ == '__main__':
    main()

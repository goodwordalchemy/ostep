import subprocess

import matplotlib.pyplot as plt

COMMAND_FMT = "python2 x86.py -p {script} -M count -a bx={cycles} -c -i {interrupt} -t {num_threads}"

CYCLES = 25
MAX_INTERRUPT_FREQ = 25
SCRIPT = "test-and-test-and-set.s"
N_THREADS = 2

def run_trial(script, irpt):
    command = COMMAND_FMT.format(script=script, interrupt=irpt, cycles=CYCLES, num_threads=N_THREADS)
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE)
    result = result.stdout.decode('utf-8')
    result = result.split("\n")

    instructions_executed = len(result)

    result = result[-2].split()
    result = result[0]
    result = int(result)

    return instructions_executed, result

def run_experiment():
    results = []
    for irpt in range(1,MAX_INTERRUPT_FREQ + 1):
        print(f"running trial {irpt} of {MAX_INTERRUPT_FREQ}")
        results.append(run_trial(SCRIPT, irpt))

    instructions_executed, memory_location = zip(*results)

    return instructions_executed, memory_location

def main():
    instructions_executed, memory_location = run_experiment()
    Xs = list(range(len(instructions_executed)))

    plt.scatter(Xs, memory_location)
    plt.yscale("linear")
    plt.ylim([0, 100])
    plt.xlabel("interrupt frequency")
    plt.ylabel("value for count")
    plt.title("Results of varying interrupt frequency on memory location")

    plt.figure()

    plt.scatter(Xs, instructions_executed)
    plt.xlabel("interrupt frequency")
    plt.ylabel("number of intstructions executed")
    plt.title("Effects of interrupt frequency on running time")

    plt.show()

if __name__ == '__main__':
    main()

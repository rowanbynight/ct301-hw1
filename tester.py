import subprocess
import sys


class Report:
    output = ""
    exit_code = 0

def run(command, args, config):
    completed = None 
    if True:#config.show_exec:
        completed = subprocess.run([command] + args, capture_output = True)
    else:
        pass#completed = subprocess.run([command] + args, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
    report = Report()
    report.output = str(completed.stdout)[2:-1].strip("\\n")
    report.exit_code = completed.returncode
    return report

# returns the index of the first item at which the iterables differ, 
# or -1 if they do not
# or -2 if the number of items differs
# or -3 if the iterables are of different types
def check_iterables(iter_a, iter_b):
    if type(iter_a) != type(iter_b):
        return -3
    if len(iter_a) != len(iter_b):
        return -2
    for i in range(len(iter_a)):
        if iter_a[i] != iter_b[i]:
            return i
    return -1

def get_file_lines(filename):
    f = open(filename, "r")
    lines = f.read().split("\n")
    f.close()
    return lines

# test format:
# arg_1 ... arg_n -exp <expected as string>
# OR
# arg_1 ... arg_n -exp-file <filename>

class Test:
    id = 0
    command = ""
    args = []
    # Can be string or list of strings
    expected = None
    expected_exit_code = 0


def parse_test(raw_test, test_i):
    tokens = raw_test.split(" ")
    new_test = Test()
    i = 0
    mode = 0
    expected_tokens = []
    while i < len(tokens):
        if tokens[i][0] == "!":
            if tokens[i] == "!exp" or tokens[i] == "!exp-file":
                mode = 1
            if tokens[i] == "!exit":
                mode = 2
        elif mode == 0:
            new_test.args.append(tokens[i])
        elif mode == 1:
            expected_tokens.append(tokens[i])
        elif mode == 2:
            new_test.expected_exit_code = int(tokens[i])
        i += 1
    new_test.id = test_i
    return new_test
    print(f"Error occured while parsing test {test_i}")

def execute(test, config):
    report = run(test.command, test.args, config)
    if (config.show_exec):
        return "Execution finished"
    if config.show_output:
        print(f"Output: {report.output}")
    if config.show_exit_code:
        print(f"Exit code: {report.exit_code}")
    if config.show_expected:
        print(f"Output: {test.expected}")
    if report.exit_code != test.expected_exit_code:
        return f"Test {test.id} failed. Expected exit code {test.expected_exit_code}, but received {report.exit_code}"
    if type(test.expected) == list:
        result = check_iterables(report.output.split("\n"), test.expected)
        if result == -2:
            return f"Test {test.id} failed. The number of lines in the output differs from expected"
        if result > -1:
            return f"Test {test.id} failed. Output first differs at line {result}"
    else:
        result = check_iterables(report.output, test.expected)
        if result == -2:
            return f"Test {test.id} failed. The number of characters in the output differs from expected"
        if result > -1:
            return f"Test {test.id} failed. Output first differs at character {result}"
    if report.exit_code != test.expected_exit_code:
        return f"Test {test.id} failed. Expected exit code {test.expected_exit_code}, but received {report.exit_code}"
    return f"Test {test.id} successful."

def execute_from_file(filename, config):
    print(f"Executing tests from file {filename}")
    f = open(filename, "r")
    lines = f.read().split("\n")
    command = lines[0]
    i = 1
    for raw_test in lines[1:]:
        parsed = parse_test(raw_test, i)
        result = execute(parsed, config)
        print(result)
        i += 1


class Config:
    FLAG_SHOW_OUTPUT = "-output"
    FLAG_SHOW_EXPECTED = "-expected"
    FLAG_SHOW_EXEC = "-show_exec"
    FLAG_SHOW_EXIT_CODE = "-exit_code"
    show_exec = False
    show_output = False
    show_expected = False
    show_exit_code = False


def main(argv):
    filenames = []
    flags = []
    for token in argv[1:]:
        if token[0] == "-":
            flags.append(token)
        else:
            filenames.append(token)
    if len(filenames) == 0:
        print("Pass at least one filename to perform tests")
        return
    config = Config()
    for flag in flags:
        if flag == config.FLAG_SHOW_EXEC:
            config.show_exec = True
        if flag == config.FLAG_SHOW_OUTPUT:
            config.show_output = True
        if flag == config.FLAG_SHOW_EXPECTED:
            config.show_expected = True
        if flag == config.FLAG_SHOW_EXIT_CODE:
            config.show_exit_code = True
    for filename in filenames:
        execute_from_file(filename, config)


main(sys.argv)
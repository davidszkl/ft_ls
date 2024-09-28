import datetime
from pathlib import Path
import subprocess
import re
from typing import List, Tuple

OK = "\033[1;32mok\033[0m"
KO = "\033[1;31mko\033[0m"

tests: List[Tuple[bool, bool, List[str]]] = [
    # long | recursive | args
    (False, False, []),
    (False, False, ["-a"]),
    (False, False, ["--all"]),
    (True, False, ["-l"]),
    (True, False, ["--long"]),
    (False, False, ["-r"]),
    (False, False, ["--reverse"]),
    (False, False, ["-t"]),
    (True, False, ["--time"]),
    (False, True, ["-R"]),
    (False, False, ["-recursive"]),
    (False, True, ["--recursive"]),
]

def normalize_expected(expected: str, long: bool, recursive: bool):
    if not expected:
        return ""
    vals = expected.split('\n')
    rval = ""
    is_title = True
    for idx, val in enumerate(vals):
        rval += val
        if long or (recursive and is_title):
            rval += "\n"
            is_title = False
        elif val and idx < len(vals) - 1 and vals[idx + 1]:
            rval += "  "
        if not val:
            is_title = True
            if recursive:
                rval += '\n'
                if idx == len(vals) - 1:
                    is_title = False
                if idx < len(vals) - 1:
                    rval += "\n"
            else:
                rval += '\n'
        
    rval = rval.replace("\n\n\n", "\n\n")
    if recursive and rval[-2: len(rval)] == "\n\n":
        rval = rval[:-1]
    return rval

def normalize_expected_error(expected: str, long: bool, recursive: bool):
    return expected
    
def normalize_actual(actual: str):
    rval = actual.replace('\0', '')
    return rval

def find_first_difference(str1, str2):
    min_length = min(len(str1), len(str2))

    for i in range(min_length):
        if str1[i] != str2[i]:
            return i

    if len(str1) != len(str2):
        return min_length

    return None

def make_diff(expected: str, actual: str):
    diff = []
    lines_expected = expected.split('\n')
    lines_actual = actual.split('\n')

    idx = 0
    len_expected, len_actual = len(lines_expected), len(lines_actual)
    while (idx < len_expected and idx < len_actual):
        line_expected = lines_expected[idx]
        line_actual = lines_actual[idx]
        if line_expected == line_actual:
            idx += 1
            continue
        diff_idx = find_first_difference(line_expected, line_actual)
        diff_line = line_actual[:diff_idx] + f"\033[1;31m{line_actual[diff_idx:]}\033[0m"
        diff.append((line_actual, f"line {idx}:\n\
expected: {line_expected}\n\
actual:   {diff_line}\n"))
        idx += 1
        return diff

def run_test(long: bool, recursive: bool, args: List[str]) -> None:
    command = ' '.join(t for t in args)

    expected_rval = subprocess.run(["ls", "-1", *args], cwd="/home/dszklarz/ft_ls/test", text=True, capture_output=True)
    expected = normalize_expected(expected_rval.stdout, long, recursive)
    expected_err = normalize_expected_error(expected_rval.stderr, long, recursive)
    
    actual_rval = subprocess.run(["/home/dszklarz/ft_ls/ft_ls", *args], cwd="/home/dszklarz/ft_ls/test", text=True, capture_output=True)
    actual = normalize_actual(actual_rval.stdout)
    actual_err = normalize_actual(actual_rval.stderr)

    leak_found = check_memory_leaks(args)
    if actual == expected and actual_err == expected_err:
        print(f"{command:{max_size}}:   {OK}      {KO if leak_found else OK}")
    else:
        print(f"{command:{max_size}}:   {KO}      {KO if leak_found else OK}")
        diff = make_diff(expected, actual)
        for line, diff_line in diff:
            print(diff_line)

def check_memory_leaks(args):
    actual_rval = subprocess.run(["/usr/bin/valgrind", "/home/dszklarz/ft_ls/ft_ls", *args], cwd="/home/dszklarz/ft_ls/test", text=True, capture_output=True)
    pattern = r"(definitely lost|indirectly lost|possibly lost|still reachable): (\d+) bytes in (\d+) blocks"
    matches = re.findall(pattern, actual_rval.stderr)
    return any(int(bytes_lost) > 0 or int(blocks_lost) > 0 for _, bytes_lost, blocks_lost in matches) 

if __name__ == "__main__":
    max_size = max(sum(len(arg) for arg in arglist) for _, _, arglist in tests)
    print(f"test         output  memory")
    print("============================")
    errors = []
    for long, recursive, args in tests:
        run_test(long, recursive, args)


#!/usr/bin/python3
import subprocess
import os
import sys

def run_test(path):
    print("running", path)
    res = subprocess.run(["./a.out", path + "/input.txt"], stdout=subprocess.PIPE)
    if res.returncode != 0:
        print("crashed")
        return
    output = res.stdout.decode("utf8").split("\n")
    expected_output = open(path + "/output.txt", "r").read().split("\n")
    inputs = open(path + "/input.txt", "r").read().split("\n")
    for i in range(len(inputs)):
        if output[i] != expected_output[i]:
            print(inputs[i])
            print("output  :", output[i])
            print("expected:", expected_output[i])

os.system("make")

if len(sys.argv) > 1:
    for dir in sys.argv[1:]:
        run_test(dir)
else:
    tests = os.listdir("tests");
    tests.sort()
    for dir in tests:
        run_test("tests/" + dir)

os.remove("a.out")

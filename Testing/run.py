from pwn import *

from os import listdir
from os.path import isfile, join
test_files = [f for f in listdir(".") if isfile(join(".", f))]

for test_file in test_files:
    if "test" in test_file:
        test_result = process(["python3", test_file]).recvall().decode("utf-8")
        log.warn("#"*50)
        log.warn(f"test_result: {test_result}")
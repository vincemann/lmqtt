from pwn import *

from os import listdir
from os.path import isfile, join
test_files = [f for f in listdir(".") if isfile(join(".", f))]

# if it hangs on recving, a test is failing
for test_file in test_files:
    if "test.py" in test_file:
        io = process(["python3", test_file])
        test_result = io.recvall().decode("utf-8")
        # ret_code = io.poll()
        # assert ret_code == 0
        log.warn("#"*50)
        log.warn(f"test_result: {test_result}")
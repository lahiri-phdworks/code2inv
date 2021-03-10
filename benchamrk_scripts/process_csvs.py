import os

pwd = os.path.dirname(__file__)
prog_generator = os.path.join(pwd, os.pardir, "code2inv",
                              "prog_generator")
results = os.path.join(prog_generator,  "results")


fileMap = dict()

for files in os.listdir(results):
    if "log_inv_" in files:
        # These are "best_root" log files.
        if fileMap.get(files.strip().split('_')[2], None) is None:
            fileMap[files.strip().split('_')[2]] = 0
        else:
            fileMap[files.strip().split(
                '_')[2]] = fileMap[files.strip().split('_')[2]] + 1

print(fileMap)

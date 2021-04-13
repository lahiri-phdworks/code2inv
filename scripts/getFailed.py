import os
import sys
import json

failedMap = {}
failure = {}
with open("failed.log", mode="r") as f:
    lines = f.readlines()

for line in lines:
    caseInstance = line.strip().split(",")[0].strip()
    if failedMap.get(caseInstance, None) is not None:
        failedMap[caseInstance] += 1
    else:
        failedMap[caseInstance] = 0

for k, v in failedMap.items():
    if v > 1 and v < 16:
        failure[k] = v

with open("failed.json", mode="w") as f:
    json.dump(failure, f, indent=4)

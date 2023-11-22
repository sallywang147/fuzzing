import json

with open('summary.json') as json_file:
  data = open("summary.json", "r")

for item in data.split("{"):
    print("=======================")
    print(item)
    print("=======================")
    #if item["Func lines hit %"] == "0.0%":
    #    print(item["Func name"], item["source_file"])
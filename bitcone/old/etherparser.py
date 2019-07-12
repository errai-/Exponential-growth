
vals = []
count = -1
with open('export-EtherPrice.csv') as f:
    for line in f.readlines():
        try:
            info = map(lambda s : s.strip('"'),line.strip('\n').strip('\r').split(','))[2]
            print(info)
        except:
            continue

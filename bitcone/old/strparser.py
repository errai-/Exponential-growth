
vals = []
count = -1
with open('coindesk-bpi-USD-close_data-2010-07-18_2017-12-10.csv') as f:
    for line in f.readlines():
        try:
            info = float(line.strip('\n').split(',')[1])
            print(info)
        except:
            continue

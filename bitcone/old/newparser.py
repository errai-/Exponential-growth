
vals = []
count = -1
with open('BTC_USD_2013-10-01_2019-07-11-CoinDesk.csv') as f:
    for line in f.readlines():
        try:
            info = float(line.strip('\n').split(',')[2])
            print(info)
        except:
            continue

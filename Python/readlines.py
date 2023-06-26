fd = open(r'C:\Users\sbc\Desktop\test.txt',"r",encoding='utf-8')
lines = fd.readlines()
for s in lines:
    if('call' in s):
        print(s,end='')

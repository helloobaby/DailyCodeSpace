# struct Iris* data = mem_malloc(data_size * sizeof(struct Iris));
# data[0].feature[0] = 5.1;
# data[0].feature[1] = 3.5;
# data[0].feature[2] = 1.4;
# data[0].feature[3] = 0.2;
# data[0].label = "Iris-setosa";

import os

f = open('D:\Download\iris.data','r')
count = 0
for line in f:
    parts = line.strip().split(',')
    if parts == ['']:
        break
    print('data[' + str(count) + '].feature[0] = ' + parts[0]+';')
    print('data[' + str(count) + '].feature[1] = ' + parts[1]+';')
    print('data[' + str(count) + '].feature[2] = ' + parts[2]+';')
    print('data[' + str(count) + '].feature[3] = ' + parts[3]+';')
    print('data[' + str(count) + '].label = \"' + parts[4]+'\";')
    count = count + 1



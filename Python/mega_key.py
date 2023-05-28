# https://pypi.org/project/mega.py/
# 每次post返回都要一秒,没法这样爆破,算了一下，大概要62年能爆破出来
from mega import Mega

all_key_str = '.0123456789/*-+/.,mnbvcxz;lkjhgfdsa][poiuytrewq]`~-=!@#$%^&*()_'
index0 = ''
index1 = ''
index2=''
index3=''
index4=''

def replace(b:str,i:int,s):
    global index0
    global index1
    global index2
    global index3
    global index4
    assert(len(b) == 5)
    t = list(b)
    t[i]=s
    return ''.join(t)

key1= 'https://mega.nz/file/yUIlFaJY#eWhpXnJOmswYAY_Vx93VF2moxjM4uQuhv_7hII'
key2 = 'xxxxx'

mega = Mega()

def download_file(url):
    try:
        print('try -> ' + key1 + key2)
        mega.download_url(key1 + key2)
        print('find key ' + key1 + key2)
    except Exception as err:
        print('exception -> ' + str(err))


for index0 in all_key_str:
    key2 = replace(key2,0,index0)
    for index1 in all_key_str:
        key2 = replace(key2, 1, index1)
        for index2 in all_key_str:
            key2 = replace(key2, 2, index2)
            for index3 in all_key_str:
                key2 = replace(key2, 3, index3)
                for index4 in all_key_str:
                    key2 = replace(key2, 4, index4)
                    #print(key2)
                    download_file(key1+key2)


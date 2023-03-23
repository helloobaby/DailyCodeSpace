# -*- coding: UTF-8 -*-
# export http_proxy="http://127.0.0.1:7890"
# export https_proxy="http://127.0.0.1:7890"
# unset http_proxy
# unset https_proxy

import os
import gzip

url = 'https://suo.yt/xxxxxxx'

def un_gz(file_name):
    """ungz zip file"""
    f_name = file_name.replace(".gz", "")
    g_file = gzip.GzipFile(file_name)
    open(f_name, "wb+").write(g_file.read())
    g_file.close()

def exist():
    if os.path.exists('Country.mmdb') and os.path.exists('clash-linux-amd64-v1.12.0'):
        return True
    else:
        return False

def downloadfile():
    os.system('curl -O http://wudiaoteman.cn/%E5%B7%A5%E5%85%B7/linux-amd64-clash/clash-linux-amd64-v1.12.0.gz')
    os.system('curl -O http://wudiaoteman.cn/%E5%B7%A5%E5%85%B7/linux-amd64-clash/Country.mmdb')

def downloadconfig():
    os.system('curl -L -o config.yaml https://suo.yt/xxxxx')

print('-- current path : '+os.getcwd())
if exist():
    print('-- 文件已存在,不执行下载人任务')
else:
    downloadfile()
print('-- 下载订阅文件')
downloadconfig()

un_gz('clash-linux-amd64-v1.12.0.gz')
os.system('rm clash-linux-amd64-v1.12.0.gz')

os.system('clash-linux-amd64-v1.12.0 -d .')








import os
import sys
import time
import re
import logging
import urllib.request
from watchdog.observers import Observer
from watchdog.events import *


def send_to_iphone(info):
    # 字符串中可能有空格,换成+号
    info = info.replace(' ', '+')
    info = info.replace('/', '%2f')
    print(info)
    try:
        ua_headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36"}
        # 稍微修改一下agent
        request = urllib.request.Request(r'https://api.day.app/QmtTLu65RbES55bnvShE5J/'+info[0:20], headers = ua_headers)
        # 发送请求
        urllib.request.urlopen(request)
    except Exception as ex: 
        print('-- urlopen failed ')
        print(ex)
        print('-- 实际url')
        print('https://api.day.app/QmtTLu65RbES55bnvShE5J/'+info[0:20])
        

def get_access_info(filename):
    # 读取nginx日志文件
    fd=open(filename,'r')
    lines = fd.readlines()
    # 取最后一行
    data = lines[-1]
    fd.close()
    #print(data)

    send_to_iphone(data)
    pass


class NewLoggingEventHandler(FileSystemEventHandler):
    def on_modified(self,event):
        #print(event.src_path)
        [path,filename] = os.path.split(event.src_path)
        #print(filename)
        if('private_access' in filename):
            print('-- 监视的文件路径'+event.src_path)
            get_access_info(event.src_path)


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO,
                        format='%(asctime)s - %(message)s',
                        datefmt='%Y-%m-%d %H:%M:%S')
    path = sys.argv[1] if len(sys.argv) > 1 else '.'

    # 生成事件处理器对象
    event_handler = NewLoggingEventHandler()

    # 生成监控器对象
    observer = Observer()
    # 注册事件处理器，配置监控目录
    observer.schedule(event_handler, path, recursive=True)
    # 监控器启动——创建线程
    observer.start()
    try:
        while True:
            time.sleep(5)
    except:
        self.observer.stop()
        print('Error')
    # 主线程任务结束之后，进入阻塞状态，一直等待其他的子线程执行结束之后，主线程再终止
    observer.join()

import os
import sys
import time
import logging
from watchdog.observers import Observer
from watchdog.events import *

def get_access_ip(filename):
    # 读取nginx日志文件
    fd = os.open(filename,os.O_RDWR)
    data = os.read(fd, 40000000).decode()
    print(data)

    data = data[0,data.find('\"GET')]
    print(data)
    
    os.close(fd)
    pass

def send_to_iphone(info):
    pass

class NewLoggingEventHandler(FileSystemEventHandler):
    def on_modified(self,event):
        #print(event.src_path)
        [path,filename] = os.path.split(event.src_path)
        #print(filename)
        if('private_access' in filename):
            get_access_ip(event.src_path)


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

    # 以下代码是为了保持主线程运行
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()

    # 主线程任务结束之后，进入阻塞状态，一直等待其他的子线程执行结束之后，主线程再终止
    observer.join()

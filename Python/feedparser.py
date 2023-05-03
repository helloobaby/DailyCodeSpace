# encoding:utf-8
import os
import feedparser

# 得开代理
d = feedparser.parse('https://v2ex.com/index.xml')
#print(d)

for entry in d.entries:
    print(entry.title)
    print(entry.link)

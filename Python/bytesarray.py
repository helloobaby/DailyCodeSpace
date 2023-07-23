ba = bytearray()
ba = '123'
print(ba)
print(ba[0])

# 这种是str类型
ba = '\xE4\xBD\xA0\xE5\xA5\xBD'
# 注意要加b'表明bytes类型
ba = bytearray(b'\xE4\xBD\xA0\xE5\xA5\xBD')
ba = bytearray.fromhex('E4BDA0E5A5BD')
# 先转化为bytes然后转码为utf-8
ba = bytes(ba).decode('utf-8')
print(ba)

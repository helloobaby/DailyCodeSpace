import os
import sys
import hashlib


file = sys.argv[1]
# print(file)
with open(file,"rb") as f:
    bytes = f.read() # read entire file as bytes
    readable_hash = hashlib.sha256(bytes).hexdigest()
    print(readable_hash)
    root,name = os.path.split(file)
    #print(root)
    #print(name)
    f.close()
    os.rename(file,root+'\\'+readable_hash)    



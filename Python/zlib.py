import zlib

def compress_text(text:str):
    data = text.encode('utf-8')
    
    compressed_data = zlib.compress(data, level=zlib.Z_BEST_COMPRESSION)
    
    return compressed_data

def decompress_text(compressed_data:bytes):
    decompressed_data = zlib.decompress(compressed_data)

    text = decompressed_data.decode('utf-8')
    
    return text


result = compress_text('helloooooo')
#print(result)
print(result.decode('utf-8',errors='ignore'))

result = decompress_text(result)
print(result)

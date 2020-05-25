import sys
import hashlib

filename = sys.argv[1]
file_hash = hashlib.new("SHA1")
with open(filename, 'rb') as in_file:
    while True:
        data = in_file.read(4096)
        if not data:
            break
        file_hash.update(data)

print(file_hash.hexdigest())

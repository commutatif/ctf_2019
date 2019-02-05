import sys, os

"""
get the content of all the files in the directory given as argument
use: f = get_files()
"""

def get_files():
    files = []
    dir = sys.argv[1]
    if not(dir[-1] == "/"):
        dir+='/'
    for filename in os.listdir(dir):
        files.append(open(dir + filename, 'rb').read())
    return files

"""
Transform the content of the files in bytearrays
use: cipher = get_bytearray(files)
"""

def get_bytearray(files):
    c = []
    for file in files:
        c.append(bytearray(file))
    return c

"""
get all the xors of the files from a bytearray of the cipher texts
use: xors = get_xors(ciphers)
xors[0][1] contains the xor of the cipher 0 with the 1
"""

def get_xors(ciphers):
    x = []
    for i in range(len(ciphers)):
        x0 = []
        for j in range(len(ciphers)):
            x0.append([a^b for a,b in zip(ciphers[i], ciphers[j])])
        x.append(x0)
    return x

"""
initialize clear texts array
use: m = init_clears(ciphers)
"""

def init_clears(ciphers):
    m = []
    for i in range(len(ciphers)):
        m.append(['°' for i in range(len(ciphers[0]))])
    return m

"""
initialize the key
"""
def init_key(ciphers):
    l = max([len(i) for i in ciphers])
    return [-1 for i in range(l)]

"""
Returns True if all the numbers in ordarr are in possibilities
"""

def is_readable(ordarr, possibilities):
    for i in ordarr:
        if not(i in possibilities):
            return False
    return True


"""
verifies if the xor^cribord is readable for all xors with n
"""
def verify_xor(i, xors, n, cribord, possibilities):
    for j in range(len(xors)):
        a = [x^y for x, y in zip(cribord, xors[n][j][i:(i+len(cribord))])]
        if not(n == i) and not(is_readable(a, possibilities)):
            return False
    return True


"""
returns the xor of a number list and a char key. (if the key is '°', there will be a '°' in the result message)
"""
def custom_xor(mess, key):
    return ['°' if k == -1 else (chr(m^k)) for m,k in zip(mess, key)]
#'°' if k == -1 else

"""
updates key if all xors are readable for the xor of 2 ciphers
"""
def get_part(xors, n1, n2, cribord, key, possibilities, ciphers):
    i=0
    while len(xors[n1][n2][i:]) >= len(cribord) :
        xorxorcrib = [a^b for a,b in zip(cribord, xors[n1][n2][i:]) if a^b in possibilities]
        if len(xorxorcrib) == len(cribord):
            #print(i)
            #print(''.join([chr(i) for i in xorxorcrib]))
            if verify_xor(i, xors, n1, cribord, possibilities):
                key[i:(i+len(cribord))] = [x^y for x, y in zip(cribord, ciphers[n1][i:(i+len(cribord))])]
            elif verify_xor(i, xors, n2, cribord, possibilities):
                key[i:(i+len(cribord))] = [x^y for x, y in zip(cribord, ciphers[n2][i:(i+len(cribord))])]
            #print("\n")
        i+=1
    return key



































"""
definition of the main operations that are done
"""

def main():
    f = get_files()
    c = get_bytearray(f)
    xors = get_xors(c)
    m = init_clears(c)
    key = init_key(c)

    possibilities = [10, 32, 34, 39, 40, 41, 43, 44, 45, 46, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 82, 83, 84, 85, 86, 87, 89, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122]


    while(1):
        os.system('clear')
        crib = input('Enter the crib you want to use:\n')
        criblist = list(crib)
        cribord = [ord(i) for i in criblist]

        for i in range(len(c)):
            for j in range(len(c)):
                if not(i==j):
                    key = get_part(xors, i, j, cribord, key, possibilities, c)

        print("key: ", key)
        for i in range(len(c)):
            print('\n\nclear' + str(i) + ':\n'+ ''.join(custom_xor(c[i], key)))
        os.system('read -p "Press Enter to continue"')
        res = open("res.txt", 'w')
        res.write("key: ")
        res.write('; '.join([str(x) if not(x == -1) else '°' for x in key]))
        for i in range(len(c)):
            res.write('\n\nclear' + str(i) + ':\n'+ ''.join(custom_xor(c[i], key)))





main()

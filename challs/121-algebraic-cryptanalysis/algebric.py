#!/usr/bin/env python

import sys
                   
ciphertext='0fd9e67a8538d200a9dab76fa3abf00a'
c = ['68636d62627672786f626e656e616771',
     '6870666a7a796f6c67737477696c6772',
     '63796a7476616a72676a7373796f6969',
     '786d696578756963796971616e6d787a',
     '6777766d6e747571656a656b667a6c75',
     '7a6b6c6a636c6f6972747a7371636d65',
     '6f6c7376747a737471637a636e61796d',
     '686e6c746266686b7a6b796c707a6c66',
     '7476646b646a78677571656561726c79',
     '757974736a756165706f747472627479',
     '6c6e6c696d6e70767a72737565766973',
     '6a787a727465756e7362637374747368']
r =  [97, 115, 27, 44, 92, 55, 27, 73, 120, 13, 112, 1]

def ROTL(s, n):
    return s[n:] + s[:n]
 
def ROTR(s, n):
    return ROTL(s,-n)
 

def dechiffre(e,c,r):
    somme=int('00000000000000000000000000000000', 16)
    for i in range(10):
       n=0
       for l in range (i+1,11):
          n+=r[l]
       n=n%128
       ci=format(int(c[i], 16),'0128b')
       rot=int(ROTR(ci,n),2)
       somme=somme^rot
  
    somme=somme^int(e, 16)^int(c[10], 16)
    
    somme=format(somme,'0128b')
    m=0
    for l in range(11):
       m=m+r[l]
    m=m%128
    s=ROTL(somme,m)
    s1=hex(int(s,2))[2:-1].decode("hex")
    print(s1)

dechiffre(ciphertext,c,r)
#le flag=interministerium
    
"""      
def key(k,r):
   lk=[k]
   for i in range(1,12):
      if i%2==1:
         lk+=[ROTR(lk[i-1],r[i-1])]
      else:
         lk+=[ROTL(lk[i-1],r[i-1])]
   return lk

def chiffre(s,c,r,k):
    lk=key(k,r)
    s=int(s,16)
    for i in range(11):
        s=s^int(lk[i],2)
        s=ROTR(format(s,'0128b'),r[i])
        s=int(s,2)^int(c[i],16)
    s=s^int(lk[11],2)
    s=hex(s)
    return s

#print(chiffre('696e7465726d696e697374657269756d',c,r,'001111000001010111010111110000011100001111101001001001110000001110111010001100101111110011101101110100010110010010100011000110'))
"""

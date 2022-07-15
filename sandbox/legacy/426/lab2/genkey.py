import time
from Crypto.Cipher import DES
from Crypto.Cipher import AES
from Crypto.Cipher import DES3
import datetime
def genkey(keylen, timeseed):
        seed = int(timeseed) & 0xffffff
        key = bytearray(8)
        modulus = pow(2,24)
        a = 1140671485 
        b = 12820163
        for i in range(keylen):
                seed = (a*seed + b) % modulus
                key[i] = (seed >> 16)
        return(bytes(key))

def main():
    keylen = 8
    message1 = 1603723200
    message2 = 1603723560
    message3 = 1603723680
    messageRange =  (datetime.datetime(2020,10,25,14,40)-datetime.datetime(1970,1,1)).total_seconds()
    docList=[]
    docxList=[]
    pngList=[]
    bitmList = []
    pdfList = []
    targetFile = "msg3.enc"
    for i in range(int((datetime.datetime(2020,10,27,14,40) - datetime.datetime(2020,10,25,14,40)).total_seconds())):
            key = genkey(keylen, int(messageRange) + i)
            with open(targetFile, "rb") as f:
                    iv = f.read(16)
            des = DES.new(key, DES.MODE_ECB)
            plaintext = des.decrypt(iv)
            print("decrypted - ",plaintext.hex(), " key = ".rjust(10), messageRange + i)
            if plaintext[0] == 208:
                    if plaintext[1] == 207:
                            if plaintext[2] == 17:
                                print("***********hit found for .doc == ", messageRange + i)
                                docList.append(messageRange + i)
                                
            elif plaintext[0] == 80:
                    if plaintext[1] == 75:
                            if plaintext[2] == 3 or plaintext[2] == 5 or plaintext[2] == 7:
                                    if plaintext[3] == 4 or plaintext[3] == 6 or plaintext[3] == 8:
                                            print("**********possible hit for .docx == ", messageRange + i)
                                            docxlist.append(messageRange + i)
                                            
            elif plaintext[0] == 137:
                   if plaintext[1] == 80:
                           if plaintext[2] == 78:
                                   pngList.append(messageRange + i)
            elif plaintext[0] == 66:
                    if plaintext[1] == 77:
                            bitmList.append(messageRange + i)
            elif plaintext[0] == 37:
                    if plaintext[1] == 80:
                            if plaintext[2] == 68:
                                    if plaintext[3] == 70:
                                        pdfList.append(messageRange + i)
    print(docList)
    for i in range(len(docList)):
            key = genkey(keylen, docList[i])
            des = DES.new(key, DES.MODE_ECB)
            with open(targetFile, "rb") as f:
                    iv = f.read()
                    
            plaintext = des.decrypt(iv)
            print("decrypted hit - ",plaintext.hex())
            with open("output2.doc", "wb") as f:
                    f.write(plaintext)
    print(docxList)
    print(pngList)
    print(bitmList)
    print(pdfList)
if __name__ == "__main__":
    main()

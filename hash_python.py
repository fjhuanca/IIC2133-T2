# -*- coding: utf-8 -*-
"""
Created on Sat Jun 12 12:35:23 2021

@author: Fernando J. Huanca
@mail: fjhuanca@uc.cl
"""

# Python implementation for the
# pattern matching in 2-D matrix
 
# Function to find the hash-value
# of the given columns of text
def findHash(arr, col, row):
    hashCol = []
    add = 0
    radix = 256
 
    # For each column
    for i in range(0, col):
 
        for j in reversed(range(0, row)):
            add = add + (radix**(row-j-1) * arr[j][i]) % prime
        hashCol.append(add % prime);
        add = 0
    return hashCol
 
# Function to check equality of the
# two strings
def checkEquality(txt, row, col, flag):
    txt = [txt[i][col:patCol + col] for i in range(row, patRow + row)]
 
# If pattern found
    if txt == pat:
        flag = 1
        print("Pattern found at", "(", row, ", ", col, ")")
    return flag
     
# Function to find the hash value of
# of the next column using rolling-hash
# of the Rabin-karp
def colRollingHash(txtHash, nxtRow):
 
    radix = 256
 
    # Find the hash of the matrix
    for j in range(txtCol):
        txtHash[j] = (txtHash[j]*radix + txt[nxtRow][j]) % prime
        
        txtHash[j] = txtHash[j] - (radix**(patRow) * txt[nxtRow-patRow][j])% prime
        
        txtHash[j] = txtHash[j]% prime
    return txtHash
     
 
# Function to match a pattern in
# the given 2D Matrix
def search(txt, pat):
     
# List of the hashed value for
    # the text and pattern columns
    patHash = []
    txtHash = []
 
    # Hash value of the
    # pat_hash and txt_hash
    patVal = 0
    txtVal = 0
 
    # Radix value for the input characters
    radix = 256
     
    # Variable to determine if
    # pattern was found or not
    flag = 0
     
    # Function call to find the
    # hash value of columns
    txtHash = findHash(txt, txtCol, patRow) 
    patHash = findHash(pat, patCol, patRow)
     
    # Calculate hash value for patHash
    for i in range(patCol):
        patVal = patVal + (radix**(patCol-i-1) * patHash[i] % prime)
    patVal = patVal % prime
     
     
    # Applying Rabin-Karp to compare
    # txtHash and patHash
    for i in range(patRow-1, txtRow):
        col = 0
        txtVal = 0
         
        # Find the hash value txtHash
        for j in range(patCol):
            txtVal = txtVal + (radix**(patCol-j-1) * txtHash[j])% prime
        txtVal = txtVal % prime
         
        if txtVal == patVal:
            flag = checkEquality(txt, i + 1-patRow, col, flag)
             
        else:
 
            # Roll the txt window by one character
            for k in range(patCol, txtCol):
 
                txtVal = txtVal * radix + (txtHash[k])% prime
                txtVal = txtVal - (radix**(patCol) * (txtHash[k-patCol]))% prime
                txtVal = txtVal % prime
                col = col + 1
 
                # Check if txtVal and patVal are equal
                if patVal == txtVal:
                    flag = checkEquality(txt, i + 1-patRow, col, flag)  
                else:
                    continue
                 
        # To make sure i does not exceed txtRow
        if i + 1<txtRow:
            txtHash = colRollingHash(txtHash, i + 1)
             
    if flag == 0:
        print("Pattern not found")
     
 
# Driver Code
if __name__ == "__main__":
  prime = 2147483647
  # Given Text
  txt = [[1, 2, 3], \
         [1, 0, 3], \
         [1, 0, 3]]
 
  # Given Pattern
  pat = [[1, 0], [1, 0]]
 
  # Dimensions of the text
  txtRow = 3
  txtCol = 3
 
  # Dimensions for the pattern
  patRow = 2
  patCol = 2
 
  # Function Call
  search(txt, pat)
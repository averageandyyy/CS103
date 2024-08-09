# Faster version of the hailstone sequence that works on decimal numbers.
# Unlike the other version, which is a composition between a decimal-to-unary
# converter and a unary hailstone sequence program, this one works entirely
# in decimal the whole time.

Start:
    If Blank Return False
    Move Left
    Goto MainLoop
    
# Main Loop: Check if we're at 1. If so, done! Otherwise handle odd/even cases.
MainLoop:
    # Trim leading 0s
    Move Right
    If Not '0' Goto MainLoop_ToEnd
    Write Blank
    Goto MainLoop

MainLoop_ToEnd:  
    # Wind to the last digit
    Move Right
    If Not Blank Goto MainLoop_ToEnd
    Move Left
    Move Left
    
    # Are we done?
    If Not Blank Goto ParityCheck
    Move Right
    If '1' Return True
    Move Left

# Determine whether to handle odd or even numbers
ParityCheck:
    Move Right
    If '2' Goto Halve
    If '4' Goto Halve
    If '6' Goto Halve
    If '8' Goto Halve
    If '0' Goto Halve
    Goto TripleAdd1

# Even case: Halve the number. First, scoot all the way to the front.
Halve:
    If Blank Goto Halve_Divide2_0
    Move Left
    Goto Halve
    
# Divide the current number by 2, no borrow.
Halve_Divide2_0:
    Move Right
    If Blank Goto Rewind
    
    # Even numbers don't carry
    If '0' Goto Divide2_0_NoCarry
    If '2' Goto Divide2_0_NoCarry
    If '4' Goto Divide2_0_NoCarry
    If '6' Goto Divide2_0_NoCarry
    If '8' Goto Divide2_0_NoCarry
    
    # Odd numbers do carry.
    If '1' Write '0'
    If '3' Write '1'
    If '5' Write '2'
    If '7' Write '3'
    If '9' Write '4'
    Goto Halve_Divide2_1

Divide2_0_NoCarry:    
    If '0' Write '0'
    If '2' Write '1'
    If '4' Write '2'
    If '6' Write '3'
    If '8' Write '4'
    Goto Halve_Divide2_0

# Divide the current number by 2, carrying 1 from the previous column
Halve_Divide2_1:
    Move Right
    If Blank Goto Rewind
    
    # Even numbers don't carry
    If '0' Goto Divide2_1_NoCarry
    If '2' Goto Divide2_1_NoCarry
    If '4' Goto Divide2_1_NoCarry
    If '6' Goto Divide2_1_NoCarry
    If '8' Goto Divide2_1_NoCarry
    
    # Odd numbers do carry.
    If '9' Write '9'
    If '7' Write '8'
    If '5' Write '7'
    If '3' Write '6'
    If '1' Write '5'
    Goto Halve_Divide2_1

Divide2_1_NoCarry:
    If '8' Write '9'
    If '6' Write '8'
    If '4' Write '7'
    If '2' Write '6'
    If '0' Write '5'
    Goto Halve_Divide2_0

    
# Rewind to the start and return to the main loop.
Rewind:
    Move Left
    If Blank Goto MainLoop
    Goto Rewind

# Triple the number and add 1.
TripleAdd1:
    If '9' Goto Init_9
    If '7' Goto Init_7
    If '5' Goto Init_5
    If '3' Goto Init_3
    If '1' Goto Init_1

# 3*9 + 1 = 28
Init_9:
    Write '8'
    Goto Triple_Carry2
    
# 3*7 + 1 = 22
Init_7:
    Write '2'
    Goto Triple_Carry2

# 3*5 + 1 = 16
Init_5:
    Write '6'
    Goto Triple_Carry1
    
# 3*3 + 1 = 10
Init_3:
    Write '0'
    Goto Triple_Carry1
    
# 3*1 + 1 = 4
Init_1:
    Write '4'
    Goto Triple_Carry0
    
# Triple the number; carry is 0
Triple_Carry0:
    Move Left
    If Blank Goto Rewind
    
    If '0' Goto Triple_Carry0_0
    If '1' Goto Triple_Carry0_1
    If '2' Goto Triple_Carry0_2
    If '3' Goto Triple_Carry0_3
    If '4' Goto Triple_Carry0_4
    If '5' Goto Triple_Carry0_5
    If '6' Goto Triple_Carry0_6
    If '7' Goto Triple_Carry0_7
    If '8' Goto Triple_Carry0_8
    If '9' Goto Triple_Carry0_9
    
# Triple the number; carry is 1
Triple_Carry1:
    Move Left    
    If '0' Goto Triple_Carry1_0
    If '1' Goto Triple_Carry1_1
    If '2' Goto Triple_Carry1_2
    If '3' Goto Triple_Carry1_3
    If '4' Goto Triple_Carry1_4
    If '5' Goto Triple_Carry1_5
    If '6' Goto Triple_Carry1_6
    If '7' Goto Triple_Carry1_7
    If '8' Goto Triple_Carry1_8
    If '9' Goto Triple_Carry1_9
    
    Write '1'
    Goto Rewind
    
# Triple the number; carry is 2
Triple_Carry2:
    Move Left    
    If '0' Goto Triple_Carry2_0
    If '1' Goto Triple_Carry2_1
    If '2' Goto Triple_Carry2_2
    If '3' Goto Triple_Carry2_3
    If '4' Goto Triple_Carry2_4
    If '5' Goto Triple_Carry2_5
    If '6' Goto Triple_Carry2_6
    If '7' Goto Triple_Carry2_7
    If '8' Goto Triple_Carry2_8
    If '9' Goto Triple_Carry2_9
    
    Write '2'
    Goto Rewind

# 3*0 + 0 = 0
Triple_Carry0_0:
    Write '0'
    Goto Triple_Carry0

# 3*1 + 0 = 3
Triple_Carry0_1:
    Write '3'
    Goto Triple_Carry0

# 3*2 + 0 = 6
Triple_Carry0_2:
    Write '6'
    Goto Triple_Carry0

# 3*3 + 0 = 9
Triple_Carry0_3:
    Write '9'
    Goto Triple_Carry0

# 3*4 + 0 = 12
Triple_Carry0_4:
    Write '2'
    Goto Triple_Carry1

# 3*5 + 0 = 15
Triple_Carry0_5:
    Write '5'
    Goto Triple_Carry1

# 3*6 + 0 = 18
Triple_Carry0_6:
    Write '8'
    Goto Triple_Carry1

# 3*7 + 0 = 21
Triple_Carry0_7:
    Write '1'
    Goto Triple_Carry2

# 3*8 + 0 = 24
Triple_Carry0_8:
    Write '4'
    Goto Triple_Carry2

# 3*9 + 0 = 27
Triple_Carry0_9:
    Write '7'
    Goto Triple_Carry2

# 3*0 + 1 = 1
Triple_Carry1_0:
    Write '1'
    Goto Triple_Carry0

# 3*1 + 1 = 4
Triple_Carry1_1:
    Write '4'
    Goto Triple_Carry0

# 3*2 + 1 = 7
Triple_Carry1_2:
    Write '7'
    Goto Triple_Carry0

# 3*3 + 1 = 10
Triple_Carry1_3:
    Write '0'
    Goto Triple_Carry1

# 3*4 + 1 = 13
Triple_Carry1_4:
    Write '3'
    Goto Triple_Carry1

# 3*5 + 1 = 16
Triple_Carry1_5:
    Write '6'
    Goto Triple_Carry1

# 3*6 + 1 = 19
Triple_Carry1_6:
    Write '9'
    Goto Triple_Carry1

# 3*7 + 1 = 22
Triple_Carry1_7:
    Write '2'
    Goto Triple_Carry2

# 3*8 + 1 = 25
Triple_Carry1_8:
    Write '5'
    Goto Triple_Carry2

# 3*9 + 1 = 28
Triple_Carry1_9:
    Write '8'
    Goto Triple_Carry2

# 3*0 + 2 = 2
Triple_Carry2_0:
    Write '2'
    Goto Triple_Carry0

# 3*1 + 2 = 5
Triple_Carry2_1:
    Write '5'
    Goto Triple_Carry0

# 3*2 + 2 = 8
Triple_Carry2_2:
    Write '8'
    Goto Triple_Carry0

# 3*3 + 2 = 11
Triple_Carry2_3:
    Write '1'
    Goto Triple_Carry1

# 3*4 + 2 = 14
Triple_Carry2_4:
    Write '4'
    Goto Triple_Carry1

# 3*5 + 2 = 17
Triple_Carry2_5:
    Write '7'
    Goto Triple_Carry1

# 3*6 + 2 = 20
Triple_Carry2_6:
    Write '0'
    Goto Triple_Carry2

# 3*7 + 2 = 23
Triple_Carry2_7:
    Write '3'
    Goto Triple_Carry2

# 3*8 + 2 = 26
Triple_Carry2_8:
    Write '6'
    Goto Triple_Carry2

# 3*9 + 2 = 29
Triple_Carry2_9:
    Write '9'
    Goto Triple_Carry2


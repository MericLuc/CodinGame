DoW = [ 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday' ]
MoY = [ 'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec' ]
DoM = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ]

# Inputs
leap     = int(input())
initDate = input()
endDate  = input()

# February leap year
DoM[1] += leap

# Parse inputs to extract dates
stDate  = initDate.split()
stDay   = DoW.index( stDate[0] ) # Monday -> 0
stMonth = MoY.index( stDate[1] ) # Jan    -> 0
stDoM   = int      ( stDate[2] ) # 2      -> 2
edDate  = endDate.split()
edMonth = MoY.index( edDate[0] )
edDoM   = int      ( edDate[1] )

dlt  = 0
PorF = 1 if(edMonth > stMonth) else -1 if (edMonth < stMonth) else 0 # Past or futur

if PorF > 0:
    dlt     += DoM[stMonth] - stDoM
    stDoM    = 0
    stMonth += 1
elif PorF < 0:
    dlt     -= stDoM
    stMonth -= 1
    stDoM    = DoM[stMonth]

while stMonth != edMonth:
    dlt     += PorF * DoM[stMonth]
    stMonth += PorF
    stDoM    = 0 if(PorF > 0) else DoM[stMonth]

dlt += edDoM - stDoM
print(DoW[(stDay + dlt) % 7])
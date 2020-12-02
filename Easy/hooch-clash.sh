read sMin sMax
read gS1 gS2
(( V = gS1**3 + gS2**3 ))
for (( i = sMin, j = sMax; i <= sMax; i++ )); do
  (( i == gS1 )) && continue
  (( j3 = V - i**3 ))
  (( j3 < sMin**3 )) && break
  (( j3 >= i**3 )) || break
  for (( ; j**3 > j3; j-- )); do :; done
  if (( j**3 == j3 )); then
    echo $i $j
    exit
  fi
done
echo VALID